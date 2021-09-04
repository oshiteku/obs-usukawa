#include <string>
#include <filesystem>
#include <boost/process/windows.hpp>
#include <obs.hpp>
#include <obs-module.h>
#include "usukawa-core.hpp"

UsukawaCore::UsukawaCore() {
}

void UsukawaCore::start(std::function<void(void)> server_started_handler) {
    std::filesystem::path data_path = obs_get_module_data_path(obs_current_module());
    auto script_path = data_path / "usukawa-core/src/App.bs.js";
    blog(LOG_INFO, "[usukawa] usukawa-core script location: %s", script_path.string().c_str());

    core_output_reader = std::thread(
        [this, server_started_handler = std::move(server_started_handler)]{
            std::string line;
            while (std::getline(core_output_stream, line)) {
                if (line == "listen!") {
                    server_started_handler();
                }
                blog(LOG_INFO, "[usukawa] core: %s", line.c_str());
            }
        }
    );

    core_proc = bp::child(
        bp::search_path("node"),
        script_path.string(),
        bp::std_out > core_output_stream,
        bp::windows::create_no_window
    );
}

UsukawaCore::~UsukawaCore() {
    core_proc.terminate();
    core_proc.wait();
    core_output_stream.pipe().close();
    core_output_reader.join();
}
