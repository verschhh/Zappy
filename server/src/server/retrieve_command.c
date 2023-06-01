/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** retrieve_command.c
*/

#include "../includes/server.h"

const cmd_t cmd_list[1] = {
};

int check_slot_team(client_t *temp)
{
    if (temp->slot == 0)
        return FULL;
    return NOT_FULL;
}

int compare_team_name_buffer(client_t *temp, char *copy)
{
    if (strcmp(temp->team_name, copy) == 0) {  // Valgrind HERE
        if (!check_slot_team(temp))
            return -1;
        return temp->slot;
    }
    return CONTINUE;
}

int check_name_team(serv_t *serv, char *buffer)
{
    client_t *temp = serv->clients;
    char *copy = malloc(sizeof(char) * (strlen(buffer) + 1));
    int slot = 0;

    strncpy(copy, buffer, strlen(buffer) - 1);
    copy[strlen(buffer)] = 0;
    if (temp == NULL) {
        free(temp);
        return 0;
    }
    while (temp->next != NULL) {
        slot = compare_team_name_buffer(temp, copy);
        if (slot == -1)
            return 0;
        else if (slot != CONTINUE)
            return slot;
        temp = temp->next;
    }
    free(temp);
    return 0;
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

void send_x_y_ai(int sockfd, serv_t *serv, char *number)
{
    char *result = malloc(sizeof(char) * strlen(number) + 8);
    char size_map[8];

    strcpy(result, number);
    sprintf(size_map, "%d %d\n", serv->map_x, serv->map_y);
    strcat(result, size_map);
    result[strlen(result) + strlen(number) - 1] = 0;
    write(sockfd, result, strlen(result));
    free(result);
}

int receive_client_msg(int sockfd, fd_set *readfds, serv_t *serv)
{
    char buffer[1024] = {0};
    int next = 0;
    int bytes_read = recv(sockfd, buffer, sizeof(buffer), 0);
    if (bytes_read <= 0) {
        close(sockfd);
        FD_CLR(sockfd, readfds);
    } else {
        next = check_name_team(serv, buffer);
        if (next != 0)
            send_x_y_ai(sockfd, serv, send_nb_slot_ai(next));
    }
    return 0;
}
