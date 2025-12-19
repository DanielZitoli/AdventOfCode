#include "helpers.h"

void printStep(string trace, long long l, long long r, long long space, vector<long long>& fileBlocks, vector<long long>& spaceBlocks) {
  cout << trace;
  // while (l <= r) {
  //   for (int i = 0; i < fileBlocks[l]; ++i) {
  //     cout << l;
  //   }
  //   for (int i = 0; i < spaceBlocks[space]; ++i) {
  //     cout << '.';
  //   }
  //   ++l; ++space;
  // }
  cout << endl;
}

int main() {

  string line;
  getline(cin, line);

  // cout << line << endl << line.size() << endl;

  vector<long long> fileBlocks, spaceBlocks;
  for (int i = 0; i < line.size(); ++i) {
    if (i%2 == 0) {
      fileBlocks.push_back(line[i]-'0');
    } else {
      spaceBlocks.push_back(line[i]-'0');
    }
  }
  // spaceBlocks.push_back(10000000); // in case space runs out

  long long sum = 0, index = 0, l = 0, r = fileBlocks.size()-1, space = 0;

  string trace = "";

  while (l < r) {
    if (fileBlocks[l]) {
      // cout << l;
      trace += to_string(l);
      sum += index++ * l;
      --fileBlocks[l];
    } else if (spaceBlocks[space]) {
      // cout << r;
      trace += to_string(r);
      sum += index++ * r;
      --spaceBlocks[space];
      --fileBlocks[r];
      if (fileBlocks[r] == 0) --r;
    } else {
      ++l; ++space;
    }
    // printStep(trace, l, r, space, fileBlocks, spaceBlocks);
  }
  while (fileBlocks[r]--) {
    // cout << r;
    trace += to_string(r);
    sum += index++ * r;
    // printStep(trace, l, r, space, fileBlocks, spaceBlocks);
  }
  cout << endl << index;
  cout << endl << space;

  cout << endl << sum << endl;


  return 0;
}