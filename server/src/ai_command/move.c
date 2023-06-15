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

    if (can_move != 0)
        return 84;
    move_to_orientation(serv, cpy);
    write(sockfd, "ok", 3);
    return 0;
}

int left(int sockfd, serv_t *serv, char *buffer)
{
    (void)buffer;
    int can_move = check_time_limit(serv, sockfd);
    client_t *cpy = get_correct_client(serv, sockfd);

    if (can_move != 0)
        return 84;
    cpy->player->orientation -= 1;
    if (cpy->player->orientation < NORTH)
        cpy->player->orientation = WEST;
    write(sockfd, "ok", 3);
    return 0;
}

int right(int sockfd, serv_t *serv, char *buffer)
{
    (void)buffer;
    int can_move = check_time_limit(serv, sockfd);
    client_t *cpy = get_correct_client(serv, sockfd);

    if (can_move != 0)
        return 84;
    cpy->player->orientation += 1;
    if (cpy->player->orientation > WEST)
        cpy->player->orientation = NORTH;
    write(sockfd, "ok", 3);
    return 0;
}