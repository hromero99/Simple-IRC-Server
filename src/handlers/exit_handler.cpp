#include "server.hpp"

void Server::exitClient(ServerClient clientToExit) {
    std::vector<ServerClient>::iterator it = _clients.begin();
    fd_set * readfds = &_readfds;
    // Delete client from list
    for (; it != _clients.end(); it++){
        if (it->getUsername() == clientToExit.getUsername()){
            //Delete from FD_SETS
            FD_CLR(clientToExit.getDescriptor(), readfds);
            //Decrement Nclients
            _Nclients--;
            break;
        }
    }
    _clients.erase(it);
    notifyAllClients("Desconected user " + clientToExit.getUsername() + "\n");

}