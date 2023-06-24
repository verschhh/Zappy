/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** incantation_level.c
*/

#include "../../includes/zappy.h"

int level_1_2_3(map_t *map, client_t *client, int nb_player_on_title)
{
    printf("nb_player_on_title = %d\n", nb_player_on_title);
    printf("linemate = %d\n", map->linemate);
    printf("deraumere = %d\n", map->deraumere);
    printf("sibur = %d\n", map->sibur);
    printf("mendiane = %d\n", map->mendiane);
    if (client->player->level == 1 && map->linemate >= 1
    && nb_player_on_title >= 1) {
        map->linemate--;
        return 0;
    }
    if (client->player->level == 2 && map->linemate >= 1
    && map->deraumere >= 1 && map->sibur >= 1 && nb_player_on_title >= 2) {
        map->linemate--;
        map->deraumere--;
        map->sibur--;
        return 1;
    }
    if (client->player->level == 3 && map->linemate >= 2 && map->sibur >= 1
    && map->phiras >= 2 && nb_player_on_title >= 2) {
        map->linemate -= 2;
        map->sibur--;
        map->phiras -= 2;
        return 1;
    }
    return 84;
}

int level_4_5(map_t *map, client_t *client, int nb_player_on_title)
{
    if (client->player->level == 4 && map->linemate >= 1 && map->deraumere >= 1
    && map->sibur >= 2 && map->phiras >= 1 && nb_player_on_title >= 4) {
        map->linemate--;
        map->deraumere--;
        map->sibur -= 2;
        map->phiras--;
        return 3;
    }
    if (client->player->level == 5 && map->linemate >= 1 && map->deraumere >= 2
    && map->sibur >= 1 && map->mendiane >= 3 && nb_player_on_title >= 4) {
        map->linemate--;
        map->deraumere -= 2;
        map->sibur--;
        map->mendiane -= 3;
        return 3;
    }
    return 84;
}

int level_6_7(map_t *map, client_t *client, int nb_player_on_title)
{
    if (client->player->level == 6 && map->linemate >= 1 && map->deraumere >= 2
    && map->sibur >= 3 && map->phiras >= 1 && nb_player_on_title >= 6) {
        map->linemate--;
        map->deraumere -= 2;
        map->sibur -= 3;
        map->phiras--;
        return 5;
    }
    if (client->player->level == 7 && map->linemate >= 2 && map->deraumere >= 2
    && map->sibur >= 2 && map->mendiane >= 2 && map->phiras >= 2
    && map->thystame >= 1 && nb_player_on_title >= 6) {
        map->linemate -= 2;
        map->deraumere -= 2;
        map->sibur -= 2;
        map->mendiane -= 2;
        map->phiras -= 2;
        map->thystame--;
        return 5;
    }
    return 84;
}
