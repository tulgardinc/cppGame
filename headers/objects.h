#include <algorithm>
#include <array>
#include <iostream>
#include <stdlib.h>
#include <vector>

#include "header.h"
#include "item.h"

using namespace std;

#pragma once

class Obj {
public:
  string name;
  void setName(string n);
};

class Chest : public Obj {
public:
  vector<Item *> content;
  bool isOpen;

  Chest(vector<Item *> _content, bool _open);

  void open();
};
