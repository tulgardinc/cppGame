#include <algorithm>
#include <array>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

class Item {
public:
  string desc, name;
  int type, prop, id;

  Item(int _id) {

    // 0: none
    // 1: puzzle
    // 2: consumable
    // 3: weraable
    // 4: weapon

    id = _id;

    switch (_id) {
    case 0:
      name = "Empty";
      type = 0;
      desc = "Your bare hands";
      prop = 0;
      break;
    case 1:
      name = "Broken Sword";
      type = 3;
      desc = "An old, rusty sword. Broken halfway, and covered in dried "
             "blood... Better than nothing.";
      prop = 5;
      break;
    default:
      name = "Buuugin";
      break;
    }
  };
};

class Obj {
public:
  string name;
  void setName(string n) { name = n; }
};

class Room {
public:
  string name;
  vector<Obj *> objects;
  vector<Item *> items;
  virtual void init() = 0;
  void setValues(string _n, vector<Obj *> _o, vector<Item *> _i) {
    name = _n;
    objects = _o;
    items = _i;
  }
};

class Player {
public:
  int health;
  vector<Item *> inv;
  vector<Item *> clothes;
  Room *curRoom;
  Item *eqp;

  Player(int _health, vector<Item *> _inv, vector<Item *> _clothes)
      : health(_health), inv(_inv), clothes(_clothes), eqp(0) {}

  void moveTo(Room *room) {
    curRoom = room;
    room->init();
  }

  void takeDamage(int dmg) {
    // hurt the player
    health -= dmg;
  }

  void consume(Item *item) {
    // add the effect to heatlh
    health += item->prop;
    // remove consumed item from inventory
    inv.erase(find(inv.begin(), inv.end(), item));
  }

  void takeItem(Item *item) {
    // add item to inventory
    inv.push_back(item);
  }

  void equipItem(Item *item) {
    // Check if the item that is being equiped is within the inventory
    if (find(inv.begin(), inv.end(), item) != inv.end()) {
      // if it is in the inventory:
      // remove it from the inventory
      inv.erase(find(inv.begin(), inv.end(), item));

      // check if the equiment is not empty
      if (eqp->type != 0) {
        // if it is not empty return it to the inventory
        inv.push_back(eqp);
      }

      // equip the item
      eqp = item;

    } else {
      // if the item is not in the inventory do nothing
      cout << item->name << " Is not in your inventory." << endl;
    }
  }
};

Player player(50, {}, {});

class Chest : public Obj {
public:
  vector<Item *> content;
  bool open;

  Chest(vector<Item *> _content, bool _open) {
    setName("chest");
    content = _content;
    open = _open;
  }
};

string _toLower(string str) {
  for (char &c : str) {
    c = tolower(c);
  }
  return str;
}

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

      vector<Item *> items = player.curRoom->items;
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

      player.inv.push_back(i);
      items.erase(find(items.begin(), items.end(), i));

      cout << "You took \"" << i->name << "\"." << endl;

      prompt();

    } else {
      cout << "What will you take?" << endl;
      cout << "usage: take <item>" << endl;
      prompt();
    }

  } else if (cmd == "equip") {

  } else {
    cout << "Invalid command, please type \"actions\" in order to view a list "
            "of possible actions."
         << endl;
    prompt();
  }
}

class TestL : public Room {
public:
  TestL() {
    // Setup the contents
    Item *sword = new Item(1);
    Chest *chest = new Chest({sword}, false);
    vector<Obj *> _objects{chest};
    setValues("TestL", _objects, vector<Item *>());
  }

  void init() {
    cout << "You wake up in a dark dungeon" << endl;
    cout << "You see a chest in front of you" << endl;
    prompt();
  }
};

int main() {

  // Initialize player

  // Initialize Rooms
  TestL testl;

  // Move player
  player.moveTo(&testl);

  return 0;
}
