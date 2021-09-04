#include "message-handler.hpp"
#include "websocket-client.hpp"

MessageHandler::MessageHandler() {
}

void MessageHandler::on_open(WebsocketClient &client) {
    client.send("{ \"topic\": \"broadcaster\",  \"type\": \"subscribe\" }");
}

void MessageHandler::on_message(WebsocketClient &client, std::string) {
}

MessageHandler::~MessageHandler() {
}
