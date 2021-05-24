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
#include "../headers/player.h"
#include "../headers/rooms.h"
#include "../headers/goblin.h"

using namespace std;

vector<shared_ptr<Room>> roomVec;

shared_ptr<Room> &getRoomFromMap(int _x, int _y) {
  // y first x second
  // y decreases as we go north
  // this solves that
  return gameMap[gameMap.size() - _y - 1][_x];
}

void Room::listEnemies() {
  for (auto & e : entities) {
    if (e->isEnemy) {
      cout << "There is a " << e->name << " (" << e->curHealth << "/" << e->maxHealth << " HP) Here!" << endl;
    }
  }
}

void Room::setValues(string _n, vector<shared_ptr<Obj>> _o,
                     vector<unique_ptr<Item>> _i, vector<shared_ptr<Entity>> _e) {
  name = _n;
  objects = move(_o);
  items = move(_i);
  entities.insert(entities.end(), _e.begin(), _e.end());
}

shared_ptr<Obj> Room::findObject(string name) {
  for (auto &o : objects) {
    if (o->name == name) {
      return o;
    }
  }
  return nullptr;
}

shared_ptr<Entity> Room::findEntity(string name) {
  for (auto &e : entities) {
    if (e->name == name) {
      return e;
    }
  }
  return nullptr;
}

void Room::printItems() {
  for (auto &i : items) {
    cout << i->name << endl;
  }
}

TestL::TestL() {
  // Setup the contents
  unique_ptr<Item> _items[] = {make_unique<Crowbar>(),
                               make_unique<BrokenHelmet>()};
  vector<unique_ptr<Item>> _content{make_move_iterator(begin(_items)),
                                    make_move_iterator(end(_items))};

  shared_ptr<Obj> chest = make_shared<Chest>(move(_content), false);
  vector<shared_ptr<Obj>> _objects{chest};

  setValues("TestL", _objects, move(vector<unique_ptr<Item>>()), {});
}

void TestL::init() {
  clearScr();
  cout << "You wake up in a dark dungeon" << endl;
  cout << "You see a chest in front of you" << endl;
}

void TestL::look() {
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

// ===== TestuL ===== //

TestuL::TestuL() {
  shared_ptr<Obj> trapDoor = make_shared<TrapDoor>(false);
  setValues("Testup", vector<shared_ptr<Obj>>{trapDoor},
            vector<unique_ptr<Item>>{}, {});
  blocks[0] = trapDoor;
}

void TestuL::init() {
  clearScr();
  cout << "You move in to what seems like an unfinished area..." << endl;
  cout
      << "The walls have no texture and your feet are clipping trough the floor"
      << endl;
  cout << endl;
  cout << "On the other end of the room you can see a trapdoor" << endl;
}

void TestuL::look() {
  cout << "Buuugin room with a trapdoor." << endl;
  if (findObject("trapdoor")->isUsed) {
    cout << "It has been opened.";
  }
}

// ===== HiddenL ===== //

HiddenL::HiddenL() {
}

void HiddenL::init() {

  vector<unique_ptr<Item>> _content;
  shared_ptr<Obj> chest = make_shared<Chest>(move(_content), false);
  setValues("Testup", vector<shared_ptr<Obj>>{chest},
            vector<unique_ptr<Item>>{}, {make_shared<Goblin>(5, vector<unique_ptr<Item>>{}, make_unique<BrokenSword>(), x, y)});


  clearScr();
  cout << "You pass trough the trapdoor into a dark room with stains on the "
          "walls."
       << endl;
  cout << "You can see a chest at the very end of the room." << endl;
  cout << "Oh shoot a goblin emerges from the dark!" << endl;
}

void HiddenL::look() {
  cout << "Spooky room with a chest inside." << endl;
  shared_ptr<Chest> c;
  {
    shared_ptr<Obj> _o = findObject("chest");
    c = static_pointer_cast<Chest>(_o);
  }
  if (c->isOpen) {
    cout << "It has been opened.";
  }
}
