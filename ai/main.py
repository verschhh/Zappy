#!/usr/bin/env python3

import socket
import sys

def check_args(av, ac):
    nb_param = 0

    for i in range(ac):
        if av[i] == "-p" or av[i] == "-n" :
            nb_param += 1
        if av[i] == "-p" and (av[i + 1].isdigit() == False or int(av[i + 1]) < 0):
            print("Error: port must be a positive number")
            return 84
        if av[i] == "-n" and av[i + 1].isalpha() == False:
            print("Error: name must be a string")
            return 84
        if av[i] == "-h" and av[i + 1].isalpha() == False:
            print("Error: machine must be a string")
            return 84

    if nb_param != 2:
        print("Error: parameters -p and -n are required")
        return 84
    return 0


def set_args(av, ac):
    port = 0
    name = ""
    machine = ""

    for i in range(ac):
        if av[i] == "-p":
            port = int(av[i + 1])
        if av[i] == "-n":
            name = av[i + 1]
        if av[i] == "-h":
            machine = av[i + 1]
    if machine == "":
        machine = "localhost"
    return port, name, machine

def main(av, ac):
    if ac == 2 and av[1] == "-help":
        print("USAGE: ./zappy_ai -p port -n name -h machine")
        print("\tport\tis the port number")
        print("\tname\tis the name of the team")
        print("\tmachine\tis the name of the machine; localhost by default")
        return 0
    elif ac == 7 or ac == 5:
        if check_args(av, ac) == 84:
            return 84
        port, team_name, host = set_args(av, ac)
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((host, port))
            s.sendall("Hello world".encode('utf-8'))
            buff = s.recv(512)
            print(buff.decode())
        print("port: " + av[2])
    else:
        print("USAGE: ./zappy_ai -help")
        return 84

if __name__ == "__main__":
    if main(sys.argv, len(sys.argv)) == 84:
        sys.exit(84)