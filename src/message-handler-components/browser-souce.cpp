#include <obs.hpp>
#include "browser-source.hpp"

const std::string BrowserSourceMessageHandler::topic = "broadcaster/browser-source";

BrowserSourceMessageHandler::BrowserSourceMessageHandler() {
}

void BrowserSourceMessageHandler::on_message(Message &message) {
    blog(LOG_INFO, "[usukawa] broadcaster/browser-source: %s", message.data.dump().c_str());
}

BrowserSourceMessageHandler::~BrowserSourceMessageHandler() {
}
