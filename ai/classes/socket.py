##
## EPITECH PROJECT, 2022
## B-YEP-400-BER-4-1-zappy-kentin.paille
## File description:
## classes.py
##

import socket
import sys

class Socket:
    def __init__(self, port, name, machine):
        self._port = port
        self._name = name
        self._machine = machine
        self._sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.buffer = ""

    def connect(self):
        try :
            self._sock.connect((self._machine, self._port))
        except socket.error as msg:
            print("Couldnt connect with the socket-server: %s\nTerminating program" % msg)
            sys.exit(84)

    def send(self, message):
        self._sock.sendall((message+"\n").encode())
        self.buffer = ""

    def receive(self, player):
        buff = self._sock.recv(4096)
        print(f"buff = {buff}")
        if not buff:
            print("Server disconnected")
            sys.exit(10)
        elif buff.decode() == "dead\n":
            print("You died")
            sys.exit(1)
        elif buff.decode().split(' ')[0] == "message":
            buff = buff.decode().split(',')
            # print(f"Message received {buff}")
            if player.level > 1:
                print(buff)
                if buff[1] == " Inventory":
                    print("Updating inventory")
                    player.update_inventory_other_player(buff[2])
                    print("Updated inventory")
                elif buff[1] == " Ready\n":
                    print("Player ready")
                    player.nb_joueur_ready += 1
                elif buff[1] == " Incantation":
                    print("Incantation launched")
                    print(f"buff[0].split(' ')[1] = {buff[0].split(' ')[1]}, buff[2] = {buff[2].split(' ')}")
                    player.call_for_incantation(buff[0].split(" ")[1], buff[2].split(' ')[:-1])
                    print("Incantation finished")
                elif buff[1] == " Here\n":
                    print(f"New direction ;{buff[0].split(' ')[1]};")
                    player.incantation_direction = int(buff[0].split(' ')[1])
            self.buffer = ""
            self.receive(player)

        else:
            self.buffer += buff.decode()
            if self.buffer.split(' ')[0] == "Current":
                player.level += 1
                print(player.level)
            if player.level == 3:
                exit(333)
            

    def close(self):
        self._sock.close()
        sys.exit(99)

