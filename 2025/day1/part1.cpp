#include "helpers.h"

int main() {

  int d, pos = 50, count = 0; string s;
  while (cin >> s) {
    d = stoi(s.substr(1));
    if (s[0] == 'L') {
      pos = (pos - d) % 100;
    } else {
      pos = (pos + d) % 100;
    }
    if (pos == 0) count++;
  }

  cout << count << endl;

  return 0;
}