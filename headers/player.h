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

  void moveDir(string dir);

  void takeDamage(int dmg);

  void use(string name);

  void useOn(string param1, string param2);

  void takeItem(string name);

  void equipItem(string name);

  void check();

  void inspect(string name);

  void calcDef();

  void unequip(string name);

  void discard(string name);

  void attack(string name);

  void action();
};

extern shared_ptr<Player> player;

extern bool game;
