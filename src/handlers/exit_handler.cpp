#include "server.hpp"

void Server::exitClient(int clientDescriptor) {
    std::vector<ServerClient>::iterator it = _clients.begin();
    // Delete client from list
    for (; it != _clients.end(); it++){
        if (it->getDescriptor() == clientDescriptor){
            sendMessageToClient(clientDescriptor, "+Ok. Desconexión completada\n");
            break;
        }
    }
    if (clientDescriptor != -1){
        //Delete from FD_SETS
        FD_CLR(clientDescriptor, &_readfds);
        //Decrement Nclients
        _Nclients--;
        _clients.erase(it);
        notifyAllClients("+Ok. Usuario " + it->getUsername() + "desconectado"+"\n");
    }

}