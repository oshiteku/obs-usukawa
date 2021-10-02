#include <memory>
#include <obs-module.h>
#include "plugin.hpp"
#include "usukawa-core.hpp"
#include "websocket-client.hpp"
#include "message-handler.hpp"

OBS_DECLARE_MODULE()

std::shared_ptr<UsukawaCore> _usukawa_core;
std::shared_ptr<WebsocketClient> _websocket_client;
std::shared_ptr<MessageHandler> _message_handler;

bool obs_module_load(void) {
    _usukawa_core = std::make_shared<UsukawaCore>();
    _message_handler = std::make_shared<MessageHandler>();
    _websocket_client = std::make_shared<WebsocketClient>(*_message_handler);

    _usukawa_core->start(
        [](std::string url){
            _websocket_client->start(url);
        }
    );

    blog(LOG_INFO, "[usukawa] plugin module loaded");

    return true;
}

void obs_module_unload() {
    _usukawa_core.reset();
    _websocket_client.reset();
    _message_handler.reset();

    blog(LOG_INFO, "[usukawa] plugin module unloaded");
}
