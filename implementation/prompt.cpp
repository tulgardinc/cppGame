#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <vector>

#include "../headers/header.h"
#include "../headers/item.h"
#include "../headers/objects.h"
#include "../headers/player.h"

using namespace std;

shared_ptr<Obj> findObj(string name) {
  for (auto &obj : player->curRoom->objects) {
    if (obj->name == name) {
      return obj;
    }
  }
  cout << "No chest in the room to open." << endl;
  return nullptr;
}

int prompt() {
  int retVal = 1;
  string ans;
  cout << endl;
  cout << "-----------------" << endl;
  cout << "What will you do?" << endl;
  cout << "(" << player->curHealth << "/" << player->maxHealth << " HP)"
       << " : ";
  getline(cin, ans);
  ans = _toLower(ans);
  cout << endl;

  if (ans == "") {
    cout << "Invalid command, please type \"actions\" in order to view a list "
            "of possible actions."
         << endl;
    return 0;
  }

  string cmd = ans.substr(0, ans.find(' '));
  string param = ans.substr(ans.find(' ') + 1, ans.length());

  // Switch can not be used on strings so if else is the only way

  if (cmd == "actions") {
    cout << "actions - Displays all possible actions." << endl;
    cout << "look - Looks around the current area." << endl;
    cout << "check - Makes player check their status." << endl;
    cout << "use <item> - Uses an item from the inventory." << endl;
    cout << "open <obj> - Opens objects like chests, boxes, or doors." << endl;
    cout << "inspect <item> - Inspects the item." << endl;
    cout << "take <item> - Takes item and adds to inventory." << endl;
    cout << "equip <item> - Equip item form inventory." << endl;
    cout << "unequip <item> - Unequip item form inventory." << endl;
    cout << "wait - Waits a turn." << endl;
    cout << "quit - Leaves the game." << endl;
    cout << "discard <item> - Discard an item from your inventory (forever)."
         << endl;
    return 0;
  } else if (cmd == "check") {
    clearScr();
    player->check();
    return 0;

  } else if (cmd == "inspect") {
    if (param != "") {

      retVal = player->inspect(param);
      return 0;

    } else {
      cout << "What will you inspect?" << endl;
      cout << "Usage: inspect <item>" << endl;
      return 0;
    }

  } else if (cmd == "look") {
    clearScr();
    cout << "You look around." << endl;
    cout << endl;
    player->curRoom->look();
    player->curRoom->listEnemies();
    return 0;
  } else if (cmd == "move") {
    if (param != "") {
      retVal = player->moveDir(param);
    } else {
      cout << "Move where?" << endl;
      cout << "Usage: move <direction>" << endl;
    }
  } else if (cmd == "use") {

    if (ans.find(" on ") != string::npos) {

      auto cmd1 = ans.find("use");
      auto cmd2 = ans.find("on");
      string param1 = ans.substr(cmd1 + 4, cmd2 - 5);
      string param2 = ans.substr(cmd2 + 3, ans.size());
      player->useOn(param1, param2);

    } else if (param != "") {
      retVal = player->use(param);

    } else {
      cout << "What will you use?" << endl;
      cout << "Usage: use <item>" << endl;
      return 0;
    }
  } else if (cmd == "open") {
    if (param == "chest") {
      shared_ptr<Obj> o = findObj("chest");

      {
        Obj *base = o.get();
        Chest *_c = static_cast<Chest *>(base);
        _c->open();
      }
    }
  } else if (cmd == "take") {
    if (param != "") {

      retVal = player->takeItem(param);

    } else {
      cout << "What will you take?" << endl;
      cout << "usage: take <item>" << endl;
      return 0;
    }
  } else if (cmd == "equip") {
    if (param != "") {

      retVal = player->equipItem(param);
      return 0;

    } else {

      cout << "What will you equip?" << endl;
      cout << "usage: equip <item>" << endl;
      return 0;
    }
  } else if (cmd == "discard") {
    if (param != "") {
      retVal = player->discard(param);
      return 0;
    } else {
      cout << "What will you discard?" << endl;
      cout << "Usage: discard <item>" << endl;
      return 0;
    }
  } else if (cmd == "unequip") {
    if (param != "") {
      player->unequip(param);
      return 0;
    }
    {
      cout << "What will you unequip?" << endl;
      cout << "Usage: unequip <item>" << endl;
      return 0;
    }
  } else if (cmd == "attack") {
    if (param != "") {
      player->attack(param);
    } else {
      cout << "Attack what?" << endl;
      cout << "Usage: attack <entitiy>" << endl;
      return 0;
    }
  } else if (cmd == "wait") {
    cout << "You choose to wait" << endl;
    return 0;
  } else if (cmd == "quit") {
    cout << "Bye :(" << endl;
    game = false;
  } else {
    cout << "Invalid command, please type \"actions\" in order to view a list "
            "of possible actions."
         << endl;
    return 0;
  }
  return retVal;
}
