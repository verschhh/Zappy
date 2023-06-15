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
        # print(map)
        foo = randint(0,6)
        if foo == 6:
            return "Look"
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

        nearest_distance = float('inf')
        nearest_coords = None
        front_resource_coords = None

        for y in range(self.max_y + 1):
            for x in range(self.max_x + 1):
                tile = map[y][x]
                if tile[resource_type] > 0:
                    distance = self.get_distance(x, y)
                    if distance < nearest_distance:
                        nearest_distance = distance
                        nearest_coords = (x, y)
                        if self.is_in_front(x, y):
                            front_resource_coords = (x, y)
                    elif distance == nearest_distance:
                        if self.is_in_front(x, y):
                            nearest_coords = (x, y)
                            front_resource_coords = (x, y)

        if nearest_coords == None:
            return -1, -1
        if front_resource_coords != None:
            return front_resource_coords
        return nearest_coords

    def is_in_front(self, x, y,):
        dx = (x - self.x + (self.max_x + 1)) % (self.max_x + 1)
        dy = (y - self.y + (self.max_y + 1)) % (self.max_y + 1)
    
        if self.orientation == Orientation.NORTH:
            return dy < (self.max_y + 1) // 2
        elif self.orientation == Orientation.SOUTH:
            return dy > (self.max_y + 1) // 2
        elif self.orientation == Orientation.EAST:
            return dx > (self.max_x + 1) // 2
        elif self.orientation == Orientation.WEST:
            return dx < (self.max_x + 1) // 2

    def get_next_move(self, target_coords):
        x, y = target_coords
        orientation_diff = (self.orientation - self.get_target_orientation(x, y)) % 4

        if orientation_diff == 0:
            return "Forward"
        elif orientation_diff == 1 or orientation_diff == -3:
            return "Right"
        else:
            return "Left"

    def get_target_orientation(self, target_x, target_y):
        dx = (target_x - self.x + (self.max_x + 1)) % (self.max_x + 1)
        dy = (target_y - self.y + (self.max_y + 1)) % (self.max_y + 1)

        if dx < (self.max_x + 1) // 2:
            if dy < (self.max_y + 1) // 2:
                return 0 if dx < dy else 3
            else:
                return 2 if dx < (self.max_y + 1) - dy else 3
        else:
            if dy < (self.max_y + 1) // 2:
                return 0 if (self.max_x + 1) - dx < dy else 1
            else:
                return 2 if (self.max_x + 1) - dx < (self.max_y + 1) - dy else 1


    def fetch_food(self, map):
        print(map[self.y][self.x])
        if map[self.y][self.x]["food"] > 0:
            self.priority = Priority.EXPLORE
            map[self.y][self.x]["food"] -= 1
            print("I JUST ATE")
            return "Take food"
        # find food
        # return self.explore() # TODO: remove this line to use the code below
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

