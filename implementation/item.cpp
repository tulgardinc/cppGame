#include <algorithm>
#include <array>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

#include "../headers/header.h"
#include "../headers/item.h"

Item::Item(int _id) {

  // types:
  // 0: puzzle
  // 1: consumable
  // 2: weapon
  // 3: helmet
  // 4: torso
  // 5: leggings
  // 6: shoes

  id = _id;

  switch (_id) {
  case 0:
    name = "Broken Sword";
    type = 2;
    desc = "An old, rusty sword. Broken halfway, and covered in dried "
           "blood... Better than nothing.";
    prop = 5;
    break;
  case 1:
    name = "Health Potion";
    type = 1;
    desc = "A potion used to rapidly heal wounds. It is not the strongest but "
           "it will do.";
    dia = "You applied the health potion to your wounds. It sooths your pane.";
    prop = 5;
    break;
  case 2:
    name = "Helmet";
    type = 3;
    desc = "Old style knight helmet. Its rusted, the face guard is split in half, and the inside is covered in old, dried blood ";
    dia = "You applied the health potion to your wounds. It sooths your pane.";
    prop = 25;
    break;
  default:
    name = "Buuugin";
    break;
  }
};
