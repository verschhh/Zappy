/*
** EPITECH PROJECT, 2023
** Zappy2
** File description:
** broadcast
*/

#include "../../includes/zappy.h"

int sound(player_t *start, player_t *goal)
{
    int x_res = goal->x - start->x;
    int y_res = goal->y - start->y;
    int orientation = 0;
    if (x_res > 0) {
        if (y_res > 0) {
            orientation = 8;
        }
        if (y_res == 0) {
            orientation = 7;
        }
        if (y_res < 0) {
            orientation = 6;
        }
    } else if (x_res == 0) {
        if (y_res > 0) {
            orientation = 1;
        }
        if (y_res < 0) {
            orientation = 5;
        }
    } else {
        if (y_res > 0) {
            orientation = 2;
        }
        if (y_res == 0) {
            orientation = 3;
        }
        if (y_res < 0) {
            orientation = 4;
        }
    }
    if (orientation == 0)
        return 0;
    if (goal->orientation == EAST)
        orientation += 8;
    if (goal->orientation == SOUTH)
        orientation += 4;
    if (goal->orientation == WEST)
        orientation += 2;

    if (goal->orientation > 8)
        orientation -= 8;

    return (orientation);
}

int broadcast(int sockfd, serv_t *serv, char *buffer)
{
    client_t *client = serv->clients;
    client_t *actual_client = get_correct_client(serv, sockfd);

    if (!client->clocking) {
        update_time_limit(serv, client, 7, buffer);
        return 0;
    }
    if (client->clocking) {
        char msg[0];
        buffer += 9;
        int len = snprintf(msg,0,"message %d,%s", sound(client->player, client->player), buffer);
        char send[len];

        for (int i = 0; client != NULL; i++) {
            if (client->sockfd != sockfd) {
                sprintf(send,"message %d,%s\n", sound(actual_client->player, client->player), buffer);
                write(client->sockfd, send, len);
                break;
            }
            client = client->next;
        }
        actual_client->clocking = false;
        write(sockfd, "ok\n", 3);
    }
    return (0);
}