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
  string desc, name;
  int type, prop, id;

  Item(int _id) {

    // 0: none
    // 1: puzzle
    // 2: consumable
    // 3: weraable
    // 4: weapon

    id = _id;

    switch (_id) {
    case 0:
      name = "Empty";
      type = 0;
      desc = "Your bare hands";
      prop = 0;
      break;
    case 1:
      name = "Broken Sword";
      type = 3;
      desc = "An old, rusty sword. Broken halfway, and covered in dried "
             "blood... Better than nothing.";
      prop = 5;
      break;
    default:
      name = "Buuugin";
      break;
    }
  };
};
