#include <algorithm>
#include <array>
#include <iostream>
#include <stdlib.h>
#include <vector>

#include "../headers/header.h"
#include "../headers/item.h"
#include "../headers/objects.h"
#include "../headers/rooms.h"

using namespace std;

void Room::setValues(string _n, vector<Obj *> _o, vector<Item *> _i) {
    name = _n;
    objects = _o;
    items = _i;
}

TestL::TestL() {
    // Setup the contents
  Chest *chest = new Chest({new Item(0), new Item(2)}, false);
    vector<Obj *> _objects{chest};
    setValues("TestL", _objects, vector<Item *>());
  }

void TestL::init() {
    cout << "You wake up in a dark dungeon" << endl;
    cout << "You see a chest in front of you" << endl;
    prompt();
  }
