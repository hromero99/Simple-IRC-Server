#ifndef _CHANNEL_H_
#define _CHANNEL_H_
#include <iostream>
#include <vector>
#include "server_client.hpp"
#include<bits/stdc++.h>

class Channel{
  private:
    std::string _name;
    std::list<ServerClient> _clients;
  public:
    Channel(std::string channelName);
    bool addNewClient(ServerClient client);
    bool removeClient(ServerClient client);
    inline std::string getChannelName()const {return _name;};
};



#endif
