#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <vector>

using namespace std;

#include "../headers/header.h"
#include "../headers/item.h"
#include "../headers/objects.h"
#include "../headers/rooms.h"
#include "../headers/player.h"
#include "../headers/goblin.h"

Goblin::Goblin(int _health, vector<unique_ptr<Item>> _loot, unique_ptr<Item> _eqp, int _x, int _y)
  :  loot(move(_loot)), eqp(move(_eqp)) {
  x = _x;
  y = _y;
  maxHealth = curHealth = _health;
  curRoom = gameMap[y][x];
  name = "goblin";
  isEnemy = true;
}

void Goblin::attack() {
  cout << endl;
  cout << "The goblin attacks you!" << endl;
  player->takeDamage(eqp->prop);
}

void Goblin::takeDamage(int dmg) {
  cout << endl;
  cout << "The goblin jumps back in pain!" << endl;
  curHealth -= dmg;
}

void Goblin::action() {
  if (curHealth <= 0) {
    cout << "The head of the goblin rolls on the floor." << endl;
    death();
    return;
  }
  attack();
}
