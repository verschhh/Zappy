/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** look.c
*/

#include "../../includes/zappy.h"

int check_if_unboud(int value, int max)
{
    if (value >= max)
        value -= max;
    if (value < 0)
        value = max + value;
    return value;
}

char *assign_new_size(serv_t *serv, char *response, map_t *map)
{
    int array[7] = {map->food, map->linemate, map->deraumere, map->sibur,
        map->mendiane, map->phiras, map->thystame};
    for (int i = 0; i != 7; i++)
        printf("%d\n", array[i]);
}

map_t *get_position_map(serv_t *serv, client_t *client, int len, int index)
{
    map_t *map = serv->map;
    int check_div_zero = len - 1;
    int get_y = 0;
    int get_x = 0;
    int mean = 0;

    if (check_div_zero <= 0) {
        get_y = client->player->y;
        get_x = client->player->x;
    } else {
        get_y = client->player->y + check_div_zero / 2;
        mean = (len - 1) / 2;
        for (int i = -mean; i != mean; i++) {
            if (mean + i == index)
                get_x = client->player->x + i;
        }
    }
    get_x = check_if_unboud(get_x, serv->max_x);
    get_y = check_if_unboud(get_y, serv->max_y);
    printf("x = %d and y = %d\n", get_x, get_y);
    while (map->next != NULL) {
        if (map->y == get_y && map->x == get_x)
            return map;
        map = map->next;
    }
    printf("HHERE\n");
    return NULL;
}

void look_north(serv_t *serv, client_t *client, int socket)
{
    printf("IN\n");
    int index = client->player->level;
    printf("lvl = %d\n", index);
    char *response = malloc(sizeof(char) * strlen("[player,") + 1);
    int len = 1;

    while (index >= 0) {
        printf("LOOP\n");
        for (int i = 0; i != len; i++) {
            response = assign_new_size(serv, response, get_position_map(serv, client, len, i));
        }
        if (len + 2 > serv->max_x)
            len -= 2;
        index--;
    }
    printf("END\n");
}

int look(int sockfd, serv_t *serv, char *buffer)
{
    (void)buffer;
    printf("Bye\n");
    serv_t *cpy_serv = serv;
    client_t *cpy_clt = get_correct_client(serv, sockfd);
    printf("Hello\n");

    if (cpy_clt == NULL)
        return 84;
    printf("orientation = %d\n", cpy_clt->player->orientation);
    if (cpy_clt->player->orientation == NORTH)
        look_north(serv, cpy_clt, socket);
    if (cpy_clt->player->orientation == EAST)
        return;
    if (cpy_clt->player->orientation == SOUTH)
        return;
    if (cpy_clt->player->orientation == WEST)
        return;
}