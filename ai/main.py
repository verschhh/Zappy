#!/usr/bin/env python3
##
## EPITECH PROJECT, 2022
## B-YEP-400-BER-4-1-zappy-kentin.paille
## File description:
## main.py
##


##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## main
##



import socket
import sys
from time import sleep

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

def print_usage():
    print("USAGE: ./zappy_ai -help || -p [port] -n [name] -h [machine]")
    print("\t[port]\tis the port number")
    print("\t[name]\tis the name of the team")
    print("\t[machine]\tis the name of the machine; localhost by default")

def main(av, ac):
    if ac == 2 and av[1] == "-help":
        print_usage()
        return 0
    elif ac == 7 or ac == 5:
        if check_args(av, ac) == 84:
            return 84
        port, team_name, host = set_args(av, ac)
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((host, port))
            buff = s.recv(512)
            print(buff.decode())
            s.sendall((team_name + "\n").encode())
            buff = s.recv(512)
            print(buff.decode())
            message = input("-> ")
            while message != "quit":
                s.sendall((message+"\n").encode())
                buff = s.recv(4096)
                if not buff:
                    break
                print(buff.decode())
                sleep(1)
                message = input("-> ")
            s.close()

    else:
        print_usage()
        return 84

if __name__ == "__main__":
    if main(sys.argv, len(sys.argv)) == 84:
        sys.exit(84)