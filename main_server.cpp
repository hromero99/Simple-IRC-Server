#include "server.hpp"

int main(){
    Server server = Server(10);
    // Waiting for requests
    server.bindServer();
    while(1){
        server.setAuxFds();
        //Waiting to get messages of clients (new o already connected)
        if (server.getClientsOutput() > 0){
            //Looking for connection Socket
            server.lookForConnectionSocket();
        }
    }
    server.shutdown();
    return 0;
}
