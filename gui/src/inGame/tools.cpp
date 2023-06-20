/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** tools.cpp
*/

#include "../../includes/scenes.hpp"

int zappy::InGame::randomNumber(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    int randomNumber = dist(gen);
    return (randomNumber);
}

std::vector<std::string> zappy::InGame::splitString(std::string str, char delimiter)
{
    std::vector<std::string> internal;
    std::stringstream ss(str);
    std::string tok;

    while (getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    return (internal);
}
