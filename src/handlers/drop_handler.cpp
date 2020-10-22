#include "server.hpp"

void Server::dropUserFromChannelHandler(ServerClient client, const std::string &clientMessage){
    int position = clientMessage.find(" ");
    std::string usernameToDelete = clientMessage.substr(position + 1, clientMessage.size());
    //The client only can delete users from the channel which is joined (and if is admin in this channel)
    bool isUserAdmin = false;
    bool isUserInChannel = false;
    std::vector<Channel>::iterator  it = _channels.begin();
    for(; it != _channels.end(); it ++){
        if (it -> getChannelName() == client.getChannel()){
            if (it ->getOwner() == client.getUsername()){
                isUserAdmin = true;
            }
            if (it->checkIfUserIsInChannel(usernameToDelete)){
                isUserInChannel = true;
            }
        }
    }
    if (isUserAdmin && isUserInChannel) {
        it = _channels.begin();
        for (; it != _channels.end(); it++) {
            if (it -> getChannelName() == client.getChannel()){
                it->dropUserFromChannel(usernameToDelete);
                sendMessageToClient(client.getDescriptor(),"+Ok. User delete succesfully\n");
            }
        }
        sendMessageToClient(client.getDescriptor(), "+Ok. User deleted from channel\n");
    }
    else {
        sendMessageToClient(client.getDescriptor(), "-Err. Error deleting user from Channel\n");
    }
}
