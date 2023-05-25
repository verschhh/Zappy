/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** serv_ctors.c
*/

#include "../includes/server.h"

serv_t *serv_ctor(args_t *arg)
{
    serv_t *serv = malloc(sizeof(serv_t));

    serv->portno = arg->port;
    serv->addr.sin_family = AF_INET;
    serv->addr.sin_port = htons(serv->portno);
    serv->addr.sin_addr.s_addr = INADDR_ANY;
    if ((serv->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        print_and_exit("ERROR opening socket");
    if (bind(serv->sockfd, (struct sockaddr*)&serv->addr,
            sizeof(serv->addr)) < 0)
        print_and_exit("ERROR on binding");
    if (listen(serv->sockfd, 16) < 0)
        print_and_exit("ERROR on listen");
    serv->clients = root_client_ctor();
    serv->global_uid = 1;
    return serv;
}
