/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** map.c
*/

#include "../../includes/server.h"

int map_size(int sockfd, serv_t *serv, char *buffer)
{
    char msg[11];
    (void)buffer;

    sprintf(msg, "%s %d %d\n", "msz", serv->map_x, serv->map_y);
    if (write(sockfd, msg, 11) == -1)
        return 84;
    return 0;
}

int send_tile_content(map_t *map, int sockfd)
{
    char msg[28];

    sprintf(msg, "%d %d %d %d %d %d %d %d %d\n",
        map->x, map->y, map->food, map->linemate, map->deraumere,
            map->sibur, map->mendiane, map->phiras, map->thystame);
    if (write(sockfd, msg, 28) == -1)
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