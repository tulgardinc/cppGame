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
  void setName(string n) { name = n; }
};

class Chest : public Obj {
public:
  vector<Item *> content;
  bool open;

  Chest(vector<Item *> _content, bool _open) {
    setName("chest");
    content = _content;
    open = _open;
  }
};
