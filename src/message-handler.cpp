#include <obs.hpp>
#include <nlohmann/json.hpp>
#include "message-handler.hpp"
#include "websocket-client.hpp"
#include "message.hpp"
#include "message-handler-components/browser-source.hpp"

using json = nlohmann::json;

MessageHandler::MessageHandler() {
    components = {
        new BrowserSourceMessageHandler()
    };
}

void MessageHandler::on_open(WebsocketClient &client) {
    json request = {
        {"topic", "broadcaster/#"},
        {"type", "subscribe"}
    };
    client.send(request.dump());
}

void MessageHandler::on_message(WebsocketClient &client, std::string message_str) {
    try {
        auto json_message = json::parse(message_str);
        auto message = Message(json_message);
        for (auto& c : components) {
            if (message.topic == c->topic) {
                c->on_message(message);
            }
        }
    } catch (const std::exception& e) {
        blog(LOG_ERROR, "[usukawa] message handler error: %s", e.what());
    } catch (...) {
        blog(LOG_ERROR, "[usukawa] message handler error");
    }
}

MessageHandler::~MessageHandler() {
    for (auto& c : components) {
        delete c;
    }
}
