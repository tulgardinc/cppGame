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


int main() {
 clearScr();

  // Move player => initiates the game
  player.moveTo(make_shared<TestL>());

  return 0;
}
