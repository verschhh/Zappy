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
#include <sstream>

zappy::Gui::Gui(int port, std::string machine) : _connection(port, machine), _indexScene(0)
{
    try {
        _connection.connect();
        std::string response = _connection.receive();
        std::cout << response << std::endl;
    } catch (const std::runtime_error& e) {
        throw GuiException("Gui error: cannot connect to the server");
        return;
    }

    try {
        _scenes.push_back(new Menu(_connection));

        int width = 20;
        int height = 10;

        _connection.send("msz\n");
        std::string response = _connection.receive();
        std::istringstream iss(response);
        std::string cmd;
        iss >> cmd >> width >> height;

        _scenes.push_back(new InGame(_connection, width, height));

        _scenes.push_back(new EndGame(_connection));
    } catch (AScene::SceneException& e) {
        std::cerr << e.what() << std::endl;
        throw GuiException("Gui error: cannot load scenes");
    }
}

void zappy::Gui::setIcon(sf::RenderWindow& window) {
    sf::Image icon;
    if (!icon.loadFromFile("gui/assets/icons/zappyFavicon.png")) {
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
        _scenes[_indexScene]->drawScene(window);
        window.display();
    }
}
