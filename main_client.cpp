#include "client.hpp"


int main(){
    Client client = Client("127.0.0.1",2000);
    client.connectIRCServer();
    std::string keyboardInput;
    std::string serverMessage;
    int exitLoop = 0;
    do {
        client.setAuxFds();

        if (keyboardInput == "salir") {
            exitLoop = 1;
        }
        serverMessage = client.checkIfHasMessages();
        std::cout<<"Server Message -> "<<serverMessage<<std::endl;
        std::cout<<":> ";
        getline(std::cin,keyboardInput);
        if (keyboardInput != "\n"){
            client.sendMessage(keyboardInput);
        }
    } while(exitLoop == 0);
    return 0;
}
