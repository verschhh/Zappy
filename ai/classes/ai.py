##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## ai
##

from .player import Priority, Player, Orientation
from .game import Game
import re
from random import randint
from math import sqrt

class Incantation:
    LVL_1 = {"player": 1, "linemate": 1, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
    LVL_2 = {"player": 2, "linemate": 1, "deraumere": 1, "sibur": 1, "phiras": 0, "thystame": 0, "mendiane": 0}
    LVL_3 = {"player": 2, "linemate": 2, "sibur": 1, "phiras": 2, "thystame": 0, "mendiane": 0, "deraumere": 0}
    LVL_4 = {"player": 4, "linemate": 1, "deraumere": 1, "sibur": 2, "phiras": 1, "thystame": 0, "mendiane": 0}
    LVL_5 = {"player": 4, "linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3, "phiras": 0, "thystame": 0}
    LVL_6 = {"player": 6, "linemate": 1, "deraumere": 2, "sibur": 3, "phiras": 1, "thystame": 0, "mendiane": 0}
    LVL_7 = {"player": 6, "linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1}

class AI(Player, Game, Priority, Orientation):
    def __init__(self, socket, x, y):
        Player.__init__(self, socket, x, y)
        Game.__init__(self, x, y)

        
    # * AI Strategy
    def pick_move(self):
        self.update_map(self.look())
        self.update_inventory()
        match self.level:
            case 1:
                self.level_1()
            case 2:
                exit(42)
                self.levels(Incantation.LVL_2)
            case 3:
                self.levels(Incantation.LVL_3)
            case 4:
                self.levels(Incantation.LVL_4)
            case 5:
                self.levels(Incantation.LVL_5)
            case 6:
                self.levels(Incantation.LVL_6)
            case 7:
                self.levels(Incantation.LVL_7)
            case _:
                self.random_move()
        

    def random_move(self):
        foo = randint(0,1)
        if foo == 0:
            self.right()
        elif foo == 1:
            self.left()
        self.forward()

    def check_if_other_player_have_more_ressources(self, inventory):
        for player in self.inv_other_player:
            for ressource in player["inventory"]:
                if player["inventory"][ressource] > inventory[ressource]:
                    return True
        return False

    def check_if_dict_empty(self, dict):
        for i in dict:
            if dict[i] > 0 and i != "player":
                return False
        return True

    def regive_ressources(self, player_select):
        for ressource in player_select[0]["inventory"]:
            while player_select[0]["inventory"][ressource] > 0:
                self._inventory[ressource] += 1
                player_select[0]["inventory"][ressource] -= 1

        for c, player in enumerate(player_select):
            for ressource in player["inventory"]:
                while player["inventory"][ressource] > 0:
                    print(c)
                    self.inv_other_player[c - 1]["inventory"][ressource] += 1
                    player["inventory"][ressource] -= 1

    def check_if_id_in_list(self, id, list):
        for i in list:
            if i["id"] == id:
                return True
        return False

    def check_evolution_possible(self, level) -> list[dict[str, int]]:
        tmp = level.copy()
        player_select = []

        player_select.append({"id": self.id, "inventory": {"food": 0, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}})
        for cle, valeur in self._inventory.items():
            while cle != "food" and tmp[cle] > 0 and valeur > 0:
                player_select[0]["inventory"][cle] += 1
                tmp[cle] -= 1
                valeur -= 1

        for player in self.inv_other_player:
            player_select.append({"id": player["id"], "inventory": {"food": 0, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}})
            for cle, valeur in player["inventory"].items():
                while cle in tmp and tmp[cle] > 0 and cle != "player" and cle != "food" and valeur > 0:
                    if self.check_if_dict_empty(tmp) == True:
                        break
                    player_select[-1]["inventory"][cle] += 1
                    tmp[cle] -= 1
                    valeur -= 1

        if self.check_if_dict_empty(tmp) == False:
            print("bad 1")
            self.regive_ressources(player_select)
            return []

        if len(player_select) == level["player"]:
            print("good")
            return player_select

        elif len(player_select) > level["player"]:
            print("bad 2")
            self.regive_ressources(player_select)
            return []


        for i in self.inv_other_player:
            if self.check_if_id_in_list(i["id"], player_select) == False and len(player_select) < level["player"]:
                player_select.append({"id": i["id"], "inventory": {"food": 0, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}})

        if len(player_select) < level["player"]:
            print("bad 3")
            self.regive_ressources(player_select)
            return []

        print("good")
        return player_select

    def take_id_player_select(self, player_select):
        message = ""
        for player in player_select:
            message += str(player["id"]) + " "
        return message
    
    def nb_player_on_tile(self, title):
        nb = 0
        for i in title:
            if i == "player":
                nb += 1
        return nb

    def levels(self, level):
        if self._inventory["food"] < 40:
            self.fetch_ressources()
        player_select = self.check_evolution_possible(level)
        if player_select != [] and self._inventory["food"] > 100:
            print("Launch Incantation")
            self.broadcast(f"Incantation,{self.take_id_player_select(player_select)}")
            print(f"{self.nb_joueur_ready} level = {level['player']} - 1")
            while self.nb_joueur_ready < level['player'] - 1:
                self.broadcast(f"Here")

            self.drop_all_ressources()
            self.update_map(self.look())
            print(self.map[self.y][self.x])
            self.take_usseless_ressources(level)
            self.update_map(self.look())
            print(self.map[self.y][self.x])
            self.incantation()
            self.nb_joueur_ready = 0
        self.broadcast(self.send_inventory())
        self.fetch_ressources()

    def fetch_ressources(self):
        pos_food = self.nb_ressources_tile(3, "food")
        self.get_next_move(pos_food)
        self.take("food")
        while self.socket.buffer == "ok\n" and self._inventory["food"] < 100:
            self.take("food")
        self.update_inventory()

    def take_usseless_ressources(self, level):
        print(level)
        for ressource in self.map[self.y][self.x]:
            while ressource != "player" and ressource != "food" and self.map[self.y][self.x][ressource] > level[ressource]:
                print(f"ressource = {ressource}")
                self.take(ressource)
                self.map[self.y][self.x][ressource] -= 1
        self.update_inventory()

    def level_1(self):
        pos_limenate = self.nb_ressources_tile(1, "linemate")
        pos_food = self.nb_ressources_tile(2, "food")
        self.update_inventory()
        if pos_limenate != (-1, -1) and self._inventory["food"] > 20:
            self.get_next_move(pos_limenate)
            self.update_map(self.look())
            # print(self.map[self.y][self.x])
            self.take_usseless_ressources(Incantation.LVL_1)
            self.update_map(self.look())
            # print(self.map[self.y][self.x])
            if self.map[self.y][self.x]["player"] > 1:
                self.random_move()
            elif self.incantation() == 84:
                self.random_move()
        elif pos_food != (-1, -1):
            nb_loop = 0
            self.get_next_move(pos_food)
            self.take("food")
            while self.socket.buffer == "ok\n" and nb_loop < 50:
                self.take("food")
                nb_loop += 1
            self.update_inventory()
        else:
            self.random_move()



    def calcul_distance(self, pos1, pos2):
        return sqrt((pos2[0] - pos1[0])**2 + (pos2[1] - pos1[1])**2)

    def nb_ressources_tile(self, nb, ressource):
        distance = float('inf')
        shortest_pos = (-1, -1)

        for y, i in enumerate(self.map):
            for x, _ in enumerate(i):
                if self.map[y][x][ressource] >= nb and self.calcul_distance((self.x, self.y), (x, y)) < distance:
                    shortest_pos = (x, y)
                    distance = self.calcul_distance((self.x, self.y), (x, y))
        return shortest_pos

    def update_inventory(self):
        print("Updating inventory")
        self.socket.send("Inventory")
        self.socket.receive(self)
        print(self._inventory)
        print(self.socket.buffer)
        inventory_regex = r"(\w+)\s+(\d+)"
        matches = re.findall(inventory_regex, self.socket.buffer)
        for item, quantity in matches:
            if item in self._inventory:
                self._inventory[item] = int(quantity)

    def take_ressource_if_possible(self):
        if self.map[self.y][self.x]["player"] > 1:
            return
        for ressource in self.map[self.y][self.x]:
            if self.map[self.y][self.x][ressource] > 0 and ressource != "player" and randint(0, 1) == 1:
                self.take(ressource)
            if ressource == "food":
                self.take("food")
            while ressource == "food" and self.map[self.y][self.x][ressource] > 0 and self.socket.buffer == "ok\n" and self._inventory["food"] < 100 :
                self.take(ressource)


    def get_next_move(self, target_coords):
        while (self.x, self.y) != target_coords:
            x, y = target_coords
            orientation_diff = (self.orientation - self.get_target_orientation(x, y)) % 4
            if orientation_diff == 0:
                self.forward()
            elif orientation_diff == 1 or orientation_diff == -3:
                self.right()
                self.forward()
            else:
                self.left()
                self.forward()
            if self.level != 1:
                self.take_ressource_if_possible()

    def get_target_orientation(self, target_x, target_y):
        dx = (target_x - self.x + (self.max_x + 1)) % (self.max_x + 1)
        dy = (target_y - self.y + (self.max_y + 1)) % (self.max_y + 1)

        if dx < (self.max_x + 1) // 2:
            if dy < (self.max_y + 1) // 2:
                return 0 if dx < dy else 3
            else:
                return 2 if dx < (self.max_y + 1) - dy else 3
        else:
            if dy < (self.max_y + 1) // 2:
                return 0 if (self.max_x + 1) - dx < dy else 1
            else:
                return 2 if (self.max_x + 1) - dx < (self.max_y + 1) - dy else 1



