#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

template <typename T>
struct Grid {
  vector<vector<T>> grid;
  int m, n;

  void getInput() {
    string line;

    // Read lines until the end of input
    while (getline(cin, line)) {
      vector<T> row;
      istringstream stream(line);
      T data;
      while (stream >> data) {
        row.push_back(data);
      }
      grid.push_back(row);
    }

    m = grid.size();
    n = grid[0].size();
  }

  void printGrid() {
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        cout << grid[i][j];
      }
      cout << endl;
    }
  }

  bool inBounds(int i, int j) {
    return (i >= 0) && (i < m) && (j >= 0) && (j < n);
  }

  T at(int i, int j) { 
    return grid[i][j]; 
  }

  bool equalAt(int i, int j, T val) {
    return inBounds(i, j) && at(i, j) == val;
  }
};


int main() {

  Grid<char> g;
  g.getInput();
  g.printGrid();

  vector<pair<int, int>> dirs1{pair(1, 1), pair(-1, -1)};
  vector<pair<int, int>> dirs2{pair(-1, 1), pair(1, -1)};
  int count = 0;
  for (int i = 0; i < g.m; ++i) {
    for (int j = 0; j < g.n; ++j) {
      bool diag1=false, diag2=false;
      if (g.at(i, j) == 'A') {
        for (auto p : dirs1) {
          int dx = p.first, dy = p.second;
          if (g.equalAt(i-dx, j-dy, 'M') && g.equalAt(i+dx, j+dy, 'S')) {
            diag1 = true;
          }
        }
        for (auto p : dirs2) {
          int dx = p.first, dy = p.second;
          if (g.equalAt(i-dx, j-dy, 'M') && g.equalAt(i+dx, j+dy, 'S')) {
            diag2 = true;
          }
        }

        if (diag1 && diag2) count++;
      }
    } 
  }

  cout << count << endl;

  return 0;
}