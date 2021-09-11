#pragma once

#include <string>
#include <vector>
#include "message-handler-components/message-handler-component.hpp"

class WebsocketClient;

class MessageHandler {
    public:
        MessageHandler();
        ~MessageHandler();

        void on_open(WebsocketClient&);
        void on_message(WebsocketClient&, std::string);

    private:
        std::vector<MessageHandlerComponent*> components;
};
