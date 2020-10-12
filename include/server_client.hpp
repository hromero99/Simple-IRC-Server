#ifndef _SERVERCLIENT_H_
#define _SERVERCLIENT_H_
#include <iostream>

class ServerClient{

    private:
        int _serverSocket;
        std::string _username;
        std::string _password;
        int _status;

    public:
        ServerClient(int serverSocket);
        inline void setUsername(const std::string &username){_username = username;}
        inline void setPassword(const std::string &password){_password = password;}
        inline std::string getUsername(){ return _username;}
        inline int getDescriptor() const{return _serverSocket;}
        void login(std::string MessageBuffer);
};

#endif