/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** accept_client.c
*/

#include "../includes/server.h"

void get_group_name()
{
    // next = check_name_team(serv, buffer);
    // if (next != 0)
    //     send_x_y_ai(sockfd, serv, send_nb_slot_ai(next));
}

void accept_new_client(fd_set *readfds, serv_t *serv)
{
    client_t *client = client_ctor(serv->clients);
    if (client == NULL)
        return;
    client->sockfd = accept(serv->sockfd,
        (struct sockaddr *)&client->addr, &client->addrlen);
    inet_ntoa(client->addr.sin_addr);
    int temp = ntohs(client->addr.sin_port);
    (void)temp;
    printf("New connection, socket fd is %d, ip is : %s, port : %d\n",
        client->sockfd, inet_ntoa(client->addr.sin_addr), temp);
    FD_SET(client->sockfd, readfds);
    if (client->sockfd > serv->max_sd)
        serv->max_sd = client->sockfd;
    write(client->sockfd, "Welcome, you are now connected", 31);
    get_group_name();
}
