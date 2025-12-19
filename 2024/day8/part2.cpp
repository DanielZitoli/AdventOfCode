#include "helpers.h"

int main() {

  Grid<char> g;
  g.getInput();
  g.printGrid();


  array<vector<Point>, 256> antennas;
  for (int i = 0; i < g.m; ++i) {
    for (int j = 0; j < g.n; ++j) {
      if (g.at(i, j) != '.') {
        antennas[static_cast<int>(g.at(i, j))].push_back(Point(i, j));
      }
    }
  }

  Grid<int> covered(g.m, g.n);
  for (int i = 0; i < 256; ++i) {
    for (int j = 0; j < antennas[i].size(); ++j) {
      for (int k = j+1; k < antennas[i].size(); ++k) {
        Point diff = antennas[i][j] - antennas[i][k];
        Point p = antennas[i][j];
        while (g.inBounds(p)) {
          covered.at(p) = 1;
          p += diff;
        }
        p = antennas[i][k];
        while (g.inBounds(p)) {
          covered.at(p) = 1;
          p -= diff;
        }
      }
    }
  }

  int spotsCovered = 0;
  for (int i = 0; i < g.m; ++i) {
    for (int j = 0; j < g.n; ++j) {
      spotsCovered += covered.at(i, j);
    }
  }

  cout << spotsCovered << endl;




  return 0;
}