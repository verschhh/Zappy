/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** move.c
*/

#include "../../includes/zappy.h"

void check_off_map(serv_t *serv, player_t *player)
{
    if (player->x >= serv->max_x)
        player->x = 0;
    if (player->x < 0)
        player->x = serv->max_x - 1;
    if (player->y >= serv->max_y)
        player->y = 0;
    if (player->y < 0)
        player->y = serv->max_y - 1;
}

void move_to_orientation(serv_t *serv, client_t *client)
{
    if (client->player->orientation == NORTH)
        client->player->y -= 1;
    if (client->player->orientation == SOUTH)
        client->player->y += 1;
    if (client->player->orientation == WEST)
        client->player->x -= 1;
    if (client->player->orientation == EAST)
        client->player->x += 1;
    check_off_map(serv, client->player);
}

int forward(int sockfd, serv_t *serv, char *buffer)
{
    (void)buffer;
    client_t *cpy = get_correct_client(serv, sockfd);

    if (!cpy->clocking) {
        update_time_limit(serv, cpy, 7, buffer);
        return 0;
    }
    if (cpy->clocking) {
        move_to_orientation(serv, cpy);
        write(sockfd, "ok\n", 4);
        cpy->clocking = false;
    }
    return 0;
}

int left(int sockfd, serv_t *serv, char *buffer)
{
    (void)buffer;
    client_t *cpy = get_correct_client(serv, sockfd);

    if (!cpy->clocking) {
        update_time_limit(serv, cpy, 7, buffer);
        return 0;
    }
    if (cpy->clocking) {
        cpy->player->orientation -= 1;
        if (cpy->player->orientation < NORTH)
            cpy->player->orientation = WEST;
        write(sockfd, "ok\n", 4);
        cpy->clocking = false;
    }
    return 0;
}

int right(int sockfd, serv_t *serv, char *buffer)
{
    (void)buffer;
    client_t *cpy = get_correct_client(serv, sockfd);

    if (!cpy->clocking) {
        update_time_limit(serv, cpy, 7, buffer);
        return 0;
    }
    if (cpy->clocking) {
        cpy->player->orientation += 1;
        if (cpy->player->orientation > WEST)
            cpy->player->orientation = NORTH;
        write(sockfd, "ok\n", 4);
        cpy->clocking = false;
    }
    return 0;
}

char *get_inv(inv_t *inv)
{
    char msg[1024];
    char tmp[1024];
    int len = 0;
    char *buf = NULL;
    sprintf(msg, "food %d, linemate %d, deraumere %d, ", inv->food,
        inv->linemate, inv->deraumere);
    sprintf(tmp, "sibur %d, mendiane %d, phiras %d, thystame %d\n",
        inv->sibur, inv->mendiane, inv->phiras, inv->thystame);
    strcat(msg, tmp);
    len = strlen(msg);
    buf = malloc(sizeof(char) * (len + 1));
    strcpy(buf, msg);
    return buf;
}

int inventory(int sockfd, serv_t *serv, char *buffer)
{
    client_t *cpy = get_correct_client(serv, sockfd);

    if (!cpy->clocking) {
        update_time_limit(serv, cpy, 1, buffer);
        return 0;
    }
    inv_t *tmp = cpy->player->inventory;
    char *msg = get_inv(tmp);
    printf("%s", msg);
    int len = strlen(msg);
    if (cpy->clocking) {
        if (write(sockfd, msg, len + 1) == -1)
            return 84;
    }
    cpy->clocking = false;
    return 0;
}