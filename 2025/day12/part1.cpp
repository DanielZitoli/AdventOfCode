#include "helpers.h"

int main() {
  vector<int> blocks;

  string line;
  for (int i = 0; i < 6; ++i) {
    int count = 0;
    getline(cin, line);
    getline(cin, line);
    for (char c : line) if (c == '#') ++count;
    getline(cin, line);
    for (char c : line) if (c == '#') ++count;
    getline(cin, line);
    for (char c : line) if (c == '#') ++count;
    getline(cin, line);
    blocks.push_back(count);
  }

  cout << blocks;

  int total = 0;

  while (getline(cin, line)) {
    auto nums = extractIntegers(line);
    int x = nums[0], y = nums[1];
    int size = x*y;
    int totalBlocks = 0, totalPresents = 0;
    for (int i = 0; i < 6; ++i) {
      totalBlocks += blocks[i]*nums[i+2];
      totalPresents += nums[i+2];
    }

    // cout << pair<int, int>(x, y) << " " << size << " : " << pair<int, int>(x/3, y/3) << totalBlocks << " : " << totalPresents << endl;

    if (totalBlocks > size) {
      // cout << "Too many blocks" << endl;
    } else if ((x/3)*(y/3) >= totalPresents) {
      ++total;
      // cout << "Presents fit trivially" << endl;
    } else {
      cout << "UNDETERMINED\n";
    }
  }

  cout << total << endl;


  return 0;
}