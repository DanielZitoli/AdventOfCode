#include "helpers.h"


int findVoltage(string battery) {
  int maxDigit = 0, secondDigit = 0;
  for (int i = 0; i < battery.size(); ++i) {
    int cur = battery[i] - '0';
    if (i < battery.size() - 1 && cur > maxDigit) {
      maxDigit = cur;
      secondDigit = battery[i+1]-'0';
    } else {
      secondDigit = max(secondDigit, cur);
    }
  }
  
  return 10*maxDigit + secondDigit;
}

int main() {

  int total = 0;
  string line;
  while (getline(cin, line)) {
    cout << findVoltage(line) << endl;
    total += findVoltage(line);
  }

  cout << total << endl;

  return 0;
}