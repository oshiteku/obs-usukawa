#pragma once

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

typedef websocketpp::client<websocketpp::config::asio_client> client;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

using websocketpp::connection_hdl;

class MessageHandler;

class WebsocketClient {
    public:
        WebsocketClient(MessageHandler &message_handler);
        ~WebsocketClient();

        void start();
        void send(std::string);

    private:
        MessageHandler& message_handler;

        client _client;
        connection_hdl _hdl;
        std::thread _client_thread;

        void on_open(connection_hdl);
        void on_close(connection_hdl);
        void on_fail(connection_hdl);
        void on_message(connection_hdl, message_ptr);
};
