#include "helpers.h"

void printMem(Grid<int>& g, int pointIndex) {
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

  int size;
  string line;
  getline(cin, line);
  istringstream stream(line);
  stream >> size;

  vector<Point> points;
  while (getline(cin, line)) {
    vector<int> nums = extractIntegers(line);
    points.push_back(Point(nums[1], nums[0]));
  }

  Grid<int> g(size, size);

  vector<Point> cur{Point(0, 0)}, next;

  Point end(size-1, size-1);

  // for (int i = 0; i < ; ++i) {
  //   g.at(points[i]) = -1;
  // }


  for (int pointIndex = 0; pointIndex < points.size(); ++pointIndex) {
    bool canReach = false;
    g.at(0, 0) = pointIndex+1;
    g.at(points[pointIndex]) = -1;
    vector<Point> cur{Point(0, 0)};

    int round = 1;
    while (true) {
      next = vector<Point>();
      for (auto p : cur) {
        for (auto dir : URDL) {
          if (g.inBounds(p+dir) && g.at(p+dir) >= 0 && g.at(p+dir) < pointIndex+1) {
            if (p+dir == end) {
              // cout << round << endl;
              canReach = true;
            }
            g.at(p+dir) = pointIndex+1;
            next.push_back(p+dir);
          }
        }
      }

      // printMem(g, pointIndex);
      if (next.empty()) break;
      cur = next;
      ++round;
    }

    if (!canReach) {
      cout << points[pointIndex] << endl;
      break;
    }
  }
  

  return 0;
}