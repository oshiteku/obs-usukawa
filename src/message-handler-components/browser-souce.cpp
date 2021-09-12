#include <obs.hpp>
#include <obs-frontend-api.h>
#include "browser-source.hpp"

const std::string BrowserSourceMessageHandler::topic = "broadcaster/browser-source";

BrowserSourceMessageHandler::BrowserSourceMessageHandler() {
}

void BrowserSourceMessageHandler::on_message(Message &message) {
    blog(LOG_INFO, "[usukawa] broadcaster/browser-source: %s", message.data.dump().c_str());

    auto scene_source = obs_frontend_get_current_scene();
    auto scene = obs_scene_from_source(scene_source);

    std::string id = "browser_source";
    std::string name = "[u]";

    auto source = obs_source_create(id.c_str(), name.c_str(), nullptr, nullptr);
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

    obs_source_release(scene_source);
    obs_source_release(source);
}

BrowserSourceMessageHandler::~BrowserSourceMessageHandler() {
}
