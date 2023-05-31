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
            return None
        self.buffer += buff.decode()

    def close(self):
        self._sock.close()
        sys.exit(0)

