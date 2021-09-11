#include <obs.hpp>
#include <nlohmann/json.hpp>
#include "message-handler.hpp"
#include "websocket-client.hpp"
#include "message.hpp"
using json = nlohmann::json;

MessageHandler::MessageHandler() {
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
    } catch (const std::exception& e) {
        blog(LOG_ERROR, "[usukawa] message handler error: %s", e.what());
    } catch (...) {
        blog(LOG_ERROR, "[usukawa] message handler error");
    }
}

MessageHandler::~MessageHandler() {
}
