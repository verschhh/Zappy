/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** player.c
*/

#include "../../includes/zappy.h"

int send_player_position(int sockfd, serv_t *serv, char *buffer)
{
    int count = 0;
    char *str = NULL;
    char **array = split_string_at_spaces(buffer, &count);
    array[1] = array[1] + 1;
    if (serv->clients->next == NULL) {
        printf("LA GROSSE DARONNE A KENTIN\n");
    }
    player_t *t = parse_player(sockfd, serv, atoi(array[1]));
    if (t == NULL) {
        printf("EXIT\n");
        return 84;
    }
    char *dir = get_orientation(t->orientation);
    int len = snprintf(str, 0, "ppo %d %d %d %s\n", t->id, t->x, t->y, dir);
    char s[len + 1];

    if (t == NULL)
        return 84;
    sprintf(s, "ppo %d %d %d %s\n", t->id, t->x, t->y, dir);
    if (write(sockfd, s, len) == -1)
        return 84;
    return 0;
}

int send_player_level(int sockfd, serv_t *serv, char *buffer)
{
    int count = 0;
    char **array = split_string_at_spaces(buffer, &count);
    player_t *tmp = parse_player(sockfd, serv, atoi(array[1]));
    char *msg = NULL;
    int len = snprintf(msg, 0, "plv %d %d\n", tmp->id, tmp->level);
    char s[len];

    snprintf(s, len, "plv %d %d\n", tmp->id, tmp->level);
    if (write(sockfd, s, len) == -1)
        return 84;
    return 0;
}

int send_player_inventory(int sockfd, serv_t *serv, char *buffer)
{
    char msg[0];
    player_t *tmp = serv->clients->player;
    inv_t *inv = tmp->inventory;
    int len = snprintf(msg, 0, "pin %d %d %d %d %d %d %d %d\n", tmp->id
        , inv->food, inv->linemate, inv->deraumere, inv->sibur, inv->mendiane,
        inv->phiras, inv->thystame);
    char s[len + 1];
    (void)buffer;

    printf("id: %d\n", tmp->id);
    snprintf(s, len, "pin %d %d %d %d %d %d %d %d\n", tmp->id
        , inv->food, inv->linemate, inv->deraumere, inv->sibur, inv->mendiane,
        inv->phiras, inv->thystame);
    if (write(sockfd, s, len) == -1)
        return 84;
    return 0;
}

int send_expulsion(int sockfd, serv_t *serv, char *buffer)
{
    (void)buffer;
    client_t *cpy = get_correct_client(serv, sockfd);
    char msg[10];

    sprintf(msg, "pex %d\n", cpy->player->id);
    write(serv->sockfd, msg, 10);
    return 0;
}


int send_death_player(int sockfd, serv_t *serv, char *buffer)
{
    (void)buffer;
    client_t *cpy = get_correct_client(serv, sockfd);
    char msg[10];

    sprintf(msg, "pdi %d\n", cpy->player->id);
    write(serv->sockfd, msg, 10);
    return 0;
}

int send_egg_laying(int sockfd, serv_t *serv, char *buffer)
{
    (void)buffer;
    client_t *cpy = get_correct_client(serv, sockfd);
    char msg[10];

    sprintf(msg, "pfk %d\n", cpy->player->id);
    write(serv->sockfd, msg, 10);
    return 0;
}

int send_broadcast(int sockfd, serv_t *serv, char *buffer)
{
    char msg[0];
    client_t *cpy = get_correct_client(serv, sockfd);
    int len = snprintf(msg, 0, "pbc %d %s", cpy->player->id, buffer);
    char send[len];

    sprintf(send, "pbc %d %s", cpy->player->id, buffer);
    write(serv->sockfd, send, len);
    return 0;
}