/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** tools.c
*/

#include "../includes/zappy.h"

void print_and_exit(char *str)
{
    fprintf(stderr, "%s\n", str);
    exit(84);
}

void usage(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height ");
    printf("-n name1 name2 ... -c clientsNb\n");
    printf("-f freq\n");
    printf("\tport\tis the port number\n");
    printf("\twidth\tis the width of the world\n");
    printf("\theight\tis the height of the world\n");
    printf("\tnameX\tis the name of the team X\n");
    printf("\tclientsNb\tis the number of authorized clients per team\n");
    printf("\tfreq\tis the reciprocal of time unit ");
    printf("for execution of actions\n");
}

char** split_string_at_spaces(const char* input, int* count)
{
    const char* delimiter = " ";
    char* copy = strdup(input);
    char* token = strtok(copy, delimiter);
    char** result = NULL;
    int i = 0;

    while (token != NULL) {
        result = realloc(result, (i + 1) * sizeof(char*));
        result[i] = strdup(token);
        i++;
        token = strtok(NULL, delimiter);
    }
    *count = i;
    free(copy);
    return result;
}

client_t *get_correct_client(serv_t *serv, int sockfd)
{
    client_t *copy = serv->clients;

    while (copy != NULL) {
        printf("copy->sockfd = %d\n", copy->sockfd);
        if (copy->sockfd == sockfd)
            return copy;
        copy = copy->next;
    }
    return NULL;
}

// void update_time_limit(serv_t *serv)
// {
    // client_t *cpy = serv->clients;

    // while (cpy->next != NULL) {
    //     if (cpy->timelimit > 0)
    //         cpy->timelimit--;
    //     cpy = cpy->next;
    // }
// }

int check_time_limit(serv_t *serv, int sockfd)
{
    client_t *cpy = get_correct_client(serv, sockfd);

    if (cpy == NULL)
        return -1;
    if (cpy->tickleft == 0)
        return 0;
    return -1;
}