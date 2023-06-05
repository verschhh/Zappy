##
## EPITECH PROJECT, 2022
## zappy
## File description:
## Makefile
##

SRC = 	src/gui.cpp \
		src/main.cpp \
		src/menu.cpp \
		src/inGame.cpp \
		src/connection.cpp \

OBJ = $(SRC:.cpp=.o)

NAME = zappy_gui

CFLAGS = -I./includes -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

CPPFLAGS = -W -Wall -Wextra -Werror -g3

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) $(CFLAGS) $(CPPFLAGS)
	mv $(NAME) ../

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ../$(NAME)

re: fclean all

.PHONY: clean fclean re
