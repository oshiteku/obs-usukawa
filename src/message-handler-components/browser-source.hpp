#pragma once

#include "message-handler-component.hpp"

class BrowserSourceMessageHandler : public MessageHandlerComponent {
    public:
        BrowserSourceMessageHandler();
        ~BrowserSourceMessageHandler();

        void on_message (Message&) override;
};
