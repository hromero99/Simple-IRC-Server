#ifndef _CHANNEL_H_
#define _CHANNEL_H_
#include <iostream>
#include <vector>
#include "server_client.hpp"
#include <bits/stdc++.h>
#include <sys/socket.h>

class Channel{
  private:
    std::string _name;
    std::list<ServerClient> _clients;
    std::string _ownerUsername;
  public:
    Channel(std::string channelName);
    bool addNewClient(ServerClient client);
    bool removeClient(ServerClient client);
    inline std::string getChannelName()const {return _name;};
    inline void setOwner(std::string ownerUsername){_ownerUsername = ownerUsername;};
    inline std::string getOwner()const{return _ownerUsername;};
    void sendMessageToAllClients(std::string message, std::string username);
    bool checkIfUserIsInChannel(std::string username);
    bool dropUserFromChannel(const std::string &username);
};



#endif
