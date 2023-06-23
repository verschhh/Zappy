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

    std::string str = "Total pnj: " + std::to_string(total.pnj) + "\n";
    str += "Total food: " + std::to_string(total.food) + "\n";
    str += "Total linemate: " + std::to_string(total.linemate) + "\n";
    str += "Total deraumere: " + std::to_string(total.deraumere) + "\n";
    str += "Total sibur: " + std::to_string(total.sibur) + "\n";
    str += "Total mendiane: " + std::to_string(total.mendiane) + "\n";
    str += "Total phiras: " + std::to_string(total.phiras) + "\n";
    str += "Total thystame: " + std::to_string(total.thystame) + "\n";

    std::cout << str << std::endl;

    window.draw(_pnjsLogoSprite);
    // std::string pnjString = std::to_string(total.pnj);
    std::string pnjString = "Hello world";
    _pnjText = setText(
        pnjString,
        sf::Vector2f(800, 350),
        50,
        sf::Color::Yellow
    );
    window.draw(_pnjText);

    // TODO: fix draw text & display all the ressources

    // window.draw(_deathsLogoSprite);
    // window.draw(_ressourcesLogoSprite);
    // window.draw(_foodSprite);
    // window.draw(_linemateSprite);
    // window.draw(_deraumereSprite);
    // window.draw(_siburSprite);
    // window.draw(_mendianeSprite);
    // window.draw(_phirasSprite);
    // window.draw(_thystameSprite);
}
