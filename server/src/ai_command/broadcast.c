/*
** EPITECH PROJECT, 2023
** Zappy2
** File description:
** broadcast
*/

#include "../../includes/zappy.h"

int sound(player_t *start, player_t *goal)
{
    return (1);
}

int broadcast(int sockfd, serv_t *serv, char *buffer)
{
    client_t *client = serv->clients;
    client_t *actual_client = get_correct_client(serv, sockfd);
    printf(buffer);
    char msg[0];
    buffer += 9;
    int len = snprintf(msg,0,"message %d,%s", sound(client->player, client->player), buffer);
    char send[len];
    printf(buffer);
    if ((7 / serv->freq) > 0 && client->tickleft <= 0 && !client->is_ticking) {
        client->tickleft = 7 / serv->freq;
        client->cpy_buffer = strdup(buffer);
        client->is_ticking = true;
        return 0;
    }
    if (client->is_ticking) {
        for (int i = 0; client->next != NULL; i++) {
            if (client->sockfd != sockfd) {
                sprintf(send,"message %d,%s", sound(client->player, client->player), buffer);
                printf(send);
                write(client->sockfd, send, len);
            }
            client = client->next;
        }
    }
    
}