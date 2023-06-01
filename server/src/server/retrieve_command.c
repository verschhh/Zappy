/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** retrieve_command.c
*/

#include "../includes/server.h"

const cmd_t cmd_list[1] = {
};

int check_name_team(serv_t *serv, char *buffer)
{
    client_t *temp = serv->clients;
    char *copy = malloc(sizeof(char) * (strlen(buffer) + 1));

    strncpy(copy, buffer, strlen(buffer) - 1);
    copy[strlen(buffer)] = 0;
    if (temp == NULL) {
        free(temp);
        return 0;
    }
    while (temp->next != NULL) {
        if (strcmp(temp->team_name, copy) == 0) {  // Valgrind HERE
            printf("Same\n");
            free(temp);
            return 1;
        }
        temp = temp->next;
    }
    free(temp);
    return 0;
}

int receive_client_msg(int sockfd, fd_set *readfds, serv_t *serv)
{
    char buffer[1024] = {0};
    int bytes_read = recv(sockfd, buffer, sizeof(buffer), 0);
    if (bytes_read <= 0) {
        close(sockfd);
        FD_CLR(sockfd, readfds);
    } else {
        // message_t message = parse_message(buffer);
        // handle_command(message, serv, sockfd);
        check_name_team(serv, buffer);
    }
    return 0;
}
