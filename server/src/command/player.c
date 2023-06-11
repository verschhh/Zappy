/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** player.c
*/

#include "../../includes/zappy.h"

void erase_first_characters(char* str, int numChars) {
    int len = strlen(str);
    if (numChars >= len) {
        str[0] = '\0';
    } else {
        memmove(str, str + numChars, len - numChars + 1);
    }
}

int send_player_position(int sockfd, serv_t *serv, char *buffer)
{
    int count = 0;
    char *str = NULL;
    char **array = split_string_at_spaces(buffer, &count);
    erase_first_characters(array[1], 1);
    printf("array[1] = %s", array[1]);
    player_t *t = parse_player(sockfd, serv, atoi(array[1]));
    if (t == NULL) {
        printf("EXIT\n");
        return 84;
    }
    char *dir = get_orientation(t->orientation);
    int len = snprintf(str, 0, "ppo %d %d %d %s\n", t->id, t->x, t->y, dir);
    char s[len + 1];

    if (t == NULL)
        return unknown_command(sockfd, serv, buffer);
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

    if (tmp == NULL)
        return unknown_command(sockfd, serv, buffer);
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

    if (tmp == NULL)
        return unknown_command(sockfd, serv, buffer);
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

    if (cpy->player == NULL)
        return unknown_command(sockfd, serv, buffer);
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

    if (cpy->player == NULL)
        return unknown_command(sockfd, serv, buffer);
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
    if (buffer == NULL)
        return unknown_command(sockfd, serv, buffer);
    sprintf(send, "pbc %d %s", cpy->player->id, buffer);
    write(serv->sockfd, send, len);
    return 0;
}

int check_level(slot_t *tmp)
{
    int count = 0;
    while (tmp->team_member->next != NULL) {
        if (tmp->team_member->player->level == 8)
            count++;
        tmp->team_member = tmp->team_member->next;
       if (count >= 6)
            return 1;
    }
    return 0;
}

int check_end_game(serv_t *serv)
{
    int count = 0;
    slot_t *slot = serv->slots;
    while (slot->next != NULL) {
        if (check_level(slot) == 1)
            return 1;
    }
    return 0;
}

int end_of_game(int sockfd, serv_t *serv, char *buffer)
{
    (void)buffer;
    char msg[10];
    int end = 0;
    update_teams(serv);
    end = check_end_game(serv);
    if (end == 0)
        return 0;
    if (serv->clients->team_name == NULL)
        return unknown_command(sockfd, serv, buffer);
    sprintf(msg, "seg %s\n", serv->clients->team_name);
    write(serv->sockfd, msg, 10);
    exit (0);
}

int unknown_command(int sockfd, serv_t *serv, char *buffer)
{
    (void)buffer;
    char msg[4];

    sprintf(msg, "suc\n");
    write(serv->sockfd, msg, 4);
    return 0;
}