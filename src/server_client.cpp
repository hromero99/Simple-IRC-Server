#include "server_client.hpp"

ServerClient::ServerClient(int serverSocket) {
    _serverSocket = serverSocket;
    // Status default is not created, because the user is created when is login and can send messages
    _status = -1;
}

