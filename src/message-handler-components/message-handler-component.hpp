#pragma once

#include "../message.hpp"

class MessageHandlerComponent {
    public:
        static const std::string topic;

        virtual void on_message(Message& message) {};
};
