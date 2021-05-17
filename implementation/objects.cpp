#include <algorithm>
#include <array>
#include <iostream>
#include <stdlib.h>
#include <vector>

#include "../headers/header.h"
#include "../headers/item.h"
#include "../headers/objects.h"

using namespace std;

void Obj::setName(string n) { name = n; }

Chest::Chest(vector<Item *> _content, bool _open) {
    setName("chest");
    content = _content;
    open = _open;
  }
