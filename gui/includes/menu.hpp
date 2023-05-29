/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-zappy-kentin.paille
** File description:
** menu.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu();

    void loadTextures();
    void setupButtons();
    void handleEvents(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    bool isQuitButtonClicked();


private:
    sf::Texture playButtonTexture;
    sf::Sprite playButtonSprite;
    sf::Texture quitButtonTexture;
    sf::Sprite quitButtonSprite;
    bool _isQuitButtonClicked;
};
