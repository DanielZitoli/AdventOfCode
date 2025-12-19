#include "helpers.h"

int main() {
  Grid<char> g;
  g.getInput();
  g.printGrid();

  Point a(1, 2);
  Point b(5, 10);

  // cout << a+b << endl;
  // b = a;
  // cout << b << endl;
  // return 0;

  vector<Point> dirs{Point(-1, 0), Point(0, 1), Point(1, 0), Point(0, -1)};
  int dirIndex = 0;
  Point guard;

  for (int i = 0; i < g.m; ++i) {
    for (int j = 0; j < g.n; ++j) {
      if (g.at(i, j) == '^') {
        guard = Point(i, j);
        break;
      }
    } 
  }

  Grid<int> visited(g.m, g.n);
  while(g.inBounds(guard)) {
    visited.at(guard) = 1;
    Point nextPos = guard + dirs[dirIndex];
    if (g.equalAt(nextPos, '#')) {
      dirIndex = (dirIndex+1)%4;
    } else {
      guard = nextPos;
    }

  }

  int visitedSpots = 0;
  for (int i = 0; i < g.m; ++i) {
    for (int j = 0; j < g.n; ++j) {
      if (visited.at(i, j)) {
        ++visitedSpots;    
      }
    } 
  }

  cout << visitedSpots << endl;

  return 0;
}
