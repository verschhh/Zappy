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
    LVL_1 = {"p": 1, "l": 1, "d": 0, "s": 0, "m": 0, "ph": 0, "t": 0}
    LVL_2 = {"p": 2, "l": 1, "d": 1, "s": 1, "ph": 0, "t": 0, "m": 0}
    LVL_3 = {"p": 2, "l": 2, "s": 1, "ph": 2, "t": 0, "m": 0, "d": 0}
    LVL_4 = {"p": 4, "l": 1, "d": 1, "s": 2, "ph": 1, "t": 0, "m": 0}
    LVL_5 = {"p": 4, "l": 1, "d": 2, "s": 1, "m": 3, "ph": 0, "t": 0}
    LVL_6 = {"p": 6, "l": 1, "d": 2, "s": 3, "ph": 1, "t": 0, "m": 0}
    LVL_7 = {"p": 6, "l": 2, "d": 2, "s": 2, "m": 2, "ph": 2, "t": 1}

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
        self._inventory = {"f": 10, "l": 0, "d": 0, "s": 0, "m": 0, "ph": 0, "t": 0}
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
        # print(id)
        for i in self.inv_other_player:
            if i["id"] == int(id):
                # print("True")
                return True
        # print("False")
        return False

    def drop_all_ressources(self):
        for ressource in self._inventory:
            print(ressource)
            tmp = 0
            while self._inventory[ressource] > 0 and ressource != "f" and tmp <= 4:
                # print(f"ressource = {ressource}")
                self.set(ressource)
                tmp += 1

    def update_inventory_other_player(self, message):
        # print("bizzare")
        # print(message)
        message = message.split(' ')
        # print(message[-1].split('\n'))
        message[-1] = message[-1].split('\n')[0]
        # print(f"deb self.inv_other_player = {self.inv_other_player}")
        if self.player_is_in_inventory(message[0]) == False:
            self.inv_other_player.append({"id": int(message[0]), "level": 0, "inventory": {"f": 0, "l": 0, "d": 0, "s": 0, "m": 0, "ph": 0, "t": 0}})

        for i in self.inv_other_player:
            if i["id"] == int(message[0]):
                i["level"] = int(message[1])
                i["inventory"]["f"] = int(message[2])
                i["inventory"]["l"] = int(message[3])
                i["inventory"]["d"] = int(message[4])
                i["inventory"]["s"] = int(message[5])
                i["inventory"]["m"] = int(message[6])
                i["inventory"]["ph"] = int(message[7])
                if not(message[8].isnumeric()):
                    message[8] = message[8].split('\n')[0]
                i["inventory"]["t"] = int(message[8])
    
        # print(f"fin self.inv_other_player = {self.inv_other_player}")
        

    def get_distance(self, x, y):
        dx = abs(self.x - x)
        dy = abs(self.y - y)

        wrapped_dx = min(dx, self.max_x - dx)
        wrapped_dy = min(dy, self.max_y - dy)

        return wrapped_dx + wrapped_dy

    def forward(self):
        # print("Forward")
        self.socket.send("Forward")
        print("Send Forward")
        self.socket.receive(self)
        print("Receive Forward")
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
        # print("Right")
        self.socket.send("Right")
        self.socket.receive(self)
        self.orientation += 1
        if self.orientation > Orientation.WEST:
            self.orientation = Orientation.NORTH

    def fork(self):
        self.socket.send("Fork")
        self.socket.receive(self)

    def left(self):
        # print("Left")
        self.socket.send("Left")
        self.socket.receive(self)
        self.orientation -= 1
        if self.orientation < Orientation.NORTH:
            self.orientation = Orientation.WEST

    def look(self):
        # print("Look")
        self.socket.send("Look")
        self.socket.receive(self)
        print(self.socket.buffer)
        while self.socket.buffer == "ko\n" or self.socket.buffer.split(" ")[0] == "Current":
            self.socket.send("Look")
            self.socket.receive(self)
            print("Tourn")
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
        # print(self.vision)
        print(f"len(self.vision) = {len(self.vision)}")
        level_len = [4, 9, 16, 25, 36, 49, 64, 81, 100]
        if len(self.vision) != level_len[self.level - 1]:
            print("Look Failed")
            return []
        for i in range(len(self.vision)):
            self.vision[i] = self.vision[i].split(' ')
        print(self.vision)
        self.find_pos_of_look()
        return self.vision_with_pos

    def find_pos_of_look(self):
        self.vision_with_pos = []
        floor = 0
        pos_vision = 0

        for c,i in enumerate(range(1, 2*self.level + 2, 2)):
            print(f"c = {c}, i = {i}")
            for x in range(i):
                print(f"x = {x}")
                if x + 1 < i/2:
                    self.set_object_pos(-c+x, floor, pos_vision)
                elif x + 1 == ceil(i/2):
                    self.set_object_pos(0, floor, pos_vision)
                else:
                    self.set_object_pos(abs(c-x), floor, pos_vision)
                pos_vision += 1
            floor += 1

    def set_object_pos(self, move, floor, i):

        print(f"move = {move}, floor = {floor}, i = {i}")
        print(f"self.vision = {self.vision}")
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
        message += str(self.level) + " "
        for key, value in self._inventory.items():
            message += f"{value}"
            if key != "t":
                message += " "
        return message

    def broadcast(self, message):
        print(f"id{self.id} send this message : {message}")
        self.socket.send(f"Broadcast {message}")
        self.socket.receive(self)
        if message == "Ready":
            self.socket.receive(self)

    def inventory(self):
        # print("Inventory")
        self.socket.send("Inventory")
        self.socket.receive(self)
        return self._inventory

    def take(self, item):
        # print(f"Take {item}")
        self.socket.send(f"Take {item}")
        self.socket.receive(self)
        if self.socket.buffer == "ok\n":
            self._inventory[item] += 1
            return SUCESS
        return FAIL

    def set(self, item):
        # print(f"Set {item}")
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
        elif self.socket.buffer.split(' ')[0] == "Elevation":
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
        tmp = 0
        while (self.orientation != Orientation.EAST):
            self.left()
        while int(self.incantation_direction) != 0:
            print("ppase")
            print(f"self.x = {self.x}, self.max_x = {self.max_x}, tmp = {tmp}")
            if (self.x == self.max_x) and tmp == 0:
                print("la")
                self.left()
                print("stuckere")
                self.forward()
                print("stuck")
                self.left()
                tmp = 1
            elif (self.x == 0) and tmp == 1:
                print("ici")
                self.right()
                print("stuc")
                self.forward()
                print("stucke")
                self.right()
                tmp = 0
            else:
                print("forward")
                self.forward() #Stuck ici * 2
            print("move over ")
            for i in range(5):
                print("Call inventory 1")
                self.inventory()
            print("Incantaton in progress")

        for i in range(5):
            print("Call inventory")
            self.inventory()
        print("Incantaton passed")
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
        print(f" ok {int(self.incantation_direction)}")
        print("Droopp all")
        self.drop_all_ressources()
        print(f" ok {int(self.incantation_direction)}")

        print("Ready")
        self.broadcast("Ready")
        # print(self.look()[0])

    def call_for_incantation(self, direction, message):
        for i in message:
            print(f"i = {i}, self.id = {self.id}")
            if int(i) == self.id:
                self.incantation_direction = direction
                self.go_to_direction()
