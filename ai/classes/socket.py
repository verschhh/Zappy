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

    def receive(self):
        buff = self._sock.recv(4096)
        if not buff:
            print("Server disconnected")
            sys.exit(10)
        elif buff.decode() == "dead\n":
            print("You died")
            sys.exit(1)
        elif buff.decode().split(' ')[0] == "message":
            print("Message from %s: %s" % (buff.decode().split(' ')[1], buff.decode().split(' ')[2]))
            self.buffer = ""
            self.receive()
        elif buff.decode().split(':')[0] == "eject":
            print
        else:
            self.buffer += buff.decode()

    def close(self):
        self._sock.close()
        sys.exit(99)

