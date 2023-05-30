/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-zappy-kentin.paille
** File description:
** gui.cpp
*/

#include "../includes/gui.hpp"
#include <iostream>

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

    Menu menu;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                    window.close();
            }
        }
        window.clear();

        menu.handleEvents(window);

        // if (menu.isQuitButtonClicked()) {
        //     window.close();
        // }

        menu.draw(window);

        window.display();
    }
}
