#include "helpers.h"

int main() {

  string line;
  vector<pair<long, long>> points;

  while(getline(cin, line)) {
    auto nums = extractIntegers(line);
    points.push_back(pair(nums[0], nums[1]));
  }

  long largest = 0;
  int n = points.size();
  for (int i = 0; i < n; ++i) {
    for (int j = i+1; j < n; ++j) {
      long area = (abs(points[i].first-points[j].first)+1)*(abs(points[i].second-points[j].second)+1);
      largest = max(largest, area);
    }
  }

  cout << largest << endl;

  return 0;
}