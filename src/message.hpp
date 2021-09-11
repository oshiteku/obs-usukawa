#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Message {
    public:
        Message(const json&);
        ~Message();

        std::string topic;
        std::string type;
        bool persistent;
        json data;

        json to_json();
};
