#include "helpers.h"

int main() {

  Grid<char> g;
  g.getInput();
  g.printGrid();

  array<vector<Point>, 10> heights;

  Grid<int> numPaths(g.m, g.n);

  for (int i = 0; i < g.m; ++i) {
    for (int j = 0; j < g.n; ++j) {
      heights[g.at(i, j)-'0'].push_back(Point(i, j));
    }
  }

  // for (auto vec : heights) cout << vec.size() << " ";
  // cout << endl;

  for (int i = 0; i < heights[9].size(); ++i) {
    Point p = heights[9][i];
    numPaths.at(p) = 1;
  }

  numPaths.printGrid();
  cout << endl;

  for (int h = 8; h >= 0; --h) {
    for (auto p : heights[h]) {
      for (auto dir : URDL) {
        if (g.inBounds(p+dir) && ((g.at(p+dir)-'0') == h+1)) {
          numPaths.at(p) += numPaths.at(p+dir);
        }
      }
    }
    // numPaths.printGrid();
    // cout << endl;
  }



  int sum = 0;
  for (auto p : heights[0]) {
    cout << numPaths.at(p) << " ";
    sum += numPaths.at(p);
  }

  cout << endl << sum << endl;

  return 0;
}