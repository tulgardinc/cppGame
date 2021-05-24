#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <vector>

#pragma once

using namespace std;

class Room;
class Item;

class Entity {
 public:
  shared_ptr<Room> curRoom;
  vector<unique_ptr<Item>> loot;
  string name;
  bool isEnemy;
  int curHealth, maxHealth, x, y;

  void death();
  void movePointer(shared_ptr<Room>& nextRoom);
  virtual int action() = 0; 
  virtual void takeDamage(int dmg) = 0;
};
