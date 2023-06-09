##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## ai
##

from .player import Priority, Player, Orientation
from .game import Game
import re
from random import randint


class AI(Player, Game, Priority, Orientation):
    def __init__(self, socket, game):
        super().__init__(socket, game)

    # * AI Strategy
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

    def get_next_move(self, target_coords):
        x, y = target_coords
        orientation_diff = (self.orientation - self.get_target_orientation(x, y)) % 4

        if orientation_diff == 0:
            return "Forward"
        elif orientation_diff == 1 or orientation_diff == -3:
            return "Right"
        elif orientation_diff == 3 or orientation_diff == -1:
            return "Left"

    def get_target_orientation(self, target_x, target_y):
        if target_x < 0:
            target_x = target_x % self.map_size_x
        if target_y < 0:
            target_y = target_y % self.map_size_y

        if target_x < self.x:
            return self.WEST
        elif target_x > self.x:
            return self.EAST
        elif target_y < self.y:
            return self.NORTH
        elif target_y > self.y:
            return self.SOUTH
        else:
            return self.orientation

    def fetch_food(self, map):
        if map[self.y][self.x]["food"] > 0:
            self.priority = Priority.EXPLORE
            map[self.y][self.x]["food"] -= 1
            print("I JUST ATE")
            return "Take food"
        # find food
        return self.explore()
        x, y = self.find_nearest_resource("food", map)
        if x > -1:
            print(f"I'm going to X:{x}, Y:{y}")
            return self.get_next_move((x, y))
        else:
            return self.explore()

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

