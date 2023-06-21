##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## player
##

from math import ceil
from random import randint
from time import sleep

SUCESS = 0
FAIL = 84

class Incantation:
    LVL_1 = {"player": 1, "linemate": 1, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
    LVL_2 = {"player": 2, "linemate": 1, "deraumere": 1, "sibur": 1, "phiras": 0, "thystame": 0, "mendiane": 0}
    LVL_3 = {"player": 2, "linemate": 2, "sibur": 1, "phiras": 2, "thystame": 0, "mendiane": 0, "deraumere": 0}
    LVL_4 = {"player": 4, "linemate": 1, "deraumere": 1, "sibur": 2, "phiras": 1, "thystame": 0, "mendiane": 0}
    LVL_5 = {"player": 4, "linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3, "phiras": 0, "thystame": 0}
    LVL_6 = {"player": 6, "linemate": 1, "deraumere": 2, "sibur": 3, "phiras": 1, "thystame": 0, "mendiane": 0}
    LVL_7 = {"player": 6, "linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1}

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
    def __init__(self, socket, map_size_x, map_size_y):
        self.x = 5
        self.y = 5
        self.max_x = map_size_x - 1
        self.max_y = map_size_y - 1
        self.level = 1
        self._inventory = {"food": 10, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
        self.team = ""
        self.orientation = Orientation.WEST
        self.priority = Priority.EXPLORE
        self.socket = socket
        self.vision = []
        self.vision_with_pos = []
        self.inv_other_player = []
        self.id = randint(0, 10000000)
        self.nb_joueur_ready = 0
        self.incantation_direction = 0
        self.incantation_launched = False

    def player_is_in_inventory(self, id):
        print(id)
        for i in self.inv_other_player:
            if i["id"] == int(id):
                print("True")
                return True
        print("False")
        return False

    def drop_all_ressources(self):
        for ressource in self._inventory:
            print(ressource)
            tmp = 0
            while self._inventory[ressource] > 0 and ressource != "food" and tmp <= 4:
                print(f"ressource = {ressource}")
                self.set(ressource)
                tmp += 1

    def update_inventory_other_player(self, message):
        print("bizzare")
        print(message)
        message = message.split(' ')
        print(message[-1].split('\n'))
        message[-1] = message[-1].split('\n')[0]
        print(f"??? {message}")
        if self.player_is_in_inventory(message[0]) == False:
            self.inv_other_player.append({"id": int(message[0]), "inventory": {"food": 0, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}})

        for i in self.inv_other_player:
            if i["id"] == int(message[0]):
                i["inventory"]["food"] = int(message[1])
                i["inventory"]["linemate"] = int(message[2])
                i["inventory"]["deraumere"] = int(message[3])
                i["inventory"]["sibur"] = int(message[4])
                i["inventory"]["mendiane"] = int(message[5])
                i["inventory"]["phiras"] = int(message[6])
                if message[7][-1] == '\n' or message[7][-1] == '[':
                    message[7] = message[7][:-1]
                    if message[7][-1] == '[' or message[7][-1] == '\n':
                        message[7] = message[7][:-1]
                i["inventory"]["thystame"] = int(message[7])

    def get_distance(self, x, y):
        dx = abs(self.x - x)
        dy = abs(self.y - y)

        wrapped_dx = min(dx, self.max_x - dx)
        wrapped_dy = min(dy, self.max_y - dy)

        return wrapped_dx + wrapped_dy

    def forward(self):
        print("Forward")
        self.socket.send("Forward")
        self.socket.receive(self)
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
        print("Right")
        self.socket.send("Right")
        self.socket.receive(self)
        self.orientation += 1
        if self.orientation > Orientation.WEST:
            self.orientation = Orientation.NORTH

    def left(self):
        print("Left")
        self.socket.send("Left")
        self.socket.receive(self)
        self.orientation -= 1
        if self.orientation < Orientation.NORTH:
            self.orientation = Orientation.WEST

    def look(self):
        print("Look")
        self.socket.send("Look")
        self.socket.receive(self)
        print(self.socket.buffer)
        while self.socket.buffer == "ko\n":
            self.socket.send("Look")
            self.socket.receive(self)

        buff = self.socket.buffer[1:-1]
        print(buff)
        buff += "\0"
        i = 0
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
        self.socket.receive(self)
        buff = self.socket.buffer
        if buff == "ok":
            return SUCESS
        return FAIL

    def fork(self):
        self.socket.send("Fork")
        self.socket.receive(self)

    def connect_nbr(self):
        self.socket.send("Connect_nbr")
        self.socket.receive(self)
        return int(self.socket.buffer)

    def send_inventory(self):
        message = "Inventory,"
        message += str(self.id) + " "
        for key, value in self._inventory.items():
            message += f"{value}"
            if key != "thystame":
                message += " "
        return message

    def broadcast(self, message):
        print(f"id{self.id} send this message : {message}")
        self.socket.send(f"Broadcast {message}")
        self.socket.receive(self)
        if message == "Ready":
            self.socket.receive(self)

    def inventory(self):
        print("Inventory")
        self.socket.send("Inventory")
        self.socket.receive(self)
        return self._inventory

    def take(self, item):
        print(f"Take {item}")
        self.socket.send(f"Take {item}")
        self.socket.receive(self)
        if self.socket.buffer == "ok\n":
            self._inventory[item] += 1
            return SUCESS
        return FAIL

    def set(self, item):
        print(f"Set {item}")
        self.socket.send(f"Set {item}")
        self.socket.receive(self)
        if self.socket.buffer == "ok\n":
            self._inventory[item] -= 1
            return SUCESS
        return FAIL

    def incantation(self):
        print("Incantation")
        self.socket.send("Incantation")
        self.socket.receive(self)
        buff = self.socket.buffer
        print(buff)
        if buff == "ko\n":
            print("Incantation Failed")
            self.socket.buffer = ""
            print("Wait to feel better")
            self.socket.receive(self)
            print("END")
            return FAIL
        print("Elevation Started\n")
        self.socket.buffer = ""
        self.socket.receive(self)
        print(f"Return:{self.socket.buffer}")
        if self.socket.buffer.split(' ')[0] == "Current":
            print("Elevation Finished")
            print("You are now level %d" % (self.level))
            return SUCESS
        print("Elevation Failed")
        return FAIL

    def go_to_direction(self):
        print(f"self.incantation_direction = {self.incantation_direction}")
        while int(self.incantation_direction) != 0:
            print(int(self.incantation_direction))
            match int(self.incantation_direction):
                case 0:
                    print("I am here")
                    break
                case 1:
                    self.forward()
                    print("Front")

                case 2:
                    self.forward()
                    self.left()
                    self.forward()
                    if randint(0, 1) == 0:
                        self.right()
                    print("Front Left")

                case 3:
                    self.left()
                    self.forward()
                    print("Left")

                case 4:
                    self.left()
                    self.forward()
                    self.left()
                    self.forward()
                    if randint(0, 1) == 0:
                        self.right()
                    print("Back Left")

                case 5:
                    self.left()
                    self.left()
                    self.forward()
                    print("Back")

                case 6:
                    self.right()
                    self.forward()
                    self.right()
                    self.forward()
                    if randint(0, 1) == 0:
                        self.left()
                    print("Back Right")

                case 7:
                    self.right()
                    self.forward()
                    print("Right")

                case 8:
                    self.right()
                    self.forward()
                    self.left()
                    self.forward()
                    if randint(0, 1) == 0:
                        self.right()
                    print("Front Right")

        self.drop_all_ressources()
        match int(self.incantation_direction):
                case 0:
                    print("I am here")
                case 1:
                    self.forward()
                    print("Front")

                case 2:
                    self.forward()
                    self.left()
                    self.forward()
                    self.right()
                    print("Front Left")

                case 3:
                    self.left()
                    self.forward()
                    print("Left")

                case 4:
                    self.left()
                    self.forward()
                    self.left()
                    self.forward()
                    self.right()
                    print("Back Left")

                case 5:
                    self.left()
                    self.left()
                    self.forward()
                    print("Back")

                case 6:
                    self.right()
                    self.forward()
                    self.right()
                    self.forward()
                    print("Back Right")

                case 7:
                    self.right()
                    self.forward()
                    print("Right")

                case 8:
                    self.right()
                    self.forward()
                    self.left()
                    self.forward()
                    print("Front Right")

        self.broadcast("Ready")
        print(self.look()[0])

    def call_for_incantation(self, direction, message):
        for i in message:
            print(f"i = {i}, self.id = {self.id}")
            if int(i) == self.id:
                self.incantation_direction = direction
                self.go_to_direction()
