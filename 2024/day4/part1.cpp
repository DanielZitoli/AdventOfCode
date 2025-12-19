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

  vector<pair<int, int>> dirs{pair(1, 0), pair(1, 1), pair(0, 1), pair(-1, 1), pair(-1, 0), pair(-1, -1), pair(0, -1), pair(1, -1)};
  int count = 0;
  for (int i = 0; i < g.m; ++i) {
    for (int j = 0; j < g.n; ++j) {
      if (g.at(i, j) == 'X') {
        for (auto p : dirs) {
          int dx = p.first, dy = p.second;
          if (g.equalAt(i+dx, j+dy, 'M') && g.equalAt(i+2*dx, j+2*dy, 'A') && g.equalAt(i+3*dx, j+3*dy, 'S')) {
            count++;
          }
        }
      }
    } 
  }

  cout << count << endl;

  return 0;
}