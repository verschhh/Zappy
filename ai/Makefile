##
## EPITECH PROJECT, 2022
## zappy
## File description:
## Makefile
##

all: clean build

build: fclean
	cp ./zappy_ai ../zappy_ai
	chmod +x ../zappy_ai

fclean: clean
	rm -f ../zappy_ai

clean:
	rm -f ./__pycache__/*.pyc
	rm -f ./classes/__pycache__/*.pyc

.PHONY: all clean fclean re