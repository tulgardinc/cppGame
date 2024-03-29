#include <algorithm>
#include <array>
#include <features.h>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <vector>

using namespace std;

#include "../headers/header.h"
#include "../headers/item.h"
#include "../headers/objects.h"
#include "../headers/player.h"
#include "../headers/rooms.h"

Player::Player(int _health, vector<unique_ptr<Item>> _inv,
               array<unique_ptr<Item>, 4> _clothes, unique_ptr<Item> _eqp) {
  maxHealth = curHealth = _health;
  clothes = move(_clothes);
  inv = move(_inv);
  eqp = move(_eqp);
  name = "player";
  calcDef();
  isEnemy = false;
};

unique_ptr<Item> Player::findItemInv(string name) {
  for (auto &i : inv) {
    if (_toLower(i->name) == name) {
      return move(i);
    }
  }
  return 0;
}

void Player::calcDef() {
  def = 0;
  for (auto &c : clothes) {
    if (c != nullptr) {
      def += c->prop;
    }
  }
}

void Player::removeFromInv(unique_ptr<Item> &i) {
  inv.erase(find(inv.begin(), inv.end(), i));
}

void Player::moveTo(int _x, int _y) {
  shared_ptr<Room> &room = getRoomFromMap(_x, _y);
  movePointer(room);
  curRoom = room;
  x = _x;
  y = _y;
  if (room->visited) {
    room->look();
    room->listEnemies();
  } else {
    room->visited = true;
    room->init();
  }
}

void Player::takeDamage(int dmg) {
  // hurt the player
  // max 500 def
  float _dmg = (float)dmg;
  float _def = (float)def;
  float _rdmg = _dmg - ( _def / 500 * _dmg );
  int rdmg = (float)(_rdmg + 0.5f);
  cout << "You take a hit! -" << rdmg << "HP!" << endl;
  curHealth -= rdmg;
}

int Player::use(string name) {
  unique_ptr<Item> i = findItemInv(name);

  if (i == nullptr) {
    cout << "Item not present in inventory." << endl;
    return 0;
  }

  switch (i->type) {
  case 0:
    // puzzle
    break;
  case 1:
    // consumable
    if (curHealth + i->prop > maxHealth) {
      curHealth = maxHealth;
    } else {
      curHealth += i->prop;
    }

    cout << i->dia << endl;

    if (i->prop > 0) {
      cout << "You gained +" << i->prop << " HP" << endl;
    } else {
      cout << "You lost -" << i->prop << " HP" << endl;
    }

    removeFromInv(i);

    break;
  default:
    cout << "Cannot use a " << i->name << endl;
    return 0;
    break;
  }
  return 1;
}

void Player::useOn(string param1, string param2) {
  // param1 = item
  // param2 = obj in room

  unique_ptr<Item> i = move(findItemInv(param1));

  if (i == nullptr) {
    cout << "Item not present in inventory." << endl;
    return;
  } else {
    removeFromInv(i);
  }

  shared_ptr<Obj> _o = curRoom->findObject(param2);
  if (_o == nullptr) {
    cout << "Object not peresent in the room." << endl;
    player->inv.push_back(move(i));
    return;
  }

  Obj &o = *_o;

  if (o.canBeUsed) {
    if (o.isUsed) {
      player->inv.push_back(move(i));
      cout << "Not much else to do here." << endl;
      return;
    } else {
      o.use(move(i));
    }
  } else {
    player->inv.push_back(move(i));
    cout << "Nothing to do here." << endl;
    return;
  }
}

int Player::takeItem(string name) {
  // add item to inventory

  vector<unique_ptr<Item>> &rItems = curRoom->items;
  unique_ptr<Item> i = nullptr;

  if (rItems.size() == 0) {
    cout << "Item not present in the room." << endl;
    return 0;
  }


  for (auto &item : rItems) {
    if (_toLower(item->name) == name) {
      auto it = find(rItems.begin(), rItems.end(), item);
      i = move(item);
      rItems.erase(it);
      break;
    }
  }

  if (i == nullptr) {
    cout << "Item not present in the room." << endl;
    return 0;
  }

  cout << "You took \"" << i->name << "\"." << endl;

  inv.push_back(move(i));
  return 1;
}

int Player::equipItem(string name) {
  // Check if the item that is being equiped is within the inventory

  unique_ptr<Item> i = findItemInv(name);

  if (i == nullptr) {
    cout << "Item not present in inventory." << endl;
    return 0;
  } else if (i->type == 2) {

    // weapon
    removeFromInv(i);

    if (eqp != nullptr) {
      inv.push_back(move(eqp));
    }

    cout << "You equipped \"" << i->name << "\"." << endl;

    eqp = move(i);

  } else if (i->type <= 6 && i->type >= 2) {
    // chlothing

    removeFromInv(i);

    if (clothes[i->type - 3] != nullptr) {
      inv.push_back(move(clothes[i->type - 3]));
    }

    cout << "You equipped \"" << i->name << "\"." << endl;

    clothes[i->type - 3] = move(i);

    calcDef();
  }

  else {
    cout << "This item can not be equipped." << endl;
  }
  return 1;
}

