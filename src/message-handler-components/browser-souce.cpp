#include <obs.hpp>
#include <obs-frontend-api.h>
#include "browser-source.hpp"

const std::string BrowserSourceMessageHandler::topic = "broadcaster/browser-source";

BrowserSourceMessageHandler::BrowserSourceMessageHandler() {
}

void BrowserSourceMessageHandler::on_message(Message &message) {
    blog(LOG_INFO, "[usukawa] broadcaster/browser-source: %s", message.data.dump().c_str());

    std::string id = "browser_source";
    std::string name;
    std::string url;
    int width = 800;
    int height = 600;

    try {
        message.data["name"].get_to(name);
        message.data["url"].get_to(url);
        if (message.data.contains("width")) {
            message.data["width"].get_to(width);
        }
        if (message.data.contains("height")) {
            message.data["height"].get_to(height);
        }
    } catch (...) {
        blog(LOG_ERROR, "[usukawa] BrowserSourceMessageHandler: invalid message data");
        return;
    }
    auto settings = obs_data_create();
    obs_data_set_string(settings, "url", url.c_str());
    obs_data_set_int(settings, "width", width);
    obs_data_set_int(settings, "heigt", height);

    auto scene_source = obs_frontend_get_current_scene();
    auto scene = obs_scene_from_source(scene_source);

    auto source = obs_source_create(id.c_str(), name.c_str(), settings, nullptr);
    if (source) {
        struct Data {
            obs_source_t *source;
            bool visible;
        };

        Data data;
        data.source = source;
        data.visible = true;

        auto add_source = [](void *_data, obs_scene_t *scene){
            auto data = reinterpret_cast<Data*>(_data);
            auto sceneitem = obs_scene_add(scene, data->source);
            obs_sceneitem_set_visible(sceneitem, data->visible);
        };

        obs_enter_graphics();
        obs_scene_atomic_update(scene, add_source, &data);
        obs_leave_graphics();
    }

    obs_data_release(settings);
    obs_source_release(scene_source);
    obs_source_release(source);
}

BrowserSourceMessageHandler::~BrowserSourceMessageHandler() {
}
