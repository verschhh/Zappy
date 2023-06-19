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
    int can_move = check_time_limit(serv, sockfd);
    client_t *cpy = get_correct_client(serv, sockfd);

    if ((7 / serv->freq) > 0 && cpy->tickleft <= 0 && !cpy->is_ticking) {
        cpy->tickleft = 7 / serv->freq;
        cpy->cpy_buffer = strdup(buffer);
        cpy->is_ticking = true;
        return 0;
    }
    if (can_move != 0)
        return 84;
    if (cpy->is_ticking) {
        move_to_orientation(serv, cpy);
        write(sockfd, "ok\n", 4);
        cpy->is_ticking = false;
    }
    return 0;
}

int left(int sockfd, serv_t *serv, char *buffer)
{
    (void)buffer;
    int can_move = check_time_limit(serv, sockfd);
    client_t *cpy = get_correct_client(serv, sockfd);

    if ((7 / serv->freq) > 0 && cpy->tickleft <= 0 && !cpy->is_ticking) {
        cpy->tickleft = 7 / serv->freq;
        cpy->cpy_buffer = strdup(buffer);
        cpy->is_ticking = true;
        return 0;
    }
    if (can_move != 0)
        return 84;
    if (cpy->is_ticking) {
        cpy->player->orientation -= 1;
        if (cpy->player->orientation < NORTH)
            cpy->player->orientation = WEST;
        write(sockfd, "ok\n", 4);
        cpy->is_ticking = false;
    }
    return 0;
}

int right(int sockfd, serv_t *serv, char *buffer)
{
    (void)buffer;
    int can_move = check_time_limit(serv, sockfd);
    client_t *cpy = get_correct_client(serv, sockfd);

    if ((7 / serv->freq) > 0 && cpy->tickleft <= 0 && !cpy->is_ticking) {
        cpy->tickleft = 7 / serv->freq;
        cpy->cpy_buffer = strdup(buffer);
        cpy->is_ticking = true;
        return 0;
    }
    if (can_move != 0)
        return 84;
    if (cpy->is_ticking) {
        cpy->player->orientation += 1;
        if (cpy->player->orientation > WEST)
            cpy->player->orientation = NORTH;
        write(sockfd, "ok\n", 4);
        cpy->is_ticking = false;
    }
    return 0;
}

char *get_inv(inv_t *inv)
{
    char msg[1024];
    char tmp[1024];
    int len = 0;
    char *buf = NULL;
    sprintf(tmp, "food %d, linemate %d, deraumere %d, ", inv->food,
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
    (void) buffer;
    client_t *cpy = get_correct_client(serv, sockfd);
    inv_t *tmp = cpy->player->inventory;
    char *msg = get_inv(tmp);
    int len = strlen(msg);

    cpy->tickleft = 1;
    if (write(sockfd, msg, len) == -1)
        return 84;
    return 0;
}