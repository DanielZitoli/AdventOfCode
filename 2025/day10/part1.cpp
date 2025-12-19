#include "helpers.h"


int findIndicator(string s) {
  int indicator = 0;
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == '#') indicator += (1 << i);
  }
  return indicator;
}

int findButton(string s) {
  auto nums = extractIntegers(s);
  int button = 0;
  for (auto num : nums) button += (1 << num);
  return button;
}

int minPresses(int indicator, vector<int> &buttons) {
  int minimum = 1000, numButtons = buttons.size();

  for (int mask = 0; mask < (1 << numButtons); ++mask) {
    int result = 0, current = 0;
    for (int i = 0; i < numButtons; ++i) {
      if (mask & (1 << i)) {
        ++current;
        result ^= buttons[i];
      }
    }

    if (result == indicator) {
      minimum = min(minimum, current);
    }
    
  }

  return minimum;

  // set<int> states;
  // states.insert(0);
  // for (int i = 0; i < 10; ++i) {
  //   set<int> newStates;
  //   for (auto state : states) {
  //     for (auto button : buttons) {
  //       newStates.insert(state^button);
  //     }
  //   }
  //   if (newStates.count(indicator) > 0) return i+1;
  //   states = newStates;
  // }
  // return -1;
}

int main() {
  string line;
  int total = 0;
  while (getline(cin, line)) {
    auto inputs = splitString(line, ' ');
    int k = inputs.size();
    vector<int> buttons;

    int numDials = inputs[0].size()-2;
    int indicator = findIndicator(inputs[0].substr(1, numDials));
    for (int i = 1; i < k-1; ++i) {
      buttons.push_back(findButton(inputs[i]));
    }
    auto voltages = extractIntegers(inputs[k-1]);

    // cout << minPresses(indicator, buttons) << endl;
    total += minPresses(indicator, buttons);
  }

  cout << total << endl;

  return 0;
}