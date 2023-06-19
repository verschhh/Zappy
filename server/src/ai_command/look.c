/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** look.c
*/

#include "../../includes/zappy.h"

char *tile_to_string(map_t *tile) {
    char *str = malloc(256 * sizeof(char));
    str[0] = '\0';  // initialize the string to be empty

    // TODO: add the player(s) on the tile

    // append each resource multiple times
    for (int i = 0; i < tile->food; i++) {
        strcat(str, "food ");
    }
    for (int i = 0; i < tile->linemate; i++) {
        strcat(str, "linemate ");
    }
    for (int i = 0; i < tile->deraumere; i++) {
        strcat(str, "deraumere ");
    }
    for (int i = 0; i < tile->sibur; i++) {
        strcat(str, "sibur ");
    }
    for (int i = 0; i < tile->mendiane; i++) {
        strcat(str, "mendiane ");
    }
    for (int i = 0; i < tile->phiras; i++) {
        strcat(str, "phiras ");
    }
    for (int i = 0; i < tile->thystame; i++) {
        strcat(str, "thystame ");
    }

    return str;
}

int look(int sockfd, serv_t *serv, char *buffer)
{
    return 0;
}