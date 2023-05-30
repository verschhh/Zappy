##
## EPITECH PROJECT, 2022
## B-YEP-400-BER-4-1-zappy-kentin.paille
## File description:
## classes.py
##

class Game:
    def __init__(self):
        self.mapsize_x = 0
        self.mapsize_y = 0

class Player:
    def __init__(self):
        self.health = 10
        self.level = 1
        self.team = ""