/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** look.c
*/

#include "../../includes/zappy.h"

char *tile_to_string(map_t *tile) {
    char *str = malloc(256 * sizeof(char));
    str[0] = '\0';  // initialize the string to be empty

    // TODO: add the player(s) on the tile

    // append each resource multiple times
    for (int i = 0; i < tile->food; i++) {
        strcat(str, "food ");
    }
    for (int i = 0; i < tile->linemate; i++) {
        strcat(str, "linemate ");
    }
    for (int i = 0; i < tile->deraumere; i++) {
        strcat(str, "deraumere ");
    }
    for (int i = 0; i < tile->sibur; i++) {
        strcat(str, "sibur ");
    }
    for (int i = 0; i < tile->mendiane; i++) {
        strcat(str, "mendiane ");
    }
    for (int i = 0; i < tile->phiras; i++) {
        strcat(str, "phiras ");
    }
    for (int i = 0; i < tile->thystame; i++) {
        strcat(str, "thystame ");
    }

    return str;
}

coord_t *get_visible_tile_coords(serv_t *server, player_t *player) {
    int vision_size = (player->level * (player->level + 1)) / 2 + 1;  // Calculate number of tiles visible
    coord_t *visible_coords = calloc(vision_size, sizeof(coord_t));  // Initialize visible_coords with NULLs

    int k = 0;
    for (int i = 0; i <= player->level; i++) {
        int row_width = 2 * i + 1;
        for (int j = 0; j < row_width; j++) {
            switch (player->orientation) {
                case 1:  // North
                    visible_coords[k].y = (player->y - i + server->max_y) % server->max_y;
                    visible_coords[k].x = (player->x + j - i + server->max_x) % server->max_x;
                    break;
                case 2:  // East
                    visible_coords[k].x = (player->x + i + server->max_x) % server->max_x;
                    visible_coords[k].y = (player->y + j - i + server->max_y) % server->max_y;
                    break;
                case 3:  // South
                    visible_coords[k].y = (player->y + i + server->max_y) % server->max_y;
                    visible_coords[k].x = (player->x - j + i + server->max_x) % server->max_x;
                    break;
                case 4:  // West
                    visible_coords[k].x = (player->x - i + server->max_x) % server->max_x;
                    visible_coords[k].y = (player->y - j + i + server->max_y) % server->max_y;
                    break;
            }
            k++;
        }
    }

    return visible_coords;
}


int look(int sockfd, serv_t *serv, char *buffer)
{
    client_t *cli = get_correct_client(serv, sockfd);
    player_t *player = cli->player;
    int vision_size = (player->level * (player->level + 1)) / 2 + 1;
    printf("player is at X%d Y%d and is facing %d\n", cli->player->x, cli->player->y, player->orientation);
    coord_t *visible_coords = get_visible_tile_coords(serv, player);
    printf("vision_size = %d\n", vision_size);
    for (int i = 0; i < vision_size; i++) {
        printf("visible_coords[%d] = X%d Y%d\n", i, visible_coords[i].x, visible_coords[i].y);
    }
}