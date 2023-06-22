/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** map.c
*/

#include "../../includes/zappy.h"

static const double FOOD_DENSITY = 0.5;
static const double LINEMATE_DENSITY = 0.3;
static const double DERAUMERE_DENSITY = 0.15;
static const double SIBUR_DENSITY = 0.1;
static const double MENDIANE_DENSITY = 0.1;
static const double PHIRAS_DENSITY = 0.08;
static const double THYSTAME_DENSITY = 0.05;

int map_size(int sockfd, serv_t *serv, char *buffer)
{
    char get_len[0];
    (void)buffer;
    int len = snprintf(get_len, 0, "msz %d %d\n", serv->max_x, serv->max_y);
    char msg[len + 1];

    sprintf(msg, "msz %d %d\n", serv->max_x, serv->max_y);
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
    char msg[25000] = "";
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

// TODO: change to a set number of ressources distributed randomly
void spawn_ressources(serv_t *serv)
{
    int tot_rss = 0;
    srand(time(NULL)); // Seed the random number generator
    map_t *current = serv->map;
    while (current != NULL) {
        tot_rss += current->food + current->linemate + current->deraumere +
            current->sibur + current->mendiane + current->phiras +
            current->thystame;
        if (tot_rss >= 420) {
            current = current->next;
            continue;
        }
        if (rand()< (RAND_MAX * FOOD_DENSITY))
            current->food += 1;
        if (rand()< (RAND_MAX * LINEMATE_DENSITY))
            current->linemate += 1;
        if (rand()< (RAND_MAX * DERAUMERE_DENSITY))
            current->deraumere += 1;
        if (rand()< (RAND_MAX * SIBUR_DENSITY))
            current->sibur += 1;
        if (rand()< (RAND_MAX * MENDIANE_DENSITY))
            current->mendiane += 1;
        if (rand()< (RAND_MAX * PHIRAS_DENSITY))
            current->phiras += 1;
        if (rand()< (RAND_MAX * THYSTAME_DENSITY))
            current->thystame += 1;
        current = current->next;
    }
}