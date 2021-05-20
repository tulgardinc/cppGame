#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdlib.h>
#include <vector>

#include "../headers/header.h"
#include "../headers/item.h"
#include "../headers/objects.h"
#include "../headers/rooms.h"

using namespace std;

vector<shared_ptr<Room>> roomVec;

void Room::addToRoomVec(shared_ptr<Room> room) { roomVec.push_back(room); }

void Room::setValues(string _n, vector<unique_ptr<Obj>> _o,
                     vector<unique_ptr<Item>> _i) {
  name = _n;
  objects = move(_o);
  items = move(_i);
  shared_ptr<Room> temp;
  temp.reset(this);
  addToRoomVec(temp);
}

TestL::TestL() {
  // Setup the contents
  unique_ptr<Item> _items[] = {make_unique<Item>(0), make_unique<Item>(2)};
  vector<unique_ptr<Item>> _content{make_move_iterator(begin(_items)),
                                    make_move_iterator(end(_items))};

  unique_ptr<Obj> chest = make_unique<Chest>(move(_content), false);
  vector<unique_ptr<Obj>> _objects;
  _objects.push_back(move(chest));

  setValues("TestL", move(_objects), move(vector<unique_ptr<Item>>()));
}

void TestL::init() {
  cout << "You wake up in a dark dungeon" << endl;
  cout << "You see a chest in front of you" << endl;
  prompt();
}
