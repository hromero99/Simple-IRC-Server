#ifndef _SERVERCLIENT_H_
#define _SERVERCLIENT_H_
#include <iostream>

class ServerClient{

    private:
        int _serverSocket;
        std::string _username;
        std::string _password;
        int _status;
        std::string _channel;

    public:
        ServerClient(int serverSocket);
        inline void setUsername(const std::string &username){_username = username;}
        inline void setPassword(const std::string &password){_password = password;}
        inline std::string getUsername(){ return _username;}
        inline std::string getPassword()const { return _password;}
        inline std::string returnCsvInfo()const {return _serverSocket + ";" +_username+";"+_password;}
        inline int getDescriptor() const{return _serverSocket;}
        inline int getStatus() const{return _status;}
        inline void setDescriptor(int descriptor) {_serverSocket = descriptor;}
        inline void setStatus(int newStatus){_status = newStatus;};
        inline void setChannel(std::string channelName){_channel = channelName;};
        inline std::string getChannel(){return _channel;};
};

#endif