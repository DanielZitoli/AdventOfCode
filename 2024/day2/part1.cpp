#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

bool isIncreasing(const vector<int> &a, int dir) {
  for (int i = 0; i < a.size()-1; i++) {
    if ((a[i+1]-a[i])*dir <= 0) return false;
  }
  return true;
}

bool isSlow(const vector<int> &a) {
  for (int i = 0; i < a.size()-1; i++) {
    if (abs(a[i+1]-a[i]) > 3) return false;
  }
  return true;
}

int main() {
  string line;
  
  int goodRows = 0;

  // Read lines until the end of input
  while (getline(cin, line)) {
    istringstream stream(line);
    vector<int> row;
    int data;
    while (stream >> data) {
      row.push_back(data);
    }
    // for (auto n : row) cout << n << " ";
    // cout << endl;
    for (int i = 0; i < row.size(); ++i) {
      vector<int> newRow = row;
      newRow.erase(newRow.begin()+i);
      if ((isIncreasing(newRow, 1) || isIncreasing(newRow, -1)) && isSlow(newRow)) {
        goodRows++;
        break;
      }
    }
  }

  cout << goodRows << endl;

  return 0;
}