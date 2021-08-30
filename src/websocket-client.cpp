#include <obs.hpp>
#include "websocket-client.hpp"

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

WebsocketClient::WebsocketClient() {
    _client.set_access_channels(websocketpp::log::alevel::all);
    _client.clear_access_channels(websocketpp::log::alevel::frame_payload);

    _client.init_asio();
    _client.set_open_handler(bind(&WebsocketClient::on_open, this, ::_1));
    _client.set_close_handler(bind(&WebsocketClient::on_close, this, ::_1));
    _client.set_message_handler(bind(&WebsocketClient::on_message, this, ::_1, ::_2));
}

void WebsocketClient::start() {
    std::string uri = "ws://localhost:5555";

    websocketpp::lib::error_code ec;
    client::connection_ptr con = _client.get_connection(uri, ec);
    if (ec) {
        blog(LOG_ERROR, "could not create websocket connection: %s", ec.message().c_str());
        return;
    }
    _client.connect(con);

    _client_thread = std::thread([&]{
        blog(LOG_INFO, "websocket thread start");
        try {
            _client.run();
        } catch (websocketpp::exception const &e) {
            blog(LOG_ERROR, "websocket error: %s", e.what());
        }
        blog(LOG_INFO, "websocket thread exit");
    });
}

void WebsocketClient::on_open(connection_hdl hdl) {
    auto con = _client.get_con_from_hdl(hdl);
    auto uri = con->get_uri()->str();
    blog(LOG_INFO, "websocket client connected: %s", uri.c_str());
}

void WebsocketClient::on_close(connection_hdl hdl) {
    auto con = _client.get_con_from_hdl(hdl);
    auto uri = con->get_uri()->str();
    blog(LOG_INFO, "websocket client disconnected: %s", uri.c_str());
}

void WebsocketClient::on_message(connection_hdl hdl, message_ptr msg) {
    auto payload = msg->get_payload();
    blog(LOG_INFO, "websocket message received: %s", payload.c_str());
}

WebsocketClient::~WebsocketClient() {
}
