/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** object.c
*/

#include "../../includes/zappy.h"

int check_element_tile(int materials, int sockfd)
{
    if (materials > 0) {
        write(sockfd, "ok\n", 4);
        return 1;
    } else {
        write(sockfd, "ko\n", 4);
        return 0;
    }
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

int take_object(int sockfd, serv_t *serv, char *buffer)
{
    client_t *client_cpy = get_correct_client(serv, sockfd);
    if (!client_cpy->clocking) {
        update_time_limit(serv, client_cpy, 7, buffer);
        return 0;
    }
    client_cpy->clocking = false;
    map_t *map_cpy = serv->map;
    int count = 0;
    char **array = split_string_at_spaces(buffer, &count);
    char *food[7] = {"f", "l", "d",
        "s", "m", "ph", "t"};
    map_cpy = get_correct_tile(map_cpy, get_correct_client(serv, sockfd));
    for (int i = 0; i < 7; i++) {
        if (strstr(array[1], food[i]) != NULL)
            switch_case_take(i, map_cpy, client_cpy, sockfd);
    }
    return 0;
}
