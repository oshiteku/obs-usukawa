#include <string>
#include <filesystem>
#include <regex>
#include <nlohmann/json.hpp>
#include <boost/process/windows.hpp>
#include <obs.hpp>
#include <obs-module.h>
#include "usukawa-core.hpp"

using json = nlohmann::json;

UsukawaCore::UsukawaCore() {
}

void UsukawaCore::start(std::function<void(std::string)> server_started_handler) {
    std::filesystem::path data_path = obs_get_module_data_path(obs_current_module());
    auto script_path = data_path / "usukawa-core/src/App.bs.js";
    blog(LOG_INFO, "[usukawa] usukawa-core script location: %s", script_path.string().c_str());

    core_output_reader = std::thread(
        [this, server_started_handler = std::move(server_started_handler)]{
            std::string line;
            while (std::getline(core_output_stream, line)) {
                blog(LOG_INFO, "[usukawa] core: %s", line.c_str());

                try {
                    auto json_log = json::parse(line);
                    std::string log_message;
                    json_log["message"].get_to(log_message);

                    std::smatch m;
                    std::regex re(R"(listen: ws://(.+):([0-9]+)/ws/(.+))");
                    if (std::regex_match(log_message, m, re)) {
                        auto host = m[1].str();
                        auto port = m[2].str();
                        auto api_key = m[3].str();
                        auto url = "ws://" + host + ":" + port + "/ws/" + api_key;
                        server_started_handler(url);
                        blog(LOG_INFO, "[usukawa] core server started: ws://%s:%s/ws/%s", host.c_str(), port.c_str(), api_key.c_str());
                    }
                    blog(LOG_INFO, "[usukawa] core: %s", log_message.c_str());
                } catch (...) {
                    blog(LOG_ERROR, "[usukawa] failed to parse core log message");
                }
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
