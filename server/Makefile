##
## EPITECH PROJECT, 2022
## zappy
## File description:
## Makefile
##

SRC = 	src/main.c \
		src/parse_arguments.c \

OBJ = $(SRC:.c=.o)

NAME = zappy_server

CFLAGS = -I./includes

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)
	mv $(NAME) ../

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
