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
  int maxHealth;
  int curHealth;
  int def = 0;
  vector<Item *> inv;
  array<Item *, 4> clothes;
  Room *curRoom;
  Item *eqp;

  Player(int _health, vector<Item *> _inv, array<Item *, 4> _clothes, Item* _eqp);

  Item* findItemInv(string name);

  void removeFromInv(Item* i);

  void moveTo(Room *room);

  void takeDamage(int dmg);

  void use(string name);

  void takeItem(string name);

  void equipItem(string name);

  void check();

  void inspect(string name);

  void calcDef();

  void unequip(string name);

  void discard(string name);
};

extern Player player;
