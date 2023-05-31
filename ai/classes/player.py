##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## player
##

from socket import *

class Orientation:
    NORTH = 0
    EAST = 1
    SOUTH = 2
    WEST = 3

class Player:
    def __init__(self, socket):
        self.x = 0
        self.y = 0
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
        print(buff)
        self.vision = buff.split(',')
        for i in range(len(self.vision)):
            self.vision[i] = self.vision[i].split(' ')
        self.socket.buffer = ""
