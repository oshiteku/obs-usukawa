#include <memory>

#include <obs-module.h>

#include "plugin.hpp"
#include "usukawa-core.hpp"

OBS_DECLARE_MODULE()

std::shared_ptr<UsukawaCore> _usukawa_core;

bool obs_module_load(void) {
    _usukawa_core = std::make_shared<UsukawaCore>();

    blog(LOG_INFO, "usukawa: module loaded");

    return true;
}

void obs_module_unload() {
    _usukawa_core.reset();

    blog(LOG_INFO, "usukawa: module unloaded");
}
