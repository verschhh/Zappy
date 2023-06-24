/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** draw.cpp
*/

#include "../../includes/scenes.hpp"
#include <iostream> //! TEMP

void zappy::Pause::drawScene(sf::RenderWindow& window)
{
    window.draw(_backgroundSprite);
    window.draw(_backButtonSprite);
    window.draw(_quitButtonSprite);
    window.draw(_statsLogoSprite);

    total_t total = _total;

    window.draw(_pnjsLogoSprite);
    std::string pnjString = std::to_string(total.pnj);
    _pnjText = setText(
        pnjString,
        sf::Vector2f(525, 315),
        50,
        sf::Color::White
    );
    window.draw(_pnjText);

    window.draw(_deathsLogoSprite);
    std::cout << "Death counter: " << _deathCounter << std::endl;
    std::string deathString = std::to_string(*_deathCounter);
    _deathText = setText(
        deathString,
        sf::Vector2f(525, 415),
        50,
        sf::Color::White
    );
    window.draw(_deathText);

    window.draw(_ressourcesLogoSprite);

    window.draw(_foodSprite);
    std::string foodString = std::to_string(total.food);
    _foodText = setText(
        foodString,
        sf::Vector2f(620, 515),
        50,
        sf::Color::White
    );
    window.draw(_foodText);

    window.draw(_linemateSprite);
    std::string linemateString = std::to_string(total.linemate);
    _linemateText = setText(
        linemateString,
        sf::Vector2f(820, 515),
        50,
        sf::Color::White
    );
    window.draw(_linemateText);

    window.draw(_deraumereSprite);
    std::string deraumereString = std::to_string(total.deraumere);
    _deraumereText = setText(
        deraumereString,
        sf::Vector2f(1020, 515),
        50,
        sf::Color::White
    );
    window.draw(_deraumereText);

    window.draw(_siburSprite);
    std::string siburString = std::to_string(total.sibur);
    _siburText = setText(
        siburString,
        sf::Vector2f(1220, 515),
        50,
        sf::Color::White
    );
    window.draw(_siburText);

    window.draw(_mendianeSprite);
    std::string mendianeString = std::to_string(total.mendiane);
    _mendianeText = setText(
        mendianeString,
        sf::Vector2f(1420, 515),
        50,
        sf::Color::White
    );
    window.draw(_mendianeText);

    window.draw(_phirasSprite);
    std::string phirasString = std::to_string(total.phiras);
    _phirasText = setText(
        phirasString,
        sf::Vector2f(1620, 515),
        50,
        sf::Color::White
    );
    window.draw(_phirasText);

    window.draw(_thystameSprite);
    std::string thystameString = std::to_string(total.thystame);
    _thystameText = setText(
        thystameString,
        sf::Vector2f(1820, 515),
        50,
        sf::Color::White
    );
    window.draw(_thystameText);
}
