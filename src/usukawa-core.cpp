#include <string>
#include <filesystem>
#include <boost/process/windows.hpp>
#include <obs.hpp>
#include <obs-module.h>
#include "usukawa-core.hpp"

UsukawaCore::UsukawaCore() {
}

void UsukawaCore::start() {
    std::filesystem::path data_path = obs_get_module_data_path(obs_current_module());
    auto script_path = data_path / "usukawa-core/src/App.bs.js";
    blog(LOG_INFO, "usukawa-core script location: %s", script_path.string().c_str());

    core_proc = bp::child(bp::search_path("node"), script_path.string(), bp::windows::create_no_window);
}

UsukawaCore::~UsukawaCore() {
}
