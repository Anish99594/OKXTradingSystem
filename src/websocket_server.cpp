#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <iostream>
#include "websocket_server.h"
#include <functional> // Include this header to use std::bind and std::placeholders

typedef websocketpp::server<websocketpp::config::asio> server;

void on_message(server* s, websocketpp::connection_hdl hdl, server::message_ptr msg) {
    std::string symbol = msg->get_payload();
    std::cout << "Client subscribed to: " << symbol << std::endl;
    s->send(hdl, "Orderbook updates for " + symbol, websocketpp::frame::opcode::text);
}

void startWebSocketServer() {
    server wsServer;

    // Correctly use std::placeholders::_1 and std::placeholders::_2
    wsServer.set_message_handler(std::bind(&on_message, &wsServer, std::placeholders::_1, std::placeholders::_2));

    wsServer.init_asio();
    wsServer.listen(9002);
    wsServer.start_accept();

    std::cout << "WebSocket Server Started" << std::endl;
    wsServer.run();
}
