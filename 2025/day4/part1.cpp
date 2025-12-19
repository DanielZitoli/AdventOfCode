#include "helpers.h"

int main() {

  Grid<char> g;
  g.getInput();
  // g.printGrid();

  int total = 0;
  for (int i = 0; i < g.m; ++i) {
    for (int j = 0; j < g.n; ++j) {
      Point p(i, j);
      int neighbours = 0;
      for (auto dir : eightDirs) {
        if (g.equalAt(p+dir, '@')) ++neighbours;
      }

      if (g.equalAt(p, '@') && neighbours < 4) ++total;
    }
  }

  cout << total << endl;

  return 0;
}