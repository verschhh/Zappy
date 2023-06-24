/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** end_game.c
*/

#include "../../includes/zappy.h"

int check_level(slot_t *tmp)
{
    int count = 0;
    while (tmp->team_member->next != NULL) {
        if (tmp->team_member->player->level == 8)
            count++;
        tmp->team_member = tmp->team_member->next;
        if (count >= 6)
            return 1;
    }
    return 0;
}

int check_end_game(serv_t *serv)
{
    slot_t *slot = serv->slots;
    while (slot->next != NULL) {
        if (check_level(slot) == 1)
            return 1;
    }
    return 0;
}

int end_of_game(int sockfd, serv_t *serv, char *buffer)
{
    (void)buffer;
    char msg[10];
    int end = 0;

    update_teams(serv);
    end = check_end_game(serv);
    if (end == 0)
        return 0;
    if (serv->clients->team_name == NULL)
        return unknown_command(sockfd, serv, buffer);
    sprintf(msg, "seg %s\n", serv->clients->team_name);
    write(serv->sockfd, msg, 10);
    exit(0);
}