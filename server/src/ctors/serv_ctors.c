/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** serv_ctors.c
*/

#include "../includes/zappy.h"

serv_t *serv_ctor2(serv_t *serv, args_t *arg)
{
    serv->nb_client = 0;
    serv->clients = NULL;
    serv->new_tick = true;
    serv->clock_start = micro_time();
    strcpy(serv->queue, "");
    serv->slots = slot_ctor(arg);
    // for (int i = 1; arg->names[i] != NULL; i++)
    //     new_slot(serv->slots, arg->names[i]);
    return serv;
}

serv_t *serv_ctor(args_t *arg)
{
    serv_t *serv = malloc(sizeof(serv_t));
    serv->addr.sin_family = AF_INET;
    serv->addr.sin_port = htons(arg->port);
    serv->addr.sin_addr.s_addr = INADDR_ANY;
    if ((serv->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        print_and_exit("ERROR opening socket");
    if (bind(serv->sockfd, (struct sockaddr*)&serv->addr,
            sizeof(serv->addr)) < 0)
        print_and_exit("ERROR on binding");
    if (listen(serv->sockfd, 16) < 0)
        print_and_exit("ERROR on listen");
    serv->max_x = arg->width;
    serv->max_y = arg->height;
    serv->map = create_map(arg);
    spawn_ressources(serv);
    serv->freq = arg->freq;
    serv = serv_ctor2(serv, arg);
    return serv;
}
