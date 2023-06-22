/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** incantation.c
*/

#include "../../includes/zappy.h"

int level_1_2_3(map_t *map, client_t *client, int nb_player_on_title)
{
    if (client->player->level == 1 && map->linemate >= 1
    && nb_player_on_title >= 1) {
        map->linemate--;
        return 0;
    }
    if (client->player->level == 2 && map->linemate >= 1
    && map->deraumere >= 1 && map->sibur >= 1 && nb_player_on_title >= 2) {
        map->linemate--;
        map->deraumere--;
        map->sibur--;
        return 1;
    }
    if (client->player->level == 3 && map->linemate >= 2 && map->sibur >= 1
    && map->phiras >= 2 && nb_player_on_title >= 2) {
        map->linemate -= 2;
        map->sibur--;
        map->phiras -= 2;
        return 1;
    }
    return 84;
}

int level_4_5(map_t *map, client_t *client, int nb_player_on_title)
{
    if (client->player->level == 4 && map->linemate >= 1 && map->deraumere >= 1
    && map->sibur >= 2 && map->phiras >= 1 && nb_player_on_title >= 4) {
        map->linemate--;
        map->deraumere--;
        map->sibur -= 2;
        map->phiras--;
        return 3;
    }
    if (client->player->level == 5 && map->linemate >= 1 && map->deraumere >= 2
    && map->sibur >= 1 && map->mendiane >= 3 && nb_player_on_title >= 4) {
        map->linemate--;
        map->deraumere -= 2;
        map->sibur--;
        map->mendiane -= 3;
        return 3;
    }
    return 84;
}

int level_6_7(map_t *map, client_t *client, int nb_player_on_title)
{
    if (client->player->level == 6 && map->linemate >= 1 && map->deraumere >= 2
    && map->sibur >= 3 && map->phiras >= 1 && nb_player_on_title >= 6) {
        map->linemate--;
        map->deraumere -= 2;
        map->sibur -= 3;
        map->phiras--;
        return 5;
    }
    if (client->player->level == 7 && map->linemate >= 2 && map->deraumere >= 2
    && map->sibur >= 2 && map->mendiane >= 2 && map->phiras >= 2
    && map->thystame >= 1 && nb_player_on_title >= 6) {
        map->linemate -= 2;
        map->deraumere -= 2;
        map->sibur -= 2;
        map->mendiane -= 2;
        map->phiras -= 2;
        map->thystame--;
        return 5;
    }
    return 84;
}

int check_enough_element(map_t *map, client_t *client, serv_t *serv)
{
    int nb_player_on_title = 0;
    for (client_t *temp = serv->clients; temp != NULL; temp = temp->next) {
        if (temp->player->x == client->player->x && temp->player->y == client->player->y)
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
        for (client_t *temp = serv->clients; temp != NULL && tmp > 0; temp = temp->next) {
            if (temp->player->x == client->player->x
            && temp->player->y == client->player->y) {
                update_time_limit(serv, temp, 300, buffer);
                tmp--;
            }
        }
        update_time_limit(serv, client, 300, buffer);
        return 0;
    }
    client->clocking = false;
    client->player->level += 1;
    sprintf(msg, "Current level: %d\n", client->player->level);
    write(sockfd, msg, 17);
    for (client_t *temp = serv->clients; temp != NULL && nb > 0; temp = temp->next) {
        if (temp->player->x == client->player->x
        && temp->player->y == client->player->y) {
            write(temp->sockfd, msg, 17);
            nb--;
        }
    }
    return 0;
}