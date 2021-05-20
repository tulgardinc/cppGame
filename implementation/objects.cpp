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

void Obj::setName(string n) { name = n; }

Chest::Chest(vector<unique_ptr<Item>> _content, bool _open) {
  setName("chest");
  content = move(_content);
  isOpen = _open;
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
}
