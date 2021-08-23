#include <obs-module.h>

#include "plugin.hpp"

OBS_DECLARE_MODULE()

bool obs_module_load(void) {
    blog(LOG_INFO, "usukawa: load");
    return true;
}

void obs_module_unload() {
    blog(LOG_INFO, "usukawa: unload");
}
