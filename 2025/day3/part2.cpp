#include "helpers.h"


long long findVoltage(string battery) {
  long long voltage = 0;
  int prevMax = -1;
  int n = battery.size();
  for (int digit = 0; digit < 12; ++digit) {
    int maxDigit = 0;
    for (int i = prevMax+1; i < n - 12 + digit+1; ++i) {
      int cur = battery[i] - '0';
      if (cur > maxDigit) {
        maxDigit = cur;
        prevMax = i;
      }
    }
    voltage *= 10;
    voltage += maxDigit;
  }
  return voltage;
}

int main() {

  long long total = 0;
  string line;
  while (getline(cin, line)) {
    cout << findVoltage(line) << endl;
    total += findVoltage(line);
  }

  cout << total << endl;

  return 0;
}