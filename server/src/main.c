/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** main.c
*/

#include "../includes/server.h"

void err_n_die(const char *string)
{
    printf("%s\n", string);
    exit (84);
}

void usage(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb\n");
    printf("-f freq\n");
    printf("\tport\tis the port number\n");
    printf("\twidth\tis the width of the world\n");
    printf("\theight\tis the height of the world\n");
    printf("\tnameX\tis the name of the team X\n");
    printf("\tclientsNb\tis the number of authorized clients per team\n");
    printf("\tfreq\tis the reciprocal of time unit for execution of actions\n");
}

int retrieve_command(int sockfd, fd_set *readfds, serv_t *serv)
{
    // char buffer[1024] = {0};
    // int bytes_read = recv(sockfd, buffer, sizeof(buffer), 0);
    // if (bytes_read <= 0) {
    //     close(sockfd);
    //     FD_CLR(sockfd, readfds);
    // } else {
    //     message_t message = parse_message(buffer);
    //     handle_command(message, serv, sockfd);
    // }
    return 0;
}

void accept_new_client(fd_set *readfds, serv_t *serv)
{
    client_t *client = client_ctor(serv->clients);
    client->sockfd = accept(serv->sockfd,
        (struct sockaddr *)&client->addr, &client->addrlen);
    inet_ntoa(client->addr.sin_addr);
    int temp = ntohs(client->addr.sin_port);
    (void)temp;
    FD_SET(client->sockfd, readfds);
    if (client->sockfd > serv->max_sd)
        serv->max_sd = client->sockfd;
}

int start_server(fd_set *readfds, serv_t *serv)
{
    fd_set tmpfds;
    tmpfds = *readfds;

    if (select(serv->max_sd + 1, &tmpfds, NULL, NULL, NULL) < 0)
        err_n_die("ERROR on select");

    for (int i = 0; i <= serv->max_sd; i++) {
        if (!FD_ISSET(i, &tmpfds)) {
            continue;
        }
        if (i == serv->sockfd) {
            accept_new_client(readfds, serv);
        } else {
            retrieve_command(i, readfds, serv);
        }
    }

    printf("port: %d, width: %d, height: %d, clientsNb: %d, freq: %.2f\n",
    args->port, args->width, args->height, args->clientsNb, args->freq);

    printf("Count: %d\n", args->namesCount);

    for (int i = 0; i < args->namesCount; i++) {
        printf("Name %d: %s\n", i + 1, args->names[i]);
    }
}

int body(args_t *args)
{
    serv_t *serv = serv_ctor(args);
    fd_set readfds;
    if (serv == NULL) {
        free(args);
        return 84;
    }
    FD_SET(serv->sockfd, &readfds);
    serv->max_sd = serv->sockfd;
    while (1)
        start_server(&readfds, serv);
    free(args);
    return 0;
}

int main(int ac, char **av)
{
    args_t *args = malloc(sizeof(args_t));
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        usage();
        free(args);
        return 0;
    }
    if (parse_arguments(ac, av, args) == 84) {
        free(args);
        return 84;
    }
    body(args);
}
