/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** look.c
*/

#include "../../includes/zappy.h"

static void update_coord(serv_t *serv, coord_t **coord, player_t *player)
{
    coord_t *c = *coord;
    switch (player->orientation) {
        case 1:
            c[c->k].y = (player->y - c->i + serv->max_y) % serv->max_y;
            c[c->k].x = (player->x + c->j - c->i + serv->max_x) % serv->max_x;
            break;
        case 2:
            c[c->k].x = (player->x + c->i + serv->max_x) % serv->max_x;
            c[c->k].y = (player->y + c->j - c->i + serv->max_y) % serv->max_y;
            break;
        case 3:
            c[c->k].y = (player->y + c->i + serv->max_y) % serv->max_y;
            c[c->k].x = (player->x - c->j + c->i + serv->max_x) % serv->max_x;
            break;
        case 4:
            c[c->k].x = (player->x - c->i + serv->max_x) % serv->max_x;
            c[c->k].y = (player->y - c->j + c->i + serv->max_y) % serv->max_y;
            break;
    }

}

coord_t *get_visible_tile_coords(serv_t *server, player_t *player)
{
    int n = player->level + 1;
    int vision_size = (n * (2 * 1 + (n - 1) * 2)) / 2;
    coord_t *coords = calloc(vision_size, sizeof(coord_t));
    coords->k = 0;
    for (coords->i = 0; coords->i < n; coords->i++) {
        int row_width = 2 * coords->i + 1;
        for (coords->j = 0; coords->j < row_width; coords->j++) {
            update_coord(server, &coords, player);
            coords->k++;
        }
    }
    return coords;
}

static char *fuse_look_response(char *str, int v, coord_t *coord, serv_t *serv)
{
    for (int i = 0; i < v; i++) {
        if (i != 0)
            strcat(str, ",");
        client_t *copy = serv->clients;
        map_t *tile = find_tile(serv, coord[i].x, coord[i].y);
        char *tile_str = tile_to_string(tile, copy);
        size_t tile_str_len = strlen(tile_str);
        str = realloc(str, sizeof(char) * (strlen(str) + tile_str_len + 6));
        if (strlen(tile_str) > 1 && i > 0) {
            strcat(str, " ");
        }
        strcat(str, tile_str);
        free(tile_str);
    }
    return str;
}

char *build_look_response(serv_t *server, player_t *player)
{
    int n = player->level + 1;
    int vision_size = (n * (2 * 1 + (n - 1) * 2)) / 2;
    coord_t *visible_coords = get_visible_tile_coords(server, player);
    char *response = malloc(sizeof(char) * (256));
    strcpy(response, "[");

    response = fuse_look_response(response, vision_size, visible_coords,
        server);
    strcat(response, "]\n");
    return response;
}

int look(int sockfd, serv_t *serv, char *buffer)
{
    client_t *cli = get_correct_client(serv, sockfd);
    player_t *player = cli->player;

    if (!cli->clocking) {
        update_time_limit(serv, cli, 7, buffer);
        return 0;
    }
    if (cli->clocking) {
        get_visible_tile_coords(serv, player);
        char *response = build_look_response(serv, player);
        write(sockfd, response, strlen(response));
        cli->clocking = false;
        free(response);
    }
    return 0;
}
