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

class Room {
public:
  string name;
  vector<shared_ptr<Obj>> objects;
  vector<unique_ptr<Item>> items;
  virtual void init() = 0;
  virtual void look() = 0;
  shared_ptr<Obj> findObject(string name);
  void printItems();
  void addToRoomVec(shared_ptr<Room> room);
  void setValues(string _n, vector<shared_ptr<Obj>> _o,
                 vector<unique_ptr<Item>> _i);
};

extern vector<shared_ptr<Room>> roomVec;

class TestL : public Room {
public:
  TestL();
  void init();
  void look();
};
