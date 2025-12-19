#include "helpers.h"

long createId(int num, int repeats) {
  int d = 1;
  while (pow(10, d) <= num) d++;
  long final = 0;
  for (int i = 0; i < repeats; ++i) {
    final += (num * pow(10, d*i));
  }
  return final;
}

long long findInvalids(long begin, long end) {
  set<long long> ids;
  int repeats = 2;
  while (createId(1, repeats) <= end) {
    int n = 1;
    while (true) {
      long long id = createId(n++, repeats);
      if (id > end) break;
      if (id >= begin) {
        cout << id << endl;
        ids.insert(id);
      }
    }

    repeats++;
  }

  return accumulate(ids.begin(), ids.end(), (long long) 0);
}

int main() {
  string line;
  getline(cin, line);
  auto ranges = splitString(line, ',');
  
  long long total = 0;
  for (auto range : ranges) {
    auto nums = splitString(range, '-');
    cout << "Starting " << nums[0] << " to " << nums[1] << endl;
    total += findInvalids(stol(nums[0]), stol(nums[1]));
  }


  cout << total << endl;

  return 0;
}
