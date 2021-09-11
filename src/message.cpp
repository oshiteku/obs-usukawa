#include "message.hpp"

Message::Message(const json& json_message) {
    json_message["topic"].get_to(topic);
    json_message["type"].get_to(type);
    json_message["persistent"].get_to(persistent);
    json_message["data"].get_to(data);
}

json Message::to_json() {
    return {
        {"topic", topic},
        {"type", type},
        {"persistent", persistent},
        {"data", data}
    };
}

Message::~Message() {
}
