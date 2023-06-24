/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** spawn_ressources.c
*/

#include "../../includes/zappy.h"

void add_ressources_on_map(map_t *current)
{
    if (rand() % 100 + 1 < FOOD_DENSITY)
        current->food += 1;
    if (rand() % 100 + 1 < LINEMATE_DENSITY)
        current->linemate += 1;
    if (rand() % 100 + 1 < DERAUMERE_DENSITY)
        current->deraumere += 1;
    if (rand() % 100 + 1 < SIBUR_DENSITY)
        current->sibur += 1;
    if (rand() % 100 + 1 < MENDIANE_DENSITY)
        current->mendiane += 1;
    if (rand() % 100 + 1 < PHIRAS_DENSITY)
        current->phiras += 1;
    if (rand() % 100 + 1 < THYSTAME_DENSITY)
        current->thystame += 1;
}
