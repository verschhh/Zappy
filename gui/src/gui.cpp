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

    // TODO: initiate server connection

    try {
        _scenes.push_back(new Menu());

        int tempWidth = 10;
        int tempHeight = 10;
        _scenes.push_back(new InGame(tempWidth, tempHeight));
    } catch (zappy::AScene::SceneException &e) {
        std::cerr << e.what() << std::endl;
        throw GuiException("Gui error: cannot load scenes");
    }
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
