#include "helpers.h"

long createId(int num) {
  int d = 1;
  while (pow(10, d) <= num) d++;
  return num + pow(10, d)*num;
}

long long findInvalids(long begin, long end) {
  long long total = 0;
  int n = 1;
  while (true) {
    long id = createId(n++);
    cout << id << endl;
    if (id > end) break;
    if (id >= begin) total += id;
  }

  return total;
}

int main() {
  string line;
  getline(cin, line);
  auto ranges = splitString(line, ',');

  long long total = 0;
  for (auto range : ranges) {
    auto nums = splitString(range, '-');

    cout << nums[0] << " - " << nums[1] << endl;
    total += findInvalids(stol(nums[0]), stol(nums[1]));
  }

  cout << total << endl;

  return 0;
}
