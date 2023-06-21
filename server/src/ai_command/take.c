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
    }
    else {
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

void switch_case_take_two(int i, map_t *map_cpy, client_t *client_cpy, int sockfd)
{
    switch (i) {
        case 3:
            if (check_element_tile(map_cpy->sibur, sockfd) == 1)
                map_cpy->sibur--;
                client_cpy->player->inventory->sibur++;
            break;
        case 4:
            if (check_element_tile(map_cpy->mendiane, sockfd) == 1)
                map_cpy->mendiane--;
                client_cpy->player->inventory->mendiane++;
            break;
        case 5:
            if (check_element_tile(map_cpy->phiras, sockfd) == 1)
                map_cpy->phiras--;
                client_cpy->player->inventory->phiras++;
            break;
        case 6:
            if (check_element_tile(map_cpy->thystame, sockfd) == 1)
                map_cpy->thystame--;
                client_cpy->player->inventory->thystame++;
            break;
    }
}

void switch_case_take(int i, map_t *map_cpy, client_t *client_cpy, int sockfd)
{
    switch (i) {
        case 0:
            if (check_element_tile(map_cpy->food, sockfd) == 1)
                map_cpy->food--;
                client_cpy->player->inventory->food++;
            break;
        case 1:
            if (check_element_tile(map_cpy->linemate, sockfd) == 1)
                map_cpy->linemate--;
                client_cpy->player->inventory->linemate++;
            break;
        case 2:
            if (check_element_tile(map_cpy->deraumere, sockfd) == 1)
                map_cpy->deraumere--;
                client_cpy->player->inventory->deraumere++;
            break;
        default:
            switch_case_take_two(i, map_cpy, client_cpy, sockfd);
            break;
    }
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
    char *food[7] = {"food", "linemate", "deraumere",
        "sibur", "mendiane", "phiras", "thystame"};
    map_cpy = get_correct_tile(map_cpy, get_correct_client(serv, sockfd));

    printf("Position = %d %d\n", map_cpy->x, map_cpy->y);
    for (int i = 0; i < 7; i++) {
        if (strstr(array[1], food[i]) != NULL) {
            switch_case_take(i, map_cpy, client_cpy, sockfd);
        }
    }
    return 0;
}