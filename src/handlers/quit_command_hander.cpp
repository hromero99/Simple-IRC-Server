#include "server.hpp"

void Server::quitCommandHandler(ServerClient *client) {
    if (client -> getChannel() == "MAIN"){
        exitClient(client->getDescriptor());
    }
    else{
        moveUserToOtherChannel(client,client->getChannel(), "MAIN");
    }
}