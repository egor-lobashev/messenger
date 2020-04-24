#include <SFML/Network.hpp>
#include <iostream>
#include <cstring>

int main()
{
    sf::TcpSocket socket;

    for (;;)
    {
        if (socket.connect("127.0.0.1", 53000) != sf::Socket::Done)
        {
            std::cout << "Connection failed" << std::endl;
            return 0;
        }

        char data[] = "";
        std::cin >> data;
        sf::Socket::Status status = socket.send(data, strlen(data) + 1);

        if (status == sf::Socket::Done) {
            std::cout << "Msg has been sent successfully" << std::endl;
        } else {
            std::cout << "Msg has been sent unsuccessfully" << std::endl;
        }

        socket.disconnect();
    }
    


    return 0;
}