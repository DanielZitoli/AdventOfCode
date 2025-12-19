#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int a, b;
  vector<int> n, m;
  while (std::cin >> a >> b) {
    n.push_back(a);
    m.push_back(b);
  }
  sort(n.begin(), n.end());
  sort(m.begin(), m.end());

  int sum = 0;
  for (int i = 0; i < n.size(); ++i) {
    sum += abs(n[i] - m[i]);
  }
  cout << sum << endl;
  return 0;
}