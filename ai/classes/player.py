##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## player
##

from socket import *

SUCESS = 0
FAIL = 84
class Orientation:
    NORTH = 0
    EAST = 1
    SOUTH = 2
    WEST = 3

class Player:
    def __init__(self, socket, game):
        self.x = 0
        self.y = 0
        self.max_x = game.map_size_x
        self.max_y = game.map_size_y
        self.level = 1
        self.inventory = {"food": 10, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
        self.team = ""
        self.orientation = Orientation.NORTH
        self.socket = socket
        self.vision = []

    def forward(self):
        self.socket.send("Forward")
        if self.orientation == Orientation.NORTH:
            self.y -= 1
        elif self.orientation == Orientation.EAST:
            self.x += 1
        elif self.orientation == Orientation.SOUTH:
            self.y += 1
        elif self.orientation == Orientation.WEST:
            self.x -= 1
        if self.x < 0:
            self.x = self.max_x - 1
        elif self.x >= self.max_x:
            self.x = 0
        if self.y < 0:
            self.y = self.max_y - 1
        elif self.y >= self.max_y:
            self.y = 0

    def right(self):
        self.socket.send("Right")
        self.orientation += 1
        if self.orientation > Orientation.WEST:
            self.orientation = Orientation.NORTH

    def left(self):
        self.socket.send("Left")
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

    def eject(self):
        self.socket.send("Eject")
        self.socket.receive()
        buff = self.socket.buffer
        if buff == "ok":
            return SUCESS
        else:
            return FAIL

    def fork(self):
        self.socket.send("Fork")
        self.socket.receive()

    def connect_nbr(self):
        self.socket.send("Connect_nbr")
        self.socket.receive()
        buff = self.socket.buffer
        return int(buff)

    def broadcast(self, message):
        self.socket.send(f"Broadcast {message}")
        self.socket.receive()

    def take(self, item):
        self.socket.send(f"Take {item}")
        self.socket.receive()
        buff = self.socket.buffer
        if buff == "ok":
            self.inventory[item] += 1
            return SUCESS
        else:
            return FAIL

    def set(self, item):
        self.socket.send(f"Set {item}")
        self.socket.receive()
        buff = self.socket.buffer
        if buff == "ok":
            self.inventory[item] -= 1
            return SUCESS
        else:
            return FAIL

    def incantation(self):
        self.socket.send("Incantation")
        self.socket.receive()
        buff = self.socket.buffer
        if buff == "Elevation underway":
            self.level += 1
        else:
            return FAIL
