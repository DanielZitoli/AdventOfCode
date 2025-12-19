#include "helpers.h"

Point dfs(Point p, const Grid<char>& g, Grid<int>& visited) {
  visited.at(p) = 1;
  Point info(1, 0);
  for (auto dir : URDL) {
    if (g.equalAt(p+dir, g.at(p))) {
      if (!visited.at(p+dir)) info += dfs(p+dir, g, visited);
    } else {
      info += Point(0, 1);
    }
  }
  return info;
}

int main() {

  Grid<char> g;
  g.getInput();
  g.printGrid();

  Grid<int> visited(g.m, g.n);
  int sum = 0, area, perim;

  for (int i = 0; i < g.m; ++i) {
    for (int j = 0; j < g.n; ++j) {
      if (!visited.at(i, j)) {
        Point info = dfs(Point(i, j), g, visited);
        area = info.x, perim = info.y;
        cout << area << " " << perim << " " << area * perim << endl;
        sum += area * perim;
      }
    }
  }

  cout << sum << endl;

  return 0;
}