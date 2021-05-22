#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <vector>

#include "header.h"
#include "item.h"

using namespace std;

#pragma once

class Obj {
public:
  string name;
  bool canBeUsed = false;
  bool isUsed = false;
  virtual void use(unique_ptr<Item> item) = 0;
  virtual void inspect() = 0;
};

class Chest : public Obj {
public:
  vector<unique_ptr<Item>> content;
  bool isOpen;

  Chest(vector<unique_ptr<Item>> _content, bool _open);

  void open();
  void use(unique_ptr<Item>) {};
  void inspect();
};

class TrapDoor : public Obj {
public:
  TrapDoor(bool _isUsed);
  void use(unique_ptr<Item>);
  void inspect();
};
