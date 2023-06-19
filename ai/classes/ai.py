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

class Incantation:
    LVL_1 = {"linemate": 1, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
    LVL_2 = {"linemate": 1, "deraumere": 1, "sibur": 1, "mendiane": 0, "phiras": 0, "thystame": 0}
    LVL_3 = {"linemate": 2, "deraumere": 0, "sibur": 1, "mendiane": 0, "phiras": 2, "thystame": 0}
    LVL_4 = {"linemate": 1, "deraumere": 1, "sibur": 2, "mendiane": 0, "phiras": 1, "thystame": 0}
    LVL_5 = {"linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3, "phiras": 0, "thystame": 0}
    LVL_6 = {"linemate": 1, "deraumere": 2, "sibur": 3, "mendiane": 0, "phiras": 1, "thystame": 0}
    LVL_7 = {"linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1}

class AI(Player, Game, Priority, Orientation):
    def __init__(self, socket, game, x, y):
        Player.__init__(self, socket, game)
        Game.__init__(self, x, y)

    # * AI Strategy
    def pick_move(self):
        # print(map)
        self.update_map(self.look())
        match self.level:
            case 1:
                self.level_1()
            case 2:
                self.take_useless_ressources(Incantation.LVL_2)
                exit(2)

    def random_move(self):
        foo = randint(0,1)
        if foo == 0:
            self.right()
        elif foo == 1:
            self.left()
        self.forward()

    def level_1(self):
        pos_limenate = self.nb_ressources_tile(1, "linemate")
        pos_food = self.nb_ressources_tile(2, "food")
        self.update_inventory()
        if pos_limenate != (-1, -1) and self._inventory["food"] > 20:
            self.get_next_move(pos_limenate)
            self.update_map(self.look())
            self.take_useless_ressources(Incantation.LVL_1)
            self.update_map(self.look())
            print(self.map[self.y][self.x])
            if self.map[self.y][self.x]["player"] > 1:
                self.random_move()
            elif self.incantation() == 84:
                self.random_move()
            
        elif pos_food != (-1, -1):
            nb_loop = 0
            self.get_next_move(pos_food)
            self.take("food")
            while self.socket.buffer == "ok\n" and nb_loop < 50:
                self.take("food")
                nb_loop += 1
            self.update_inventory()
        else:
            self.random_move()

    def take_useless_ressources(self, good_ressources):
        print("take useless ressources")
        for ressource in self.map[self.y][self.x]:
            if ressource != "player" and ressource != "food" and good_ressources[ressource] != self.map[self.y][self.x][ressource]:
                self.take(ressource)
                self.map[self.y][self.x][ressource] -= 1
                while good_ressources[ressource] < self.map[self.y][self.x][ressource]:
                    self.take(ressource)
                    self.map[self.y][self.x][ressource] -= 1



    def nb_ressources_tile(self, nb, ressource):
        for y, i in enumerate(self.map):
            for x, _ in enumerate(i):
                if self.map[y][x][ressource] >= nb:
                    return (x, y)
        return (-1, -1)

    def update_inventory(self):
        self.socket.send("Inventory")
        self.socket.receive()
        print(self._inventory)
        inventory_regex = r"(\w+)\s+(\d+)"
        matches = re.findall(inventory_regex, self.socket.buffer)
        for item, quantity in matches:
            if item in self._inventory:
                self._inventory[item] = int(quantity)


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


        while (self.x, self.y) != target_coords:
            print(f"X:{self.x} Y:{self.y}, Target X:{target_coords[0]} Target Y:{target_coords[1]}")
            x, y = target_coords
            orientation_diff = (self.orientation - self.get_target_orientation(x, y)) % 4
            print(f"Orientation diff: {orientation_diff}")
            if orientation_diff == 0:
                self.forward()
            elif orientation_diff == 1 or orientation_diff == -3:
                self.right()
                self.forward()
            else:
                self.left()
                self.forward()

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

