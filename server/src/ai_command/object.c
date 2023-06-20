/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** object.c
*/

#include "../../includes/zappy.h"

int check_element_tile(map_t *map, int materials)
{
    if (materials > 0)
        return 1;
    else
        return 0;
}

map_t *get_correct_tile(map_t *map, client_t *client)
{
    while (map != NULL) {
        if (client->player->x == map->x && client->player->y == map->y)
            return map;
        map = map->next;
    }

    return NULL;
}

void switch_case_take_two(int i, map_t *map_cpy, client_t *client_cpy)
{
    switch (i) {
        case 3:
            if (check_element_tile(map_cpy, map_cpy->sibur) == 1)
                map_cpy->sibur--;
                client_cpy->player->inventory->sibur++;
            break;
        case 4:
            if (check_element_tile(map_cpy, map_cpy->mendiane) == 1)
                map_cpy->mendiane--;
                client_cpy->player->inventory->mendiane++;
            break;
        case 5:
            if (check_element_tile(map_cpy, map_cpy->phiras) == 1)
                map_cpy->phiras--;
                client_cpy->player->inventory->phiras++;
            break;
        case 6:
            if (check_element_tile(map_cpy, map_cpy->thystame) == 1)
                map_cpy->thystame--;
                client_cpy->player->inventory->thystame++;
            break;
    }
}

void switch_case_take(int i, map_t *map_cpy, client_t *client_cpy)
{
    switch (i) {
        case 0:
            if (check_element_tile(map_cpy, map_cpy->food) == 1)
                map_cpy->food--;
                client_cpy->player->inventory->food++;
            break;
        case 1:
            if (check_element_tile(map_cpy, map_cpy->linemate) == 1)
                map_cpy->linemate--;
                client_cpy->player->inventory->linemate++;
            break;
        case 2:
            if (check_element_tile(map_cpy, map_cpy->deraumere) == 1)
                map_cpy->deraumere--;
                client_cpy->player->inventory->deraumere++;
            break;
        default:
            switch_case_take_two(i, map_cpy, client_cpy);
            break;
    }
}

int take_object(int sockfd, serv_t *serv, char *buffer)
{
    map_t *map_cpy = serv->map;
    int count = 0;
    char **array = split_string_at_spaces(buffer, &count);
    client_t *client_cpy = get_correct_client(serv, sockfd);
    char *food[7] = {"food", "linemate", "deraumere",
        "sibur", "mendiane", "phiras", "thystame"};
    map_cpy = get_correct_tile(map_cpy, get_correct_client(serv, sockfd));

    printf("Position = %d %d\n", map_cpy->x, map_cpy->y);
    for (int i = 0; i < 7; i++) {
        if (strstr(array[1], food[i]) != NULL) {
            switch_case_take(i, map_cpy, client_cpy);
        }
    }
    write(sockfd, "ok\n", 4);
    return 0;
}