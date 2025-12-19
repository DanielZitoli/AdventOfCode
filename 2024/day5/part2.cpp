#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>

using namespace std;


int main() {
  vector<vector<bool>> rules(100, vector<bool>(100, false));
  string line;
  char c;

  // Read lines until the end of input
  while (getline(cin, line)) {
    if (line.empty()) break;

    vector<int> row;
    istringstream stream(line);
    int page1, page2;
    stream >> page1 >> c >> page2;
    rules[page1][page2] = true;
  }

  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      if (rules[i][j]) cout << "1";
      else cout << "0";
    }
    cout << endl;
  }

  int pageSum = 0;

  while (getline(cin, line)) {
    vector<int> row;
    istringstream stream(line);
    string token;
    while (std::getline(stream, token, ',')) {
      row.push_back(std::stoi(token)); // Convert token to integer and store in vector
    }
    
    bool valid = true;
    for (int i = 0; i < row.size(); ++i) {
      for (int j = i+1; j < row.size(); ++j) {
        if (rules[row[j]][row[i]]) {
          sort(row.begin(), row.end(), [&rules] (int a, int b) { return rules[a][b]; });
          pageSum += row[row.size()/2];
        }
      }
    }

  }

  cout << pageSum << endl;

  return 0;
}