void Player::check() {
  cout << "|--------Status---------|" << endl;
  cout << "   -  Health: "
       << "\t" << curHealth << "/" << maxHealth << " HP" << endl;
  cout << "   -  Defense: "
       << "\t" << def << " DP" << endl;
  cout << "|-------Inventory-------|" << endl;
  for (auto &item : inv) {
    string stat;
    if (item->type == 0) {
      cout << "   -  " << item->name << endl;
      }
    else {
      if (item->type == 1) {
	stat = "HP";
      }
      else if (item->type == 2) {
	stat = "AP";
      }
      else if (item->type > 2 && item->type <= 6 ) {
	stat = "DP";
      } else {
	stat = "BUUGIN";
      }
      cout << "   -  " << item->name << " (" << item->prop << " " << stat << ")" << endl;
    }
  }
  cout << "|--------Clothes--------|" << endl;
  for (auto &item : clothes) {
    if (item == nullptr) {
      cout << "   -  Empty" << endl;
    } else {
      cout << "   -  " << item->name << " (" << item->prop << " DP)" << endl;
    }
  }
  cout << "|-------Equipped--------|" << endl;
  if (eqp == nullptr) {
    cout << "   -  Empty" << endl;
  } else {
    cout << "   -  " << eqp->name << " (" << eqp->prop << " AP)" << endl;
  }
  cout << "|-----------------------|" << endl;
}

int Player::inspect(string name) {
  unique_ptr<Item> i = findItemInv(name);

  if (i == nullptr) {
    shared_ptr<Obj> o = curRoom->findObject(name);
    if (o == nullptr) {
      cout << "No item or object to inspect." << endl;
      return 0;
    } else {
      o->inspect();
      return 1;
    }
  } else {
    cout << i->desc << endl;

    return 1;
  }
}

int Player::discard(string name) {
  unique_ptr<Item> i = findItemInv(name);

  if (i == nullptr) {
    cout << "Item not present in inventory." << endl;
    return 0;
  }

  if (i->type != 0) {
    removeFromInv(i);

    cout << "Discarded \"" << i->name << "\"." << endl;

    i.reset();
  } else {
    cout << "This item seems important." << endl;
    return 0;
  }
  return 1;
}

void Player::unequip(string name) {

  unique_ptr<Item> c = nullptr;

  for (auto &_c : clothes) {
    if (_c != nullptr && _toLower(_c->name) == name) {
      c = move(_c);
    }
  }

  if (c != nullptr) {
    cout << "You took off " << c->name << "." << endl;
    inv.push_back(move(c));
    calcDef();
  } else if (eqp != nullptr && _toLower(eqp->name) == name) {
    cout << "You put " << eqp->name << " back into your bag." << endl;
    inv.push_back(move(eqp));
  } else {
    cout << "No item to remove." << endl;
  }
}

void Player::attack(string name) {
  shared_ptr<Entity> entity = curRoom->findEntity(name);
  if (entity == nullptr) {
    cout << "There is no " << name << " in the room." << endl;
    return;
  }

  cout << "You attack the " << name <<" -" << eqp->prop << "HP!" << endl;
  entity->takeDamage(eqp->prop);
}

int Player::moveDir(string dir) {
  if (dir == "north" && getRoomFromMap(x, y + 1) != nullptr) {
    if (curRoom->blocks[0] == nullptr || curRoom->blocks[0]->isUsed) {
      clearScr();
      cout << "You move " << dir << "." << endl;
      cout << endl;
      moveTo(x, y + 1);
    } else {
      cout << "You can't move " << dir << "." << endl;
      cout << "Your path is blocked by a " << curRoom->blocks[0]->name << "."
           << endl;
    }
  } else if (dir == "east" && getRoomFromMap(x + 1, y) != nullptr) {
    if (curRoom->blocks[1] == nullptr || curRoom->blocks[0]->isUsed) {
      clearScr();
      cout << "You move " << dir << "." << endl;
      cout << endl;
      moveTo(x + 1, y);
    } else {
      cout << "You can't move " << dir << "." << endl;
      cout << "Your path is blocked by a " << curRoom->blocks[0]->name << "."
           << endl;
    }
  } else if (dir == "south" && getRoomFromMap(x, y - 1) != nullptr) {
    if (curRoom->blocks[2] == nullptr || curRoom->blocks[0]->isUsed) {
      clearScr();
      cout << "You move " << dir << "." << endl;
      cout << endl;
      moveTo(x, y - 1);
    } else {
      cout << "You can't move " << dir << "." << endl;
      cout << "Your path is blocked by a " << curRoom->blocks[0]->name << "."
           << endl;
    }
  } else if (dir == "west" && getRoomFromMap(x - 1, y) != nullptr) {
    if (curRoom->blocks[3] == nullptr || curRoom->blocks[0]->isUsed) {
      clearScr();
      cout << "You move " << dir << "." << endl;
      cout << endl;
      moveTo(x - 1, y);
    } else {
      cout << "You can't move " << dir << "." << endl;
      cout << "Your path is blocked by a " << curRoom->blocks[0]->name << "."
           << endl;
    }
  } else {
    cout << "Can't move in that direction" << endl;
  }
  return 0;
}

int Player::action() {
  if (curHealth <= 0) {
    cout << "You fall to the floor in pain." << endl;
    death();
    game =false;
  }
  int val = prompt();
  return val;
}

shared_ptr<Player> createPlayer() {
  vector<unique_ptr<Item>> inv;
  return make_shared<Player>(50, move(inv), array<unique_ptr<Item>, 4>{}, make_unique<BrokenSword>());
}

shared_ptr<Player> player = createPlayer();
