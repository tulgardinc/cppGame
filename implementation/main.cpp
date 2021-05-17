#include <algorithm>
#include <array>
#include <iostream>
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

  // Initialize Rooms
  TestL testl;

  // Move player
  player.moveTo(&testl);

  return 0;
}
