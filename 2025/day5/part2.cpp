#include "helpers.h"

int main() {

  string line;
  long total = 0;
  vector<pair<long, long>> fresh;

  while(getline(cin, line)) {
    if (line.empty()) break;

    auto nums = splitString(line, '-');

    // cout << nums[0] << "   ---   " << nums[1] << endl;

    fresh.push_back(pair(stol(nums[0]), stol(nums[1])));
  }

  sort(fresh.begin(), fresh.end(), [](auto p1, auto p2) {return p1.first < p2.first; });

  // cout << fresh;

  long maxId = 0;
  for (auto r : fresh) {
    long start = r.first, finish = r.second;
    if (maxId < start) {
      total += (finish - start + 1);
    } else if (start <= maxId && maxId <= finish) {
      total += (finish - maxId);
    }
    maxId = max(maxId, finish);
  }



  cout << total << endl;

  return 0;
}