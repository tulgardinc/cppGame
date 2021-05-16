#include <algorithm>
#include <array>
#include <iostream>
#include <stdlib.h>
#include <vector>

#include "header.h"

using namespace std;

string _toLower(string str) {
  for (char &c : str) {
    c = tolower(c);
  }
  return str;
}
