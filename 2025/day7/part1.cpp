#include "helpers.h"

int main() {

  Grid<char> g;
  g.getInput();
  g.printGrid();

  Grid<int> beams(g.m, g.n, 0);
  int s = 0;
  for (int j = 0; j < g.n; ++j) {
    if (g.equalAt(0, j, 'S')) s = j;
  }

  beams.at(0, s) = 1;
  
  int total = 0;

  for (int i = 0; i < g.m - 1; ++i) {
    for (int j = 0; j < g.n; ++j) {
      if (beams.at(i, j) == 1) {
        if (g.equalAt(i, j, '^')) {
          ++total;
          beams.at(i+1, j-1) = 1;
          beams.at(i+1, j+1) = 1;
        } else {
          beams.at(i+1, j) = 1;
        }
      }
    }
  }

  beams.printGrid();

  cout << total << endl;

  return 0;
}