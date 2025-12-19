#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
  int a, b;
  vector<int> n, m;
  while (std::cin >> a >> b) {
    n.push_back(a);
    m.push_back(b);
  }

  map<int, int> rightFreq;
  for (auto r : m) {
    rightFreq[r]++;
  }

  int sum = 0;
  for (auto l : n) {
    if (rightFreq.count(l) > 0) {
      sum += l * rightFreq[l];
    }
  }

  cout << sum << endl;
  return 0;
}