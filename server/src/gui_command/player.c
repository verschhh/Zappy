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
    erase_first_characters(array[1], 1);
    player_t *t = parse_player(sockfd, serv, atoi(array[1]));
    if (t == NULL)
        return unknown_command(sockfd, serv, buffer);
    char *dir = get_orientation(t->orientation);
    int len = snprintf(str, 0, "ppo %d %d %d %s\n", t->id, t->x, t->y, dir);
    char s[len + 1];

    sprintf(s, "ppo %d %d %d %s\n", t->id, t->x, t->y, dir);
    if (write(sockfd, s, len) == -1)
        return 84;
    return 0;
}

int send_player_level(int sockfd, serv_t *serv, char *buffer)
{
    int count = 0;
    char **array = split_string_at_spaces(buffer, &count);
    erase_first_characters(array[1], 1);
    player_t *tmp = parse_player(sockfd, serv, atoi(array[1]));
    char *msg = NULL;
    if (tmp == NULL)
        return unknown_command(sockfd, serv, buffer);
    int len = snprintf(msg, 0, "plv %d %d%s\n", tmp->id, tmp->level, "\n");
    char s[len];

    snprintf(s, len, "plv %d %d%s\n", tmp->id, tmp->level, "\n");
    if (write(sockfd, s, len) == -1)
        return 84;
    return 0;
}

int send_expulsion(int sockfd, serv_t *serv, char *buffer)
{
    (void)buffer;
    client_t *cpy = get_correct_client(serv, sockfd);
    char msg[10];

    if (cpy->player == NULL)
        return unknown_command(sockfd, serv, buffer);
    sprintf(msg, "pex %d\n", cpy->player->id);
    write(serv->sockfd, msg, 10);
    return 0;
}

int send_death_player(serv_t *serv, int id)
{
    sprintf(serv->queue + strlen(serv->queue), "pdi %d\n", id);
    return 0;
}

int send_egg_laying(int sockfd, serv_t *serv, char *buffer)
{
    (void)buffer;
    client_t *cpy = get_correct_client(serv, sockfd);
    char msg[10];

    if (cpy->player == NULL)
        return unknown_command(sockfd, serv, buffer);
    sprintf(msg, "pfk %d\n", cpy->player->id);
    write(serv->sockfd, msg, 10);
    return 0;
}
