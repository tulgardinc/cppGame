#include <algorithm>
#include <array>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

#include "header.h"
#include "item.h"
#include "objects.h"
#include "rooms.h"

#pragma once

class Player {
public:
  int health;
  vector<Item *> inv;
  vector<Item *> clothes;
  Room *curRoom;
  Item *eqp;

  Player(int _health, vector<Item *> _inv, vector<Item *> _clothes)
      : health(_health), inv(_inv), clothes(_clothes), eqp(0) {}

  void moveTo(Room *room) {
    curRoom = room;
    room->init();
  }

  void takeDamage(int dmg) {
    // hurt the player
    health -= dmg;
  }

  void consume(Item *item) {
    // add the effect to heatlh
    health += item->prop;
    // remove consumed item from inventory
    inv.erase(find(inv.begin(), inv.end(), item));
  }

  void takeItem(Item *item) {
    // add item to inventory
    inv.push_back(item);
  }

  void equipItem(Item *item) {
    // Check if the item that is being equiped is within the inventory
    if (find(inv.begin(), inv.end(), item) != inv.end()) {
      // if it is in the inventory:
      // remove it from the inventory
      inv.erase(find(inv.begin(), inv.end(), item));

      // check if the equiment is not empty
      if (eqp->type != 0) {
        // if it is not empty return it to the inventory
        inv.push_back(eqp);
      }

      // equip the item
      eqp = item;

    } else {
      // if the item is not in the inventory do nothing
      cout << item->name << " Is not in your inventory." << endl;
    }
  }
};

extern Player player;
