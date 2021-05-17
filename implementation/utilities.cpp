#include <algorithm>
#include <array>
#include <iostream>
#include <stdlib.h>
#include <vector>

#include "../headers/header.h"

using namespace std;

void clearScr() {
  cout << "\033[2J\033[1;1H";
}

string _toLower(string str) {
  for (char &c : str) {
    c = tolower(c);
  }
  return str;
}
