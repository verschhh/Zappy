/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-zappy-kentin.paille
** File description:
** gui.cpp
*/

#include "../includes/gui.hpp"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

// zappy::Gui::Gui(int port, std::string machine)
// : _indexScene(0)
// {
//     _port = port;
//     _machine = machine;

//     // TODO: initiate server connection

//     try {
//         _scenes.push_back(new Menu());

//         int tempWidth = 10;
//         int tempHeight = 10;
//         _scenes.push_back(new InGame(tempWidth, tempHeight));
//     } catch (zappy::AScene::SceneException &e) {
//         std::cerr << e.what() << std::endl;
//         throw GuiException("Gui error: cannot load scenes");
//     }
// }

zappy::Gui::Gui(int port, std::string machine)
: _indexScene(0)
{
    _port = port;
    _machine = machine;

    // Initiate server connection
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        throw GuiException("Error: Failed to create socket");
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(_port);
    serverAddress.sin_addr.s_addr = inet_addr(_machine.c_str());

    // int connectionResult = connect(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    // if (connectionResult == -1) {
    //     throw GuiException("Error: Failed to connect to the server");
    // }
    int connectionResult = connect(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if (connectionResult == -1) {
        perror("connect");
        throw GuiException("Error: Failed to connect to the server");
    }


    try {
        _scenes.push_back(new Menu());

        int tempWidth = 10;
        int tempHeight = 10;
        _scenes.push_back(new InGame(tempWidth, tempHeight));
    } catch (zappy::AScene::SceneException &e) {
        std::cerr << e.what() << std::endl;
        throw GuiException("Gui error: cannot load scenes");
    }

    // TODO: Store the socket file descriptor and use it for communication with the server
    // You can store the sockfd as a member variable of the Gui class and use it in other methods as needed.
}

void zappy::Gui::setIcon(sf::RenderWindow& window) {
    sf::Image icon;
    if (!icon.loadFromFile("gui/assets/zappyFavicon.png")) {
        throw GuiException("Error: cannot load icon");
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void zappy::Gui::run() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Zappy", sf::Style::Fullscreen);
    setIcon(window);

    sf::Clock clock;

    while (window.isOpen()) {
        _scenes[_indexScene]->handleEvents(window);
        setIndexScene(_scenes[_indexScene]->getIndexScene());

        window.clear();

        _scenes[_indexScene]->drawScene(window, clock);

        window.display();
    }
}
