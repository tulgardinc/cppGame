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

  Item(int _id);
};
