#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <utility>

using namespace std;

int main() {
  int num1=0, num2=0, state=0, sum=0;
  char c;
  vector<char> input;
  while (cin >> c) input.push_back(c);

  vector<pair<int, int>> mults;
  for (int i = 0; i < input.size(); ++i) {
    c = input[i];
    if (state == 0) {
      if (c == 'm') state = 1;
      else state = 0;
    } else if (state == 1) {
      if (c == 'u') state = 2;
      else state = 0;
    } else if (state == 2) {
      if (c == 'l') state = 3;
      else state = 0;
    } else if (state == 3) {
      if (c == '(') state = 4;
      else state = 0;
    } else if (state == 4) {
      if (isdigit(c)) {
        num1 = (num1 * 10 + (c-'0'));
      } else if (c == ',') {
        state = 5;
      } else {
        num1 = num2 = state = 0;
      }
    } else if (state == 5) {
      if (isdigit(c)) {
        num2 = (num2 * 10 + (c-'0'));
      } else if (c == ')') {

        // sum += (num1 * num2);
        mults.push_back(pair(i, num1*num2));

        num1 = num2 = state = 0;
      } else {
        num1 = num2 = state = 0;
      }
    }

    cout << c << "  state: " << state << "  sum: " << sum << endl;
  }

  vector<int> dos, donts;
  state = 0;
  for (int i = 0; i < input.size(); ++i) {
    c = input[i];
    if (state == 0) {
      if (c == 'd') state = 1;
      else state = 0;
    } else if (state == 1) {
      if (c == 'o') state = 2;
      else state = 0;
    } else if (state == 2) {
      if (c == '(') state = 3;
      else if (c == 'n') state = 4;
      else state = 0;
    } else if (state == 3) {
      if (c == ')') dos.push_back(i);
      else state = 0;
    } else if (state == 4) {
      if (c == '\'') state = 6;
      else state = 0;
    } else if (state == 6) {
      if (c == 't') state = 7;
      else state = 0;
    } else if (state == 7) {
      if (c == '(') state = 8;
      else state = 0;
    } else if (state == 8) {
      if (c == ')') donts.push_back(i);
      else state = 0;
    }
  }

  // for (auto p : mults) {
  //   cout << " (" << p.first << ", " << p.second << ")\n";
  // }
  // cout << "dos" << endl;
  // for (auto d : dos) {
  //   cout << d << endl;
  // }
  // cout << "donts" << endl;
  // for (auto d : donts) {
  //   cout << d << endl;
  // }

  bool allowed = true;

  int i1 = 0, i2 = 0, i3 = 0, n1, n2, n3;
  while (i1 < mults.size()) {
    n1 = mults[i1].first;
    n2 = (i2 < dos.size())? dos[i2]: 100000000;
    n3 = (i3 < donts.size())? donts[i3]: 100000000;
    int n = min(n1, min(n2, n3));
    if (n1 == n) {
      if (allowed) {
        sum += mults[i1].second;
      }
      i1++;
    } else if (n2 == n) {
      allowed = true;
      i2++;
    } else {
      allowed = false;
      i3++;
    }
  }

  cout << sum << endl;

  return 0;
}