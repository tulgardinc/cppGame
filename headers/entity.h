#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <vector>

#pragma once

using namespace std;

class Room;

class Entity {
 public:
  shared_ptr<Room> curRoom;
  string name;
  bool isEnemy;
  int curHealth, maxHealth, x, y;

  void death();
  void movePointer(shared_ptr<Room>& nextRoom);
  virtual void action() = 0; 
  virtual void takeDamage(int dmg) = 0;
};
