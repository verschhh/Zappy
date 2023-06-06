/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** check_group_name.c
*/

#include "../../includes/zappy.h"


int check_slot_team(client_t *temp)
{
    if (temp->slot == 0)
        return FULL;
    return NOT_FULL;
}

int compare_team_name_buffer(char *name, char *copy)
{
    if (strcmp(name, copy) == 0) {  // Valgrind HERE
        if (!check_slot_team(temp))
            return -1;
        return temp->slot;
    }
    return CONTINUE;
}

char *send_nb_slot_ai(int slot)
{
    char *number = malloc(sizeof(char) * 5);

    if (slot != 0)
        sprintf(number, "%d\n", slot);
    else
        sprintf(number, "%s\n", "KO");
    return number;
}

int check_name_team(serv_t *serv, char *buffer)
{
    char *copy = malloc(sizeof(char) * (strlen(buffer) + 1));
    int slot = 0;

    strncpy(copy, buffer, strlen(buffer) - 1);
    copy[strlen(buffer)] = 0;
    if (temp == NULL) {
        return 0;
    }
    for (int i = 0; serv->names[i] != NULL, i++) {
        slot = compare_team_name_buffer(serv->names[i], copy);
        if (slot == -1)
            return 0;
        else if (slot != CONTINUE)
            return slot;
    }
    return 0;
}

void send_x_y_ai(int sockfd, serv_t *serv, char *number)
{
    char *result = malloc(sizeof(char) * strlen(number) + 8);
    char size_map[8];

    strcpy(result, number);
    sprintf(size_map, "%d %d\n", serv->max_x, serv->max_y);
    strcat(result, size_map);
    result[strlen(result) + strlen(number) - 1] = 0;
    write(sockfd, result, strlen(result));
    free(result);
}
