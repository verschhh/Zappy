/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** map.c
*/

#include "../../includes/zappy.h"

int map_size(int sockfd, serv_t *serv, char *buffer)
{
    char get_len[0];
    (void)buffer;
    int len = snprintf(get_len, 0, "msz %d %d\n", serv->max_x, serv->max_y);
    char msg[len + 1];

    // pop_client(&serv->clients);
    serv->start = clock();
    sprintf(msg, "%s %d %d\n", "msz", serv->max_x, serv->max_y);
    if (write(sockfd, msg, len) == -1)
        return 84;
    return 0;
}

int send_tile_content(map_t *map, int sockfd)
{
    char get_len[0];
    int len = snprintf(get_len, 0, "bct %d %d %d %d %d %d %d %d %d\n",
        map->x, map->y, map->food, map->linemate, map->deraumere,
            map->sibur, map->mendiane, map->phiras, map->thystame);
    char msg[len + 1];

    sprintf(msg, "bct %d %d %d %d %d %d %d %d %d\n",
        map->x, map->y, map->food, map->linemate, map->deraumere,
            map->sibur, map->mendiane, map->phiras, map->thystame);
    if (write(sockfd, msg, len + 1) == -1)
        return 84;
    return 0;
}

int tile_content(int sockfd, serv_t *serv, char *buffer)
{
    int count = 0;
    int error = 0;
    char **array = split_string_at_spaces(buffer, &count);
    int my_x = atoi(array[1]);
    int my_y = atoi(array[2]);
    map_t *temp = serv->map;

    while (temp != NULL) {
        if (temp->x == my_x && temp->y == my_y) {
            error = send_tile_content(temp, sockfd);
            return error;
        }
        temp = temp->next;
    }
    return 0;
}

int map_content(int sockfd, serv_t *serv, char *buffer)
{
    (void) buffer;
    char msg[5000] = "";
    map_t *map = serv->map;

    while (map != NULL) {
        sprintf(msg + strlen(msg), "bct %d %d %d %d %d %d %d %d %d\n",
        map->x, map->y, map->food, map->linemate, map->deraumere,
            map->sibur, map->mendiane, map->phiras, map->thystame);
        map = map->next;
    }
    write(sockfd, msg, strlen(msg));
    return 0;
}