/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** check_group_name.c
*/

#include "../../includes/zappy.h"

int check_slot_team(int slot)
{
    if (slot == 0)
        return FULL;
    return NOT_FULL;
}

int compare_team_name_buffer(slot_t *slot, char *copy)
{
    if (strstr(copy, slot->team_name) != NULL) {
        if (check_slot_team(slot->nb) == FULL)
            return -1;
        slot->nb -= 1;
        return slot->nb;
    }
    return 84;
}

int check_name_team(serv_t *serv, char *buffer)
{
    char *copy = malloc(sizeof(char) * (strlen(buffer) + 1));
    slot_t *temp = serv->slots;
    int slot = 0;

    strncpy(copy, buffer, strlen(buffer) - 1);
    copy[strlen(buffer) - 1] = 0;
    while (temp != NULL) {
        slot = compare_team_name_buffer(temp, copy);
        if (slot != 84) {
            free(copy);
            return slot;
        }
        temp = temp->next;
    }
    free(copy);
    return -1;
}

void send_x_y_ai(int sockfd, serv_t *serv, int slot)
{
    char msg[14];

    sprintf(msg, "%d\n %d %d\n", slot, serv->max_x, serv->max_y);
    write(sockfd, msg, strlen(msg));
}
