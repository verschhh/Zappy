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
    char msg[2];

    while (slot->next != NULL) {
        if (strcmp(slot->team_member, cpy->team_name) == 0) {
            sprintf(msg, "%d\n", slot->nb);
            write(sockfd, msg, 2);
        }
        slot = slot->next;
    }
    return 0;
}