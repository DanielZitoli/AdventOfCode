#include "helpers.h"

int main() {

  Grid<char> g;
  g.getInput();
  g.printGrid();

  Grid<long> beams(g.m, g.n, 0);
  int s = 0;
  for (int j = 0; j < g.n; ++j) {
    if (g.equalAt(0, j, 'S')) s = j;
  }

  beams.at(0, s) = 1;
  
  long total = 0;

  for (int i = 0; i < g.m - 1; ++i) {
    for (int j = 0; j < g.n; ++j) {
      cout << beams.at(i, j) << endl;
      if (g.equalAt(i, j, '^')) {
        beams.at(i+1, j-1) += beams.at(i, j);
        beams.at(i+1, j+1) += beams.at(i, j);
      } else {
        beams.at(i+1, j) += beams.at(i, j);
      }
    }
  }

  for (int j = 0; j < g.n; ++j) {
    total += beams.at(g.m-1, j);
  }


  cout << total << endl;

  return 0;
}