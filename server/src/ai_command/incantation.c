/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** incantation.c
*/

#include "../../includes/zappy.h"

int check_enough_element(map_t *map, client_t *client, serv_t *serv)
{
    int nb_player_on_title = 0;
    for (client_t *temp = serv->clients; temp != NULL; temp = temp->next) {
        if (temp->player->x == client->player->x
            && temp->player->y == client->player->y)
            nb_player_on_title++;
    }
    int nb = level_1_2_3(map, client, nb_player_on_title);
    int nb2 = level_4_5(map, client, nb_player_on_title);
    int nb3 = level_6_7(map, client, nb_player_on_title);
    if (nb != 84)
        return nb;
    if (nb2 != 84)
        return nb2;
    if (nb3 != 84)
        return nb3;
    return 84;
}

static int start_incataion(serv_t *serv, client_t *client, char *buff, int tmp)
{
    for (client_t *temp = serv->clients; temp != NULL && tmp > 0;
        temp = temp->next) {
        if (temp->player->x == client->player->x
        && temp->player->y == client->player->y) {
            update_time_limit(serv, temp, 300, buff);
            tmp--;
            }
        }
        update_time_limit(serv, client, 300, buff);
        return 0;
}

static int finish_incantation(serv_t *serv, client_t *client, char *s, int nb)
{
    for (client_t *temp = serv->clients; temp != NULL && nb > 0;
        temp = temp->next) {
        if (temp->player->x == client->player->x
        && temp->player->y == client->player->y) {
            write(temp->sockfd, s, 17);
            nb--;
        }
    }
    return 0;
}

int incantation(int sockfd, serv_t *serv, char *buffer)
{
    (void)buffer;
    client_t *client = get_correct_client(serv, sockfd);
    char msg[25];
    map_t *map = get_correct_tile(serv->map, client);
    int nb = check_enough_element(map, client, serv);
    if (nb == 84) {
        write(sockfd, "ko\n", 4);
        return 0;
    }
    int tmp = nb;
    if (!client->clocking) {
        write(sockfd, "Elevation underway\n", 20);
        return start_incataion(serv, client, buffer, tmp);
    }
    client->clocking = false;
    client->player->level += 1;
    sprintf(msg, "Current level: %d\n", client->player->level);
    write(sockfd, msg, 17);
    printf("Player %d level up to %d\n", client->player->id, client->player->level);
    return finish_incantation(serv, client, msg, nb);
}
