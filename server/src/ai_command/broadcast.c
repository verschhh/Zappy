/*
** EPITECH PROJECT, 2023
** Zappy2
** File description:
** broadcast
*/

#include "../../includes/zappy.h"

int sound(player_t *start, player_t *goal)
{
   int orientation = get_facing(start, goal);
   if (orientation == 0)
       return 0;
    if (goal->orientation == EAST)
        orientation += 6;
    if (goal->orientation == SOUTH)
        orientation += 4;
    if (goal->orientation == WEST)
        orientation += 2;
    if (orientation > 8)
        orientation -= 8;
    return (orientation);
}

void print_broadcast(client_t *client, client_t *actual_client, int sockfd, char *buffer)
{
    char msg[0];
    int len = snprintf(msg, 0, "message 8,%s", buffer);
    char send[len];
    for (; client != NULL; client = client->next) {
        if (client->sockfd != sockfd) {
            sprintf(send, "message %d,%s\n",
                sound(actual_client->player, client->player), buffer);
            printf(send);
            write(client->sockfd, send, len);
        }
    }
    write(sockfd, "ok\n", 3);
}

int broadcast(int sockfd, serv_t *serv, char *buffer)
{
    client_t *client;
    client_t *actual_client = get_correct_client(serv, sockfd);

    if (!actual_client->clocking) {
        update_time_limit(serv, actual_client, 7, buffer);
        return 0;
    }
    if (actual_client->clocking) {
        char msg[0];
        buffer += 9;
        client = serv->clients;
        print_broadcast(client, actual_client, sockfd, buffer);
        actual_client->clocking = false;
    }
    return (0);
}