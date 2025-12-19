#include "helpers.h"

int main() {

  int d, pos = 50, count = 0; string s;
  while (cin >> s) {
    d = stoi(s.substr(1));
    count += (d / 100);
    d %= 100;
    if (s[0] == 'L') {
      if (pos > 0 && pos - d <= 0) {
        count++;
      }
      pos = (pos-d+100)%100;
    } else {
      if (pos > 0 && pos + d > 99) {
        count++;
      }
      pos = (pos+d)%100;
    }
  }

  cout << count << endl;

  return 0;
}