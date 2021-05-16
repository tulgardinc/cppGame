#include <algorithm>
#include <array>
#include <iostream>
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
  vector<Obj *> objects;
  vector<Item *> items;
  virtual void init() = 0;
  void setValues(string _n, vector<Obj *> _o, vector<Item *> _i) {
    name = _n;
    objects = _o;
    items = _i;
  }
};

class TestL : public Room {
public:
  TestL() {
    // Setup the contents
    Item *sword = new Item(1);
    Chest *chest = new Chest({sword}, false);
    vector<Obj *> _objects{chest};
    setValues("TestL", _objects, vector<Item *>());
  }

  void init() {
    cout << "You wake up in a dark dungeon" << endl;
    cout << "You see a chest in front of you" << endl;
    prompt();
  }
};
