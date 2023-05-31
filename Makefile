##
## EPITECH PROJECT, 2022
## zappy
## File description:
## Makefile
##

all: gui server ai

ai:
	@make -C ai

gui:
	@make -C gui

server:
	@make -C server

clean:
	@make clean -C ai
	@make clean -C gui
	@make clean -C server

fclean:
	@make fclean -C ai
	@make fclean -C gui
	@make fclean -C server

re: fclean all

.PHONY: all ai gui server clean fclean re
