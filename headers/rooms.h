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
  void setValues(string _n, vector<Obj *> _o, vector<Item *> _i); 
};

class TestL : public Room {
public:
  TestL();

  void init(); 
};
