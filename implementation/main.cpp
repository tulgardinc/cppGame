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
#include "../headers/player.h"
#include "../headers/rooms.h"

array<array<shared_ptr<Room>, 5>, 5> gameMap{{
    {nullptr, nullptr, make_shared<HiddenL>(), nullptr, nullptr},
    {nullptr, nullptr, make_shared<TestuL>(), nullptr, nullptr},
    {nullptr, make_shared<TestlL>(), make_shared<TestL>(),
     make_shared<TestrL>(), nullptr},
    {nullptr, nullptr, make_shared<TestdL>(), nullptr, nullptr},
    {nullptr, nullptr, nullptr, nullptr, nullptr},
}};

bool game = true;

void initGame(int _x, int _y) {
  // Give each room their corresponding coordinates

  for (unsigned int i = 0; i < gameMap.size(); i++) {
    for (unsigned int j = 0; j < gameMap[i].size(); j++) {
      if (gameMap[i][j] != nullptr) {
        gameMap[i][j]->x = j;
        gameMap[i][j]->y = i;
      }
    }
  }

  // Put player in its starting room
  shared_ptr<Room> room = getRoomFromMap(_x, _y);
  player->curRoom = room;
  player->curRoom->entities.push_back(player);
  player->x = _x;
  player->y = _y;
  room->init();
}

int main() {
  clearScr();

  initGame(2, 2);

  // Start the game
  while (game) {
    for (auto &entity : player->curRoom->entities) {
      entity->action();
    }
  }

  return 0;
}
