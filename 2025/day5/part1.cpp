#include "helpers.h"

int main() {

  string line;
  long total = 0;
  vector<pair<long, long>> fresh;

  while(getline(cin, line)) {
    if (line.empty()) break;

    auto nums = splitString(line, '-');


    fresh.push_back(pair(stol(nums[0]), stol(nums[1])));
  }




  while(getline(cin, line)) {
    long id = stol(line);

    bool isFresh = false;
    for (auto r : fresh) {
      if (r.first <= id && id <= r.second) isFresh = true;
    }
    if (isFresh) ++total;
  }

  cout << total << endl;

  return 0;
}