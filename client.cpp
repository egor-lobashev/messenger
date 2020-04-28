#include <SFML/Network.hpp>
#include <iostream>
#include <cstring>

int main()
{
    char name[] = "#";
    char input[10] = "";
    std::cout << "Print your name\n";
    std::cin.getline(input, 256, '\n');
    strcat(name, input);
    std::cout << name << "\n";
    
    //name[strlen(name)] = *sep;
    sf::TcpSocket socket;

    for (;;)
    {
        if (socket.connect("127.0.0.1", 53000) != sf::Socket::Done)
        {
            std::cout << "Connection failed" << std::endl;
            return 0;
        }

        char data[256] = "";
        
        std::cin.getline(data, 256, '\n');

        strcat(data, name);
        std::cout << data << '\n';
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