/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** serv_ctors.c
*/

#include "../includes/zappy.h"

// char **get_tn_serv(char **names, char **arg_names)
// {
//     int len = 0;

//     for (int i = 0; arg_names[i] != NULL; i++)
//         len++;
//     names = malloc(sizeof(char *) * (len + 1));
//     for (int i = 0; i != len; i++) {
//         names[i] = malloc(sizeof(char) * strlen(arg_names[i]) + 1);
//         strcpy(names[i], arg_names[i]);
//         names[i][strlen(arg_names[i])] = '\0';
//     }
//     names[len] = NULL;
//     return names;
// }

void serv_ctor2(serv_t *serv, args_t *arg)
{
    serv->nb_client = 0;
    serv->clients = NULL;
    serv->slots = slot_ctor(arg);
    for (int i = 1; arg->names[i] != NULL; i++)
        new_slot(serv->slots, arg->names[i]);
    return;
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
    serv->freq = arg->freq;
    serv_ctor2(serv, arg);
    return serv;
}
