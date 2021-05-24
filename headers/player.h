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
#include "rooms.h"
#include "entity.h"

#pragma once

class Player: public Entity {
public:
  int def = 0;
  vector<unique_ptr<Item>> inv;
  array<unique_ptr<Item>, 4> clothes;
  unique_ptr<Item> eqp;

  Player(int _health, vector<unique_ptr<Item>> _inv, array<unique_ptr<Item>, 4> _clothes,
               unique_ptr<Item> _eqp);

  unique_ptr<Item> findItemInv(string name);

  void removeFromInv(unique_ptr<Item>& i);

  void init(shared_ptr<Room> room);

  void moveTo( int _y, int _x);

  int moveDir(string dir);

  void takeDamage(int dmg);

  int use(string name);

  void useOn(string param1, string param2);

  int takeItem(string name);

  int equipItem(string name);

  void check();

  int inspect(string name);

  void calcDef();

  void unequip(string name);

  int discard(string name);

  void attack(string name);

  int action();
};

extern shared_ptr<Player> player;

extern bool game;
