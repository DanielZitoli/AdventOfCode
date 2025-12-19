#include "helpers.h"


long long solve(const string& pattern, int start, int end, const unordered_set<string>& towels, vector<long long>& dp) {
  if (start == end) {
    // dp[start] = 1;
    return 1;
  }
  // if (dp[start]) {
  //   if (dp[start] > 0) return dp[start];
  //   else return 0;
  // }
  long long count = 0;
  for (int i = 1; i <= min(10, end-start); ++i) {
    // cout << pattern.substr(start, i) << " - " << (towels.count(pattern.substr(start, i)) > 0) << endl;
    if (towels.count(pattern.substr(start, i)) > 0 && dp[start+i] > 0){ //(solve(pattern, start+i, end, towels, dp) > 0)) {
      count += dp[start+i];
    }
  }
  return count;
  // if (count > 0) {
  //   dp[start] = count;
  //   return count;
  // } else {
  //   dp[start] = 0;
  //   return 0;
  // }
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


  long long sum = 0;
  while (getline(cin, line)) {
    cout << line << endl;
    vector<long long> dp(line.size()+1, 0);
    cout << "HERE";
    for (int i = line.size(); i >= 0; --i) {
      cout << i << " ";
      dp[i] = solve(line, i, line.size(), towels, dp);
    }
    cout << endl;
    cout << dp << endl;
    if (dp[0] > 0) sum += dp[0];
  }

  cout << sum << endl;

  return 0;
}