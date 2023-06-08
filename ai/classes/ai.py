##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## ai
##

from .player import Priority, Player
import re
from random import randint


class AI(Player):
    def __init__(self, socket, game):
        super().__init__(socket, game)

    # * AI Strategy
    def update_inventory(self):
        self.socket.send("Inventory")
        self.socket.receive()
        print(self._inventory)
        inventory_regex = r"(\w+)\s+(\d+)"
        matches = re.findall(inventory_regex, self.socket.buffer)
        for item, quantity in matches:
            if item in self._inventory:
                self._inventory[item] = int(quantity)

    def update_priority(self):
        if (self._inventory["food"] < 12):
            self.priority = Priority.FOOD
            return
        if self.priority != Priority.EXPLORE:
            return

    def pick_move(self, map):
        move = ""
        self.update_inventory()
        self.update_priority()
        match self.priority:
            case Priority.EXPLORE:
                move = self.explore()
            case Priority.FOOD:
                move = self.fetch_food(map)
        return move

    def find_nearest_resource(self, resource_type, map):
        map_height = len(map)
        map_width = len(map[0])

        nearest_distance = float('inf')
        nearest_coords = None

        for y in range(map_height):
            for x in range(map_width):
                tile = map[y][x]
                if tile[resource_type] > 0:
                    distance = self.get_distance(x, y)
                    if distance < nearest_distance:
                        nearest_distance = distance
                        nearest_coords = (x, y)
        if nearest_coords == None:
            return -1, -1
        return nearest_coords

    def fetch_food(self, map):
        if map[self.y][self.x]["food"] > 0:
            self.priority = Priority.EXPLORE
            map[self.y][self.x]["food"] -= 1
            return "Take food"
        # find food
        return self.explore()
        # TODO : Implement navigation to nearest food
        # x, y = self.find_nearest_resource("food", map)
        # if x > -1:
        #     print(f"there is food at Y {y}, X {x}")
        # return "Forward"

    def explore(self):
        foo = randint(0,12)
        if foo < 5:
            return "Forward"
        elif foo < 10:
            return "Look"
        elif foo < 11:
            return "Right"
        else:
            return "Left"

