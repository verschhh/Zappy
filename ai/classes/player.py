##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## player
##

from math import ceil
from random import randint
import re


SUCESS = 0
FAIL = 84

class Orientation:
    NORTH = 0
    EAST = 1
    SOUTH = 2
    WEST = 3

class Priority:
    EXPLORE = 0
    FOOD = 1
    LINEMATE = 2
    DERAUMERE = 3
    SIBUR = 4
    MENDIANE = 5
    PHIRAS = 6
    THYSTAME = 7

class Player:
    def __init__(self, socket, game):
        self.x = 5
        self.y = 5
        self.max_x = game.map_size_x - 1
        self.max_y = game.map_size_y - 1
        self.level = 1
        self._inventory = {"food": 10, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
        self.team = ""
        self.orientation = Orientation.WEST
        self.priority = Priority.EXPLORE
        self.socket = socket
        self.vision = []
        self.vision_with_pos = []

    def get_distance(self, x, y):
        dx = abs(self.x - x)
        dy = abs(self.y - y)

        wrapped_dx = min(dx, self.max_x - dx)
        wrapped_dy = min(dy, self.max_y - dy)

        return wrapped_dx + wrapped_dy

    def forward(self):
        self.socket.send("Forward")
        self.socket.receive()
        if self.orientation == Orientation.NORTH:
            self.y -= 1
        elif self.orientation == Orientation.EAST:
            self.x += 1
        elif self.orientation == Orientation.SOUTH:
            self.y += 1
        elif self.orientation == Orientation.WEST:
            self.x -= 1
        if self.x < 0:
            self.x = self.max_x
        elif self.x > self.max_x:
            self.x = 0
        if self.y < 0:
            self.y = self.max_y
        elif self.y > self.max_y:
            self.y = 0

    def right(self):
        self.socket.send("Right")
        self.socket.receive()
        self.orientation += 1
        if self.orientation > Orientation.WEST:
            self.orientation = Orientation.NORTH

    def left(self):
        self.socket.send("Left")
        self.socket.receive()
        self.orientation -= 1
        if self.orientation < Orientation.NORTH:
            self.orientation = Orientation.WEST

    def look(self):
        self.socket.send("Look")
        self.socket.receive()
        buff = self.socket.buffer[2:-2]
        i = 0
        print(buff)
        while buff[i] != '\0':
            if buff[i] == ',' and buff[i + 1] == ' ':
                buff = buff[:i + 1] + buff[i + 2:]
                if i >= buff.rfind(','):
                    break
            i += 1
        self.vision = buff.split(',')
        for i in range(len(self.vision)):
            self.vision[i] = self.vision[i].split(' ')
        if len(self.vision[-1]) > 1:
            self.vision[-1] = self.vision[-1][:-1]
        self.find_pos_of_look()
        return self.vision_with_pos

    def find_pos_of_look(self):
        self.vision_with_pos = []
        floor = 0
        pos_vision = 0

        for c,i in enumerate(range(1, 1+3*self.level, 2)):
            for x in range(i):
                if x + 1 < i/2:
                    self.set_object_pos(-c+x, floor, pos_vision)
                elif x + 1 == ceil(i/2):
                    self.set_object_pos(0, floor, pos_vision)
                else:
                    self.set_object_pos(abs(c-x), floor, pos_vision)
                pos_vision += 1
            floor += 1

    def set_object_pos(self, move, floor, i):
        if self.orientation == Orientation.NORTH:
            if self.x + move > self.max_x:
                move = -self.max_x - move + 1
            elif self.x + move < 0:
                move = self.max_x - move - 1

            if self.y - floor < 0:
                floor = -self.max_y - floor + 1
            self.vision_with_pos.append([self.x + move, self.y - floor, self.vision[i]])

        elif self.orientation == Orientation.EAST:
            if self.y + move > self.max_y:
                move = -self.max_y - move + 1
            elif self.y + move < 0:
                move = self.max_y - move - 1

            if self.x + floor > self.max_x:
                floor = -self.max_x - floor + 1
            self.vision_with_pos.append([self.x + floor, self.y + move, self.vision[i]])

        elif self.orientation == Orientation.SOUTH:
            if self.x - move > self.max_x:
                move = self.max_x - move - 1
            elif self.x - move < 0:
                move = -self.max_x + move - 1

            if self.y + floor > self.max_y:
                floor = -self.max_y + floor - 1

            self.vision_with_pos.append([self.x - move, self.y + floor, self.vision[i]])

        elif self.orientation == Orientation.WEST:
            if self.y - move > self.max_y:
                move = self.max_y + move + 1
            elif self.y - move < 0:
                move = -self.max_y + move - 1

            if self.x - floor < 0:
                floor = -self.max_x + floor - 1

            self.vision_with_pos.append([self.x - floor, self.y - move, self.vision[i]])

    def eject(self):
        self.socket.send("Eject")
        self.socket.receive()
        buff = self.socket.buffer
        if buff == "ok":
            return SUCESS
        return FAIL

    def fork(self):
        self.socket.send("Fork")
        self.socket.receive()

    def connect_nbr(self):
        self.socket.send("Connect_nbr")
        self.socket.receive()
        return int(self.socket.buffer)

    def broadcast(self, message):
        self.socket.send(f"Broadcast {message}")
        self.socket.receive()

    def inventory(self):
        self.socket.send("Inventory")
        self.socket.receive()
        print(f"Inventory: {self.socket.buffer}")
        print(f"My inventory: {self._inventory}")
        return self._inventory

    def take(self, item):
        self.socket.send(f"Take {item}")
        self.socket.receive()
        if self.socket.buffer == "ok\n":
            self._inventory[item] += 1
            print("Success")
            return SUCESS
        print("Fail")
        return FAIL

    def set(self, item):
        self.socket.send(f"Set {item}")
        self.socket.receive()
        if self.socket.buffer == "ok\n":
            self._inventory[item] -= 1
            print("Success")
            return SUCESS
        print("Fail")
        return FAIL

    def incantation(self):
        self.socket.send("Incantation")
        self.socket.receive()
        buff = self.socket.buffer
        if buff == "ko\n":
            print("Incantation Failed")
            self.socket.buffer = ""
            print("Wait to feel better")
            self.socket.receive()
            print("END")
            return FAIL
        print("Elevation Started\n")
        self.socket.buffer = ""
        self.socket.receive()
        if self.socket.buffer.split(' ')[0] == "Current":
            self.level += 1
            print("Elevation Finished")
            print("You are now level %d" % (self.level))
            return SUCESS
        print("Elevation Failed")
        return FAIL

    # * AI Strategy
    def update_inventory(self):
        self.socket.send("Inventory")
        self.socket.receive()
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

