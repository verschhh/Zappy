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

    def set_map(self):
        for i in range(self.map_size_y):
            self.map.append([])
            for i in range(self.map_size_x):
                self.map[-1].append({"p": 0, "f": 0,"l": 0, "d": 0, "s": 0, "m": 0, "ph": 0, "t": 0})


    def update_map(self, list_items_to_update):
        for y, i in enumerate(self.map):
            for  x, _ in enumerate(i):
                for item in list_items_to_update:
                    if item[0] == x and item[1] == y:
                        self.map[y][x] = {"p": 0, "f": 0, "l": 0, "d": 0, "s": 0, "m": 0, "ph": 0, "t": 0}
                        for item2 in item[2]:
                            if item2 in self.map[y][x]:
                                self.map[y][x][item2] += 1

                
