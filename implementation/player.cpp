#include <algorithm>
#include <array>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

#include "../headers/header.h"
#include "../headers/item.h"
#include "../headers/objects.h"
#include "../headers/player.h"
#include "../headers/rooms.h"

Player::Player(int _health, vector<Item *> _inv, array<Item *, 4> _clothes,
               Item *_eqp)
    : maxHealth(_health), curHealth(_health), inv(_inv), clothes(_clothes),
      eqp(_eqp) {
  calcDef();
};

Item *Player::findItemInv(string name) {
  for (auto item : inv) {
    if (_toLower(item->name) == name) {
      return item;
    }
  }
  return nullptr;
}

void Player::calcDef() {
  def = 0;
  for (auto c : clothes) {
    if (c != nullptr) {
      def += c->prop;
    }
  }
}

void Player::removeFromInv(Item *i) {
  inv.erase(find(inv.begin(), inv.end(), i));
}

void Player::moveTo(Room *room) {
  curRoom = room;
  room->init();
}

void Player::takeDamage(int dmg) {
  // hurt the player
  curHealth -= dmg;
}

void Player::use(string name) {
  Item *i = findItemInv(name);

  if (i == nullptr) {
    cout << "Item not present in inventory." << endl;
    prompt();
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
    break;
  }
}

void Player::takeItem(string name) {
  // add item to inventory

  vector<Item *> &rItems = curRoom->items;
  Item *i;

  if (rItems.size() == 0) {
    cout << "Item not present in the room." << endl;
    prompt();
  }

  for (auto item : rItems) {
    if (_toLower(item->name) == name) {
      i = item;
      break;
    }
  }

  if (i == nullptr) {
    cout << "Item not present in the room." << endl;
    prompt();
  }

  inv.push_back(i);
  rItems.erase(find(rItems.begin(), rItems.end(), i));

  cout << "You took \"" << i->name << "\"." << endl;
}

void Player::equipItem(string name) {
  // Check if the item that is being equiped is within the inventory

  Item *i = findItemInv(name);

  if (i == nullptr) {
    cout << "Item not present in inventory." << endl;
    prompt();
  } else if (i->type == 2) {

    // weapon
    removeFromInv(i);

    if (eqp != nullptr) {
      inv.push_back(eqp);
    }

    eqp = i;
  } else if (i->type <= 6 && i->type >= 2) {

    removeFromInv(i);

    if (clothes[i->type - 3] != nullptr) {
      inv.push_back(clothes[i->type - 3]);
    }

    clothes[i->type - 3] = i;

    calcDef();
  }

  else {
    cout << "This item can not be equipped." << endl;
    prompt();
  }

  // if it is in the inventory:
  // remove it from the inventory

  cout << "You equipped \"" << i->name << "\"." << endl;
}

void Player::check() {
  cout << "|-------Inventory-------|" << endl;
  for (auto item : inv) {
    cout << "   -  " << item->name << endl;
  }
  cout << "|--------Clothes--------|" << endl;
  for (auto item : clothes) {
    if (item == nullptr) {
      cout << "   -  Empty" << endl;
    } else {
      cout << "   -  " << item->name << endl;
    }
  }
  cout << "|-----------------------|" << endl;
  if (eqp == nullptr) {
    cout << "   -  Nothing Equipped" << endl;
  } else {
    cout << "   -  " << eqp->name << " Equipped" << endl;
  }
  cout << "|-----------------------|" << endl;
}

void Player::inspect(string name) {
  Item *i = findItemInv(name);

  if (i == nullptr) {
    cout << "Item not present in inventory." << endl;
    prompt();
  }

  cout << i->desc << endl;

  return;
}

void Player::discard(string name) {
  Item *i = findItemInv(name);

  if (i == nullptr) {
    cout << "Item not present in inventory." << endl;
    prompt();
  }

  if (i->type != 0) {
    removeFromInv(i);

    cout << "Discarded " << name << "." << endl;
  } else {
    cout << "This item seems important." << endl;
  }
}

void Player::unequip(string name) {

  Item **c = nullptr;

  for (auto &_c : clothes) {
    if (_c != nullptr && _toLower(_c->name) == name) {
      c = &_c;
    }
  }

  if (c != nullptr) {
    inv.push_back(*c);
    cout << "You took off " << (*c)->name << "." << endl;
    *c = nullptr;
  } else if (eqp != nullptr && _toLower(eqp->name) == name) {
    cout << "Chungus" << endl;
    inv.push_back(eqp);
    cout << "You put " << eqp->name << " back into your bag." << endl;
    eqp = nullptr;
  } else {
    cout << "No item to remove." << endl;
  }
}

Player player(50, {}, {}, new Item(0));
