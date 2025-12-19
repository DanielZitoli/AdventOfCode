#include "helpers.h"


Point modPoint(Point p, int m, int n) {
  return Point(((p.x%m) + m)%m, ((p.y%n) + n)%n);
}

Grid<int> ithGrid(vector<Point>& pos, vector<Point>& vel, int m, int n, int i) {
  Grid<int> g(m, n, 0);
  for (int k = 0; k < pos.size(); ++k) {
    ++g.at(modPoint(pos[k]+i*vel[k], m, n));
  }
  return g;
}

int countPackedCells(Grid<int>& g) {
  int packedCells = 0;
  for (int i = 0; i < g.m; ++i) {
    for (int j = 0; j < g.n; ++j) {
      int adj = 0;
      for (int k = 0; k <= 1; ++k) {
        for (int l = 0; l <= 1; ++l) {
          if (g.inBounds(i+k, j+l)&&g.at(i+k, j+l)>0) ++adj;
        }
      }
      if (adj >= 4) ++packedCells;
    }
  }
  return packedCells;
}

void printGuards(Grid<int>& g) {
  for (int i = 0; i < g.m; ++i) {
    for (int j = 0; j < g.n; ++j) {
      if (g.at(i, j) > 0) cout << '#';
      else cout << '.';
    }
    cout << endl;
  }
}

int main() {

  string line;
  int m, n, a, b;

  getline(cin, line);
  istringstream stream(line);
  stream >> m >> n;

  vector<int> quadrants(4, 0);
  char c;
  vector<Point> pos, vel;
  while (getline(cin, line)) {
    vector<int> nums = extractIntegers(line);

    // Actual solution
    Point p(nums[0], nums[1]), v(nums[2], nums[3]);
    pos.push_back(p); vel.push_back(v);
  }

  Grid<int> g(m, n, 0);

  for (const Point& p : pos) ++g.at(p);

  int i = 1;
  while (i++ < 10000) {
    Grid<int> grid = ithGrid(pos, vel, m, n, i);
    int packed = countPackedCells(grid);
    if (packed > 10) {
      printGuards(grid);
      cout << i << " " << packed << endl;
    }
  }

  return 0;
}