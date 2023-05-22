##
## EPITECH PROJECT, 2022
## zappy
## File description:
## Makefile
##

SRC = 	src/main.cpp \

OBJ = $(SRC:.cpp=.o)

NAME = zappy_gui

CFLAGS = -I./includes

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) $(CFLAGS)
	mv $(NAME) ../

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ../$(NAME)

re: fclean all

.PHONY: clean fclean re
