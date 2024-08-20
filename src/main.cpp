#include "order_management.h"
#include "websocket_server.h"

int main() {
    // Start the order management system
    startOrderManagement();

    // Start the WebSocket server
    startWebSocketServer();

    return 0;
}
