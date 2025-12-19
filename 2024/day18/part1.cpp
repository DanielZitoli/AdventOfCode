#include "helpers.h"

void printMem(Grid<int>& g) {
  for (int i = 0; i < g.m; ++i) {
    for (int j = 0; j < g.n; ++j) {
      if (g.at(i, j) > 0) cout << "O";
      else if (g.at(i, j) == 0) cout << ".";
      else cout << "#";
    }
    cout << endl;
  }
  cout << endl;
}

int main() {

  int size, steps;
  string line;
  getline(cin, line);
  istringstream stream(line);
  stream >> size >> steps;

  vector<Point> points;
  while (getline(cin, line)) {
    vector<int> nums = extractIntegers(line);
    points.push_back(Point(nums[1], nums[0]));
  }

  Grid<int> g(size, size);

  vector<Point> cur{Point(0, 0)}, next;
  g.at(0, 0) = 1;
  Point end(size-1, size-1);

  for (int i = 0; i < steps; ++i) {
    g.at(points[i]) = -1;
  }

  printMem(g);

  int round = 1;
  while (true) {
    next = vector<Point>();
    for (auto p : cur) {
      for (auto dir : URDL) {
        if (g.equalAt(p+dir, 0)) {
          if (p+dir == end) {
            cout << round << endl;
            return 0;
          }
          g.at(p+dir) = 1;
          next.push_back(p+dir);
        }
      }
    }
    printMem(g);
    if (next.empty()) break;
    cur = next;
    ++round;
  }
  

  return 0;
}