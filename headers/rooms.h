#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <vector>

#include "header.h"
#include "item.h"
#include "objects.h"

using namespace std;

#pragma once

class Entity;

class Room {
public:
  string name;
  vector<shared_ptr<Obj>> objects;
  vector<unique_ptr<Item>> items;
  array<shared_ptr<Obj>, 4> blocks{}; // n e s w
  vector<shared_ptr<Entity>> entities{};
  bool visited = false;
  int x, y;
  virtual void init() = 0;
  virtual void look() = 0;
  shared_ptr<Obj> findObject(string name);
  shared_ptr<Entity> findEntity(string name);
  void printItems();
  void listEnemies();
  void addToRoomVec(shared_ptr<Room> room);
  void setValues(string _n, vector<shared_ptr<Obj>> _o,
                 vector<unique_ptr<Item>> _i, vector<shared_ptr<Entity>> _e);
};

extern array<array<shared_ptr<Room>, 5>, 5> gameMap;

extern shared_ptr<Room> & getRoomFromMap(int _x, int _y);

class TestL : public Room {
public:
  TestL();
  void init();
  void look();
};

class HiddenL : public Room {
public:
  HiddenL();
  void init();
  void look();
};

class TestrL : public Room {
public:
  TestrL() {name = "right";};
  void init() {};
  void look() {};
};

class TestlL : public Room {
public:
  TestlL() {name = "left";};
  void init() {};
  void look() {};
};

class TestuL : public Room {
public:
  TestuL();
  void init();
  void look();
};

class TestdL : public Room {
public:
  TestdL() {name = "down";};
  void init() {};
  void look() {};
};
