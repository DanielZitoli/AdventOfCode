#include "helpers.h"

int main() {

  vector<vector<int>> nums;
  vector<string> ops;
  string line;
  while (getline(cin, line)) {
    if (line[0] == '+' || line[0] == '*') {
      ops = splitString(line, ' ');
    } else {
      nums.push_back(extractIntegers(line));
    }
  }

  long total = 0;

  for (int i = 0; i < ops.size(); ++i) {
    long ans;
    if (ops[i] == "+") {
      ans = 0;
      for (auto &num : nums) ans += (long) num[i];
    } else {
      ans = 1;
      for (auto &num : nums) ans *= (long) num[i];
    }
    cout << ans << endl;
    total += ans;
  }

  cout << total << endl;

  return 0;
}