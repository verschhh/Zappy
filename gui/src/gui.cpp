/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-zappy-kentin.paille
** File description:
** gui.cpp
*/

#include "../includes/gui.hpp"
#include <iostream>

zappy::Gui::Gui(int port, std::string machine)
: _indexScene(0)
{
    _port = port;
    _machine = machine;

    _scenes.push_back(new Menu());

    // TODO: initiate server connection
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

    while (window.isOpen()) {
        _scenes[_indexScene]->handleEvents(window);

        window.clear();

        _scenes[_indexScene]->drawScene(window);

        window.display();
    }
}
