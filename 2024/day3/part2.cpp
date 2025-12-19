#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
struct Grid {
  vector<vector<T>> grid;
  int m, n;

  void getInput() {
    std::string line;

    // Read lines until the end of input
    while (std::getline(std::cin, line)) {
      std::istringstream stream(line);
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
};


int main() {

  Grid<char> g;
  g.getInput();

  return 0;
}