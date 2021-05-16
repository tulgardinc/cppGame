#include <algorithm>
#include <array>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

#include "header.h"
#include "item.h"
#include "objects.h"
#include "rooms.h"
#include "player.h"

Player player(50, {}, {});

int main() {

  // Initialize player

  // Initialize Rooms
  TestL testl;

  // Move player
  player.moveTo(&testl);

  return 0;
}
