##
## EPITECH PROJECT, 2022
## zappy
## File description:
## Makefile
##

SRC = $(shell find ./src/ -name '*.c')

OBJ = $(SRC:.c=.o)

NAME = zappy_server

CFLAGS = -I./includes

# CPPFLAGS = -W -Wall -Wextra -g3

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS) $(CPPFLAGS)
	# mv $(NAME) ../

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
