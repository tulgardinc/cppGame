#include <algorithm>
#include <array>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

#include "header.h"

#pragma once

class Item {
public:
  string desc, name, dia;
  int type, prop, id;
};

class BrokenSword : public Item {
public:
  BrokenSword();
};

class HealthPotion : public Item {
public:
  HealthPotion();
};

class BrokenHelmet : public Item {
public:
  BrokenHelmet();
};

class Crowbar : public Item {
public:
  Crowbar();
};
