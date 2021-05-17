#include <algorithm>
#include <array>
#include <iostream>
#include <stdlib.h>
#include <vector>

#include "../headers/header.h"
#include "../headers/player.h"
#include "../headers/item.h"
#include "../headers/objects.h"

using namespace std;

void prompt() {
  string ans;
  cout << endl;
  cout << "-----------------" << endl;
  cout << "What will you do?" << endl;
  cout << ": ";
  getline(cin, ans);
  ans = _toLower(ans);
  cout << endl;

  if (ans == "") {
    cout << "Invalid command, please type \"actions\" in order to view a list "
            "of possible actions."
         << endl;
    prompt();
  }

  string cmd = ans.substr(0, ans.find(' '));
  string param = ans.substr(ans.find(' ') + 1, ans.length());

  // Switch can not be used on strings so if else is the only way

  if (cmd == "actions") {
    cout << "actions - Displays all possible actions" << endl;
    cout << "look - Looks around the current area" << endl;
    cout << "check - Makes player check their status" << endl;
    cout << "consume <item> - Consumes the item from inventory" << endl;
    cout << "open <obj> - opens objects like chests, boxes, or doors" << endl;
    cout << "take <item> - takes item and adds to inventory" << endl;
    cout << "equip <item> - equip item form inventory" << endl;
    prompt();
  } else if (cmd == "look") {

  } else if (cmd == "look") {

  } else if (cmd == "consume") {

  } else if (cmd == "open") {
    if (param == "chest") {
      vector<Obj *> objs = player.curRoom->objects;
      Chest *c;

      for (auto obj : objs) {
        if (obj->name == "chest") {
          c = static_cast<Chest *>(obj);
          if (c->open) {
            cout << "Chest is already open." << endl;
          }
          break;
        } else {
          cout << "No chest in the room to open." << endl;
          prompt();
        }
      }

      cout << "You move over to the chest and open it." << endl;
      cout << "Inside you can see..." << endl;
      cout << endl;
      cout << "----+---+---+----" << endl;

      for (auto &item : c->content) {
        cout << item->name << endl;
      }

      // Add the chest content to the room items
      Item *i = c->content[0];

      vector<Item *> *roomItems = &player.curRoom->items;
      roomItems->insert(roomItems->end(), c->content.begin(), c->content.end());

      cout << "----+---+---+----" << endl;

      prompt();
    }
  } else if (cmd == "take") {
    if (param != "") {

      vector<Item *>& items = player.curRoom->items;
      Item *i;

      for (auto item : items) {
        if (_toLower(item->name) == param) {
          i = item;
          break;
        } else {
          cout << "Item not present in the room." << endl;
          prompt();
        }
      }


      player.takeItem(i);
      items.erase(find(items.begin(), items.end(), i));

      cout << "You took \"" << i->name << "\"." << endl;

      prompt();

    } else {
      cout << "What will you take?" << endl;
      cout << "usage: take <item>" << endl;
      prompt();
    }

  } else if (cmd == "equip") {
    if (param != "") {

      vector<Item *>& inv = player.inv;
      Item *i;

      for (auto item : inv) {
        if (_toLower(item->name) == param) {
          i = item;
          break;
        } else {
          cout << "Item not present in inventory." << endl;
          prompt();
        }
      }


      player.equipItem(i);

      cout << "You equipped \"" << i->name << "\"." << endl;

      prompt();
    } else {
      cout << "What will you equip?" << endl;
      cout << "usage: equip <item>" << endl;
      prompt();
    }

  } else {
    cout << "Invalid command, please type \"actions\" in order to view a list "
            "of possible actions."
         << endl;
    prompt();
  }
}
