#include "helpers.h"

int main() {

  Grid<char> g;
  g.getInput();
  // g.printGrid();

  int total = 0;
  while (true) {  
    int progress = false;

    for (int i = 0; i < g.m; ++i) {
      for (int j = 0; j < g.n; ++j) {
        Point p(i, j);
        int neighbours = 0;
        for (auto dir : eightDirs) {
          if (g.equalAt(p+dir, '@')) ++neighbours;
        }

        if (g.equalAt(p, '@') && neighbours < 4) {
          progress = true;
          g.at(p) = '.';
          ++total;
        }
      }
    }

    if (!progress) break;
  }

  cout << total << endl;

  return 0;
}