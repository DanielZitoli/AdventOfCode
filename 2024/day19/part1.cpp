#include "helpers.h"


bool solve(const string& pattern, int start, int end, const unordered_set<string>& towels, vector<int>& dp) {
  if (start == end) return true;
  if (dp[start]) return dp[start] > 0;
  for (int i = 1; i <= min(10, end-start); ++i) {
    // cout << pattern.substr(start, i) << " - " << (towels.count(pattern.substr(start, i)) > 0) << endl;
    if (towels.count(pattern.substr(start, i)) > 0 && solve(pattern, start+i, end, towels, dp)) {
      dp[start] = 1;
      return true;
    }
  }
  dp[start] = -1;
  return false;
}

int main() {
  unordered_set<string> towels;
  string line;

  getline(cin, line);
  istringstream stream(line);
  while (getline(stream, line, ',')) {
    towels.insert((line[0] == ' ')? line.substr(1): line);
  }
  getline(cin, line);

  for (auto t : towels) {
    cout << t << " ";
  } cout << endl;


  int sum = 0;
  while (getline(cin, line)) {
    cout << line << endl;
    vector<int> dp(line.size(), 0);
    for (int i = line.size(); i >= 0; --i) {
      solve(line, i, line.size(), towels, dp);
    }
    cout << dp << endl;
    if (dp[0] > 0) sum++;
  }

  cout << sum << endl;

  return 0;
}