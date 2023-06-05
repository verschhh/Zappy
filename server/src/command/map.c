/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** map.c
*/

#include "../../includes/server.h"

int map_size(int sockfd, serv_t *serv, char *buffer)
{
    printf("Hello\n");
    char msg[10];
    (void)buffer;

    sprintf(msg, "%s %d %d\n", "msz", serv->map_x, serv->map_y);
    if (write(sockfd, msg, 10) == -1)
        return 84;
    return 0;
}

int send_tile_content(map_t *map, int sockfd)
{
    char msg[32];

    sprintf(msg, "bct %d %d %d %d %d %d %d %d %d\n",
        map->x, map->y, map->food, map->linemate, map->deraumere,
            map->sibur, map->mendiane, map->phiras, map->thystame);
    if (write(sockfd, msg, 32) == -1)
        return 84;
    return 0;
}

int tile_content(int sockfd, serv_t *serv, char *buffer)
{
    int count = 0;
    int error = 0;
    char **array = splitStringAtSpaces(buffer, &count);
    int my_x = atoi(array[1]);
    int my_y = atoi(array[2]);
    map_t *temp = serv->map;

    while (temp->next != NULL) {
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
    int array[6] = {0, 0, 0, 0, 0, 0, 0};
    char msg[32];

    for (int i = 0; i != serv->map_x; i++) {
        for (int j = 0; j != serv->map_y; j++) {
            count_content_tile(array, serv->map);
            serv->map = serv->map->next;
        }
    }
    sprintf(msg, "bct %d %d %d %d %d %d %d %d %d\n",
        serv->map_x, serv->map_y, array[0], array[1], array[2],
            array[3], array[4], array[5], array[6]);
    write(sockfd, msg, 32);
}