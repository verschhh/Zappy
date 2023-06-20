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

void get_correct_tile(map_t *map, client_t *client)
{
    while (map != NULL) {
        if (client->player->x == map->x && client->player->y == map->y)
            return;
        map = map->next;
    }
}

int take_object(int sockfd, serv_t *serv, char *buffer)
{
    map_t *map_cpy = serv->map;
    int count = 0;
    char **array = split_string_at_spaces(buffer, &count);
    char *food[7] = {"food", "linemate", "deraumere",
        "sibur", "mendiane", "phiras", "thystame"};
    MapFieldFunc fieldFuncs[7] = {FOOD(serv->map), LINEMATE(serv->map), DERAUMERE(serv->map),
        SIBUR(serv->map), MENDIANE(serv->map), PHIRAS(serv->map), THYSTAME(serv->map)};

    get_correct_client(map_cpy, get_correct_client(serv, sockfd));
    printf("Position = %d %d", map_cpy->x, map_cpy->y);
    for (int i = 0; i != 7; i++) {
        if (strstr(array[1], food[i]) != NULL) {
            check_element_tile(map_cpy, fieldFuncs[i]);
        }
    }
}