#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <vector>

#include "../headers/entity.h"
#include "../headers/rooms.h"

using namespace std;

void Entity::death() {
  if (loot.size() != 0) {
    cout << "the " << name << " drops:" << endl;
    for (auto & i : loot) {
      cout << i->name << endl;
      curRoom->items.push_back(move(i));
    }
  }
  vector<shared_ptr<Entity>>& _vec = curRoom->entities;
  auto _tmp = find_if(_vec.begin(), _vec.end(), [&] (shared_ptr<Entity> e) {
    return e.get() == this;
  });

  _vec.erase(_tmp);
}

void Entity::movePointer(shared_ptr<Room>& nextRoom) { 
  vector<shared_ptr<Entity>>& _vec = curRoom->entities;
  auto _tmp = find_if(_vec.begin(), _vec.end(), [&] (shared_ptr<Entity> e) {
    return e.get() == this;
  });

  nextRoom->entities.insert(nextRoom->entities.begin(), *_tmp);

  _vec.erase(_tmp);
}
