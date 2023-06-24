/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** set.c
*/

#include "../../includes/zappy.h"

int check_inventory_material(int materials, int sockfd)
{
    if (materials > 0) {
        write(sockfd, "ok\n", 4);
        return 1;
    } else {
        write(sockfd, "ko\n", 4);
        return 0;
    }
}

int set_object(int sockfd, serv_t *serv, char *buffer)
{
    client_t *client_cpy = get_correct_client(serv, sockfd);
    int count = 0;

    if (!client_cpy->clocking) {
        update_time_limit(serv, client_cpy, 7, buffer);
        return 0;
    }
    client_cpy->clocking = false;
    map_t *map_cpy = serv->map;
    char **array = split_string_at_spaces(buffer, &count);
    char *food[7] = {"food", "linemate", "deraumere",
        "sibur", "mendiane", "phiras", "thystame"};
    map_cpy = get_correct_tile(map_cpy, get_correct_client(serv, sockfd));
    for (int i = 0; i < 7; i++) {
        if (strstr(array[1], food[i]) != NULL) {
            switch_case_set(i, map_cpy, client_cpy, sockfd);
        }
    }
    return 0;
}
