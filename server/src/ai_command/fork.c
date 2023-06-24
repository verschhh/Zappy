/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** fork.c
*/

#include "../../includes/zappy.h"

int fork_cmd(int sockfd, serv_t *serv, char *buffer)
{
    client_t *cpy = get_correct_client(serv, sockfd);
    slot_t *slot = serv->slots;

    if (!cpy->clocking) {
        update_time_limit(serv, cpy, 42, buffer);
        return 0;
    }
    while (slot != NULL) {
        printf("Cpy tn = %s and slot tn = %s\n", cpy->team_name, slot->team_name);
        if (strstr(cpy->team_name, slot->team_name) != NULL) {
            slot->nb += 1;
            write(sockfd, "ok\n", 4);
        }
    }
    cpy->clocking = false;
    return 0;
}