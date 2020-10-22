#include "server.hpp"

void Server::sendMessageToChannelHandler(ServerClient client, std::string clientMessage){
    int position  = clientMessage.find(" ");
    std::string message = clientMessage.substr(position + 1 ,clientMessage.size());
    std::vector<Channel>::iterator it = _channels.begin();
    for (; it != _channels.end(); it++){
        //Found the Channel object in which our user in
        if (it->getChannelName() == client.getChannel() ){
            it -> sendMessageToAllClients(message,client.getUsername());
        }
    }
    sendMessageToClient(client.getDescriptor(), "+OK. Message sended");

}