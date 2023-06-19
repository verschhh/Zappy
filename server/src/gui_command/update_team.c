/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** update_team.c
*/

#include "../../includes/zappy.h"

void update_teams(serv_t *serv)
{
    slot_t *tmp = serv->slots;
    client_t *tmp2 = serv->clients;

    while (tmp->next != NULL) {
        if (tmp->team_member != NULL)
            continue;
        if (strcmp(tmp->team_name, tmp2->team_name) == 0) {
            tmp->team_member = tmp2;
            tmp->team_member = tmp2->next;
        }
        tmp2 = tmp2->next;
        tmp = tmp->next;
    }
    return;
}