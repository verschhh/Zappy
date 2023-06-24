/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** time.c
*/

#include "../includes/zappy.h"

uint64_t micro_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * (uint64_t)1000000 + tv.tv_usec;
}

void update_time_limit(serv_t *serv, client_t *client, int time_limit, char *s)
{
    client->limit = ((float) time_limit) / ((float) serv->freq);
    client->cpy_buffer = strdup(s);
    client->clock = micro_time();
    client->clocking = true;
    return;
}
