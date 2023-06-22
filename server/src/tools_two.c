/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-zappy-kentin.paille
** File description:
** tools_two.c
*/

#include "../includes/zappy.h"

map_t *find_tile(serv_t *server, int x, int y)
{
    map_t *tile = server->map;
    while (tile != NULL) {
        if (tile->x == x && tile->y == y) {
            return tile;
        }
        tile = tile->next;
    }
    return NULL;
}

int calc_tile_to_string(map_t *tile, client_t *client)
{
    int len = 0;
    while (client != NULL) {
        if (client->player->x == tile->x && client->player->y == tile->y)
            len += 8;
        client = client->next;
    }
    for (int i = 0; i < tile->food; i++)
        len += 6;
    for (int i = 0; i < tile->linemate; i++)
        len += 10;
    for (int i = 0; i < tile->deraumere; i++)
        len += 11;
    for (int i = 0; i < tile->sibur; i++)
        len += 7;
    for (int i = 0; i < tile->mendiane; i++)
        len += 10;
    for (int i = 0; i < tile->phiras; i++)
        len += 8;
    for (int i = 0; i < tile->thystame; i++)
        len += 10;
    return len;
}
