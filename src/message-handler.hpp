#pragma once

#include <string>

class WebsocketClient;

class MessageHandler {
    public:
        MessageHandler();
        ~MessageHandler();

        void on_open(WebsocketClient&);
        void on_message(WebsocketClient&, std::string);
};
