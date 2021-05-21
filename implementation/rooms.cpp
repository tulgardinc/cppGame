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
#include "../headers/player.h"

using namespace std;

vector<shared_ptr<Room>> roomVec;

void Room::addToRoomVec(shared_ptr<Room> room) { roomVec.push_back(room); }

void Room::setValues(string _n, vector<shared_ptr<Obj>> _o,
                     vector<unique_ptr<Item>> _i) {
  name = _n;
  objects = move(_o);
  items = move(_i);
  shared_ptr<Room> temp;
  temp.reset(this);
  addToRoomVec(temp);
}

shared_ptr<Obj> Room::findObject(string name) {
  for (auto & o : objects) {
    if (o->name == name) {
      return o;
    }
  }
  return nullptr;
}

void Room::printItems() {
  for (auto & i : items) {
    cout << i->name << endl;
  }
}

TestL::TestL() {
  // Setup the contents
  unique_ptr<Item> _items[] = {make_unique<Item>(0), make_unique<Item>(2)};
  vector<unique_ptr<Item>> _content{make_move_iterator(begin(_items)),
                                    make_move_iterator(end(_items))};

  shared_ptr<Obj> chest = make_shared<Chest>(move(_content), false);
  vector<shared_ptr<Obj>> _objects{chest};

  setValues("TestL", _objects, move(vector<unique_ptr<Item>>()));
}

void TestL::init() {
  cout << "You wake up in a dark dungeon" << endl;
  cout << "You see a chest in front of you" << endl;
  prompt();
}

void TestL::look() {
  cout << "You look around the room" << endl;
  cout << endl;
  cout << "It is a dark and dank cave." << endl;
  cout << "There is a chest. It is ";
  shared_ptr<Chest> c;
  {
    shared_ptr<Obj> _c = findObject("chest");
    c = static_pointer_cast<Chest>(_c);
  }
  
  if (c->isOpen) {
    cout << "open." << endl;
  } else {
    cout << "closed." << endl;
  }
  cout << endl;
  if (items.size() > 0) {
    cout << "There are a few items of use here" << endl;
    cout << endl;
    printItems();
    cout << endl;
  } else {
    cout << "There are no items to take here." << endl;
  }
}
