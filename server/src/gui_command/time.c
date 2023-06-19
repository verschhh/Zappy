/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** time.c
*/

#include "../../includes/zappy.h"

int send_unit_time(int sockfd, serv_t *serv, char *buffer)
{
    char msg[6];
    (void) serv;
    (void) buffer;

    sprintf(msg, "%s %d", "sgt", serv->freq);
    write(sockfd, msg, 6);
    return 0;
}

int modify_unit_time(int sockfd, serv_t *serv, char *buffer)
{
    int count = 0;
    char msg[9];
    char **array = split_string_at_spaces(buffer, &count);
    int time = atoi(array[1]);

    serv->freq = time;
    sprintf(msg, "sst %d\n", time);
    write(sockfd, msg, 9);
    return 0;
}