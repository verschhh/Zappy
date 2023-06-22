/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** clock.c
*/

#include "../../includes/zappy.h"


void decrement_tick(serv_t *serv)
{
    client_t *copy = serv->clients;
    double elapsed = 0;
    while (copy != NULL) {
        elapsed = ((double) micro_time() - copy->clock ) / 1000000.0;
        if (copy->clocking && elapsed >= copy->limit) {
            lauch_cmd(parse_command(copy->cpy_buffer), copy->sockfd, serv,
            copy->cpy_buffer);
            copy->cpy_buffer = NULL;
        }
        copy = copy->next;
    }
    return;
}

void spawn_rss(serv_t *serv)
{
    double rss = ((double) micro_time() - serv->rss_clock) / 1000000.0;
    if (rss >= (20 / serv->freq)) {
        
        spawn_ressources(serv);
        serv->rss_clock = micro_time();
    }
    return;
}

void decrease_food(serv_t *serv)
{
    client_t *copy = serv->clients;
    double elapsed = 0;
    while (copy != NULL) {
        elapsed = ((double) micro_time() - copy->dec_food_clock ) / 1000000.0;
        if (elapsed >= (126 / serv->freq)) {
            copy->dec_food_clock = micro_time();
            copy->player->inventory->food -= 1;
        }
        copy = copy->next;
    }
    return;
}

void clock_action(serv_t *serv)
{
    decrement_tick(serv);
    spawn_rss(serv);
    decrease_food(serv);
}