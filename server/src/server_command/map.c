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

    pop_client(&serv->clients);
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

void count_content_tile(int *array, map_t *map)
{
    array[0] += map->food;
    array[1] += map->linemate;
    array[2] += map->deraumere;
    array[3] += map->sibur;
    array[4] += map->mendiane;
    array[5] += map->phiras;
    array[6] += map->thystame;
}

int map_content(int sockfd, serv_t *serv, char *buffer)
{
    (void) buffer;
    int array[7] = {0, 0, 0, 0, 0, 0, 0};
    char get_len[32];
    int len = snprintf(get_len, 0, "bct %d %d %d %d %d %d %d %d %d\n",
        serv->max_x, serv->max_y, array[0], array[1], array[2],
            array[3], array[4], array[5], array[6]);
    char msg[len + 15];

    for (int i = 0; i != serv->max_x; i++) {
        for (int j = 0; j != serv->max_y; j++) {
            count_content_tile(array, serv->map);
            serv->map = serv->map->next;
        }
    }
    sprintf(msg, "bct %d %d %d %d %d %d %d %d %d\n",
        serv->max_x, serv->max_y, array[0], array[1], array[2],
            array[3], array[4], array[5], array[6]);
    write(sockfd, msg, len);
    return 0;
}