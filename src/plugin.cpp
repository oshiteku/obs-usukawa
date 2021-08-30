#include <memory>
#include <obs-module.h>
#include "plugin.hpp"
#include "usukawa-core.hpp"
#include "websocket-client.hpp"

OBS_DECLARE_MODULE()

std::shared_ptr<UsukawaCore> _usukawa_core;
std::shared_ptr<WebsocketClient> _websocket_client;

bool obs_module_load(void) {
    _usukawa_core = std::make_shared<UsukawaCore>();
    _websocket_client = std::make_shared<WebsocketClient>();

    // _usukawa_core->start();
    _websocket_client->start();

    blog(LOG_INFO, "usukawa: module loaded");

    return true;
}

void obs_module_unload() {
    _usukawa_core.reset();

    blog(LOG_INFO, "usukawa: module unloaded");
}
