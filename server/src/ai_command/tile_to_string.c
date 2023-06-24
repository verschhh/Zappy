/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** tile_to_string.c
*/

#include "../../includes/zappy.h"


static char *add_map_content(char *str, map_t *tile)
{
    for (int i = 0; i < tile->food; i++)
        strcat(str, "food ");
    for (int i = 0; i < tile->linemate; i++)
        strcat(str, "linemate ");
    for (int i = 0; i < tile->deraumere; i++)
        strcat(str, "deraumere ");
    for (int i = 0; i < tile->sibur; i++)
        strcat(str, "sibur ");
    for (int i = 0; i < tile->mendiane; i++)
        strcat(str, "mendiane ");
    for (int i = 0; i < tile->phiras; i++)
        strcat(str, "phiras ");
    for (int i = 0; i < tile->thystame; i++)
        strcat(str, "thystame ");
    if (strlen(str) > 0)
        str[strlen(str) - 1] = '\0';
    return str;
}

char *tile_to_string(map_t *tile, client_t *client)
{
    char *str = malloc(sizeof(char) * (calc_tile_to_string(tile, client) + 1));
    str[0] = '\0';
    while (client != NULL) {
        if (client->player->x == tile->x && client->player->y == tile->y)
            strcat(str, "player ");
        client = client->next;
    }
    str = add_map_content(str, tile);
    return str;
}