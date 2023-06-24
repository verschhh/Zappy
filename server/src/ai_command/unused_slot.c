/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** unused_slot.c
*/

#include "../../includes/zappy.h"

int unused_slot(int sockfd, serv_t *serv, char *buffer)
{
    (void)buffer;
    client_t *cpy = get_correct_client(serv, sockfd);
    slot_t *slot = serv->slots;
    char msg[0];
    int len = 0;

    while (slot != NULL) {
        if (strstr(cpy->team_name, slot->team_name) != NULL) {
            len = snprintf(msg, 0, "%d\n", slot->nb);
            char send[len];
            sprintf(send, "%d\n", slot->nb);
            write(sockfd, send, len);
        }
        slot = slot->next;
    }
    return 0;
}
