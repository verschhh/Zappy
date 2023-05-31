##
## EPITECH PROJECT, 2022
## B-YEP-400-BER-4-1-zappy-kentin.paille
## File description:
## classes.py
##

class Game:
    def __init__(self):
        self.map_size_x = 0
        self.map_size_y = 0


class Player:
    def __init__(self):
        self.x = 0
        self.y = 0
        self.level = 1
        self.inventory = {"food": 10, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
        self.team = ""