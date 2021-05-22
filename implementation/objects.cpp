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

using namespace std;


// ======= Chest ======= // 

Chest::Chest(vector<unique_ptr<Item>> _content, bool _open) {
  name = "chest";
  content = move(_content);
  isOpen = _open;
}

void Chest::inspect() {
  cout << "An old wooden chest with no lock on it." << endl;
}

void Chest::open() {

  if (isOpen) {
    cout << "Chest is already open." << endl;
    return;
  }

  cout << "You move over to the chest and open it." << endl;
  cout << "Inside you can see..." << endl;
  cout << endl;
  cout << "----+---+---+----" << endl;

  for (auto &item : content) {
    cout << item->name << endl;
  }
  cout << "----+---+---+----" << endl;

   vector<unique_ptr<Item>> &roomItems = player.curRoom->items;
   roomItems.insert(roomItems.end(), make_move_iterator(content.begin()), make_move_iterator(content.end()));
   isOpen = true;
}

// ======= Trap Door ======= //

TrapDoor::TrapDoor(bool _isUsed) {
  name = "trapdoor";
  canBeUsed = true;
  isUsed = _isUsed;
}

void TrapDoor::inspect() {
  cout << "Thick wooden trapdoor with a metal lock." << endl;
  if (!isUsed) {
    cout << "Could probably be wedged open with something..." << endl;
  }
}

void TrapDoor::use(unique_ptr<Item> item) {
  if (_toLower(item->name) == "crowbar") {
    isUsed = true;
    cout << "Your crowbar broke, but you managed to open the trap door." << endl;
  } else {
    cout << "Cant use this here." << endl;
    player.inv.push_back(move(item));
  }
}
