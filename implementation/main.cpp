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

array<array<shared_ptr<Room>, 5>, 5> gameMap{{
      {nullptr, nullptr, nullptr, nullptr, nullptr},
      {nullptr, nullptr, make_shared<TestuL>(), nullptr, nullptr},
      {nullptr, make_shared<TestlL>(), make_shared<TestL>(), make_shared<TestrL>(), nullptr},
      {nullptr, nullptr, make_shared<TestdL>(), nullptr, nullptr},
      {nullptr, nullptr, nullptr, nullptr, nullptr},
  }}; 

int main() {
 clearScr();

 player.moveTo(2,2);

 // Start the game
 prompt();

  return 0;
}
