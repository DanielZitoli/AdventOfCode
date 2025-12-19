#include "helpers.h"

bool loops(Grid<char>& g, Point guard, const vector<Point>& dirs) {
  int dirIndex = 0;
  int iterations = 0;
  while(g.inBounds(guard)) {
    Point nextPos = guard + dirs[dirIndex];
    if (g.equalAt(nextPos, '#')) {
      dirIndex = (dirIndex+1)%4;
    } else {
      guard = nextPos;
    }
    ++iterations;
    if (iterations > (g.m*g.n)) return true;
  }
  return false;
}

int main() {
  Grid<char> g;
  g.getInput();
  g.printGrid();

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

  // Grid<int> visited(g.m, g.n);
  // while(g.inBounds(guard)) {
  //   visited.at(guard) = 1;
  //   Point nextPos = guard + dirs[dirIndex];
  //   if (g.equalAt(nextPos, '#')) {
  //     dirIndex = (dirIndex+1)%4;
  //   } else {
  //     guard = nextPos;
  //   }

  // }

  int loopedSpots = 0;
  for (int i = 0; i < g.m; ++i) {
    for (int j = 0; j < g.n; ++j) {
      if (g.at(i, j) != '#') {
        g.at(i, j) = '#';
        if (loops(g, guard, dirs) && guard != Point(i, j)) {
          ++loopedSpots;
        }
        g.at(i, j) = '.';
      }
    } 
  }

  cout << loopedSpots << endl;

  return 0;
}
