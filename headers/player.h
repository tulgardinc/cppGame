#ifndef PLAYER_H
#define PLAYER_H

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

  Player(int _health, vector<Item *> _inv, vector<Item *> _clothes);

  void moveTo(Room *room);

  void takeDamage(int dmg);

  void consume(Item *item);

  void takeItem(Item *item);

  void equipItem(Item *item);
};

extern Player player;

#endif
