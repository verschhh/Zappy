##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## game
##

class Game:
    def __init__(self, x, y):
        self.map_size_x = x
        self.map_size_y = y
        self.map = []
        self.players = []
        self.eggs = []
        self.tiles = {"food": 0, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}

    def set_map(self):
        for i in range(self.map_size_y):
            self.map.append([])
            for i in range(self.map_size_x):
                self.map[-1].append({"food": 0, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0})


    # def update_map(self, player):
    #     for y, i in enumerate(self.map):
    #         for  x, _ in enumerate(i):
