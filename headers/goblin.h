#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <vector>

using namespace std;

#include "header.h"
#include "item.h"
#include "objects.h"
#include "entity.h"
#include "rooms.h"

#pragma once

class Goblin:  public Entity {
public:
  vector<unique_ptr<Item>> loot;
  unique_ptr<Item> eqp;

  Goblin(int _maxHealth, vector<unique_ptr<Item>> _loot, unique_ptr<Item> _eqp, int _x, int _y);

  void attack();
  void takeDamage(int dmg);
  void action();
};
