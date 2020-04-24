#include <SFML/Network.hpp>
#include <iostream>
#include <cstring>
#include <thread>
//#include <vector>

void manageClient(sf::TcpSocket socket)
{
    std::cout << "Client connected" << std::endl;

    for (;;)
    {
        char data[10] = {};
        std::size_t bytesReceived = 0;

        //std::cout << "Waiting for receive" << std::endl;
        sf::Socket::Status status = socket.receive(data, 10, bytesReceived);

        if (status == sf::Socket::Done)
        {
            //std::cout << "Got " << bytesReceived << " bytes." << std::endl;
            std::cout << "Msg: " << data << std::endl;
        }

        if (status == sf::Socket::Disconnected)
        {
            //std::cout << "Client disconnected" << std::endl;
            break;
        }
    }
}

int main()
{
    sf::TcpListener listener;

    if (listener.listen(53000) != sf::Socket::Done) 
    {
        std::cout << "Can not binding port" << std::endl;
        return 0;
    }

    std::vector<std::thread*> clients;
    int i = 0;

    for (;;)
    {
        sf::TcpSocket socket;
        if (listener.accept(socket) != sf::Socket::Done) {
            std::cout << "Can not accept connection" << std::endl;
            return 0;
        }

        clients[i++] = new std::thread(manageClient, socket);
    }

    for (i=0; i<clients.size(); i++)
        delete clients[i];

    return 0;
}