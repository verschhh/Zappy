/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** object.c
*/

#include "../../includes/zappy.h"

int check_element_tile(map_t *map, MapFieldFunc getFieldFunc)
{
    if (getFieldFunc > 0)
        return 1;
    else return 0;
}

int take_object(int sockfd, serv_t *serv, char *buffer)
{
    map_t *map_cpy = serv->map;
    int count = 0;
    char **array = split_string_at_spaces(buffer, &count);
    char *food[7] = {"food", "linemate\n", "deraumere\n",
        "sibur\n", "mendiane\n", "phiras\n", "thystame\n"};
    MapFieldFunc fieldFuncs[7] = {FOOD(serv->map), LINEMATE(serv->map), DERAUMERE(serv->map),
        SIBUR(serv->map), MENDIANE(serv->map), PHIRAS(serv->map), THYSTAME(serv->map)};

    for (int i = 0; i != 7; i++) {
        if (strstr(array[1], food[i]) != NULL) {
            check_element_tile(map_cpy, fieldFuncs[i]);
        }
    }
}