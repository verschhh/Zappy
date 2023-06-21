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

int my_modulo(double nb, double div)
{
    int result = nb / div;
    

}