#include "server.hpp"

void Server::addClientToChannelHandler(ServerClient client, std::string clientMessage){
    //Split original message to get username to add
    int position;
    position = clientMessage.find(" ");
    std::string clientToAdd = clientMessage.substr(position + 1, clientMessage.size());
    // Check if user is User to move exists, otherwise it is impossible to move
    bool existsUser = false;
    bool isJoinedToOtherChannel = false;
    ServerClient*  clientObjectToMove =  new ServerClient(-1);
    std::vector<ServerClient>::iterator it = _clients.begin();
    for (; it != _clients.end(); it++){
        if (it -> getUsername() == clientToAdd){
          // Flag to indicate user exists
          existsUser = true;
          clientObjectToMove = &*it;
          //Flag to check if user is in other channel from default
          if (it -> getChannel() != "MAIN"){
                isJoinedToOtherChannel = true;
          }
        }
    }
   if (!existsUser){
       sendMessageToClient(client.getDescriptor(), "-Err. User " + clientToAdd + "is not connected\n");
   }
   else if (isJoinedToOtherChannel){
       sendMessageToClient(client.getDescriptor(), "-Err. User" + clientToAdd+ " cannot be included\n");
   }
   else{
       sendMessageToClient(client.getDescriptor(), "+Ok.User"+clientToAdd+" included successfully\n");
       moveUserToOtherChannel(clientObjectToMove, clientObjectToMove->getChannel(), client.getChannel());
   }
}