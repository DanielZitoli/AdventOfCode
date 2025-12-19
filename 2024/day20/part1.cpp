#include "helpers.h"

void printDist(Grid<int>& g) {
  for (int i = 0; i < g.m; ++i) {
    for (int j = 0; j < g.n; ++j) {
      if (g.at(i, j) >= 0) cout << (g.at(i, j)%10);
      else cout << "#";
    }
    cout << endl;
  }
}

int main() {

  Grid<char> g;
  g.getInput();
  g.printGrid();

  Point start, end;

  for (int i = 0; i < g.m; ++i) {
    for (int j = 0; j < g.n; ++j) {
      if (g.at(i, j) == 'S') start = Point(i, j);
      if (g.at(i, j) == 'E') end = Point(i, j);
    }
  }

  Grid<int> fromStart(g.m, g.n, -1), fromEnd(g.m, g.n, -1);
  fromStart.at(start) = 0; fromEnd.at(end) = 0;
  vector<Point> cur, next;

  cur = vector<Point>{start}; 
  while (true) {
    next = vector<Point>();
    for (auto p : cur) {
      for (auto dir : URDL) {
        if (fromStart.equalAt(p+dir, -1) && !g.equalAt(p+dir, '#')) {
          fromStart.at(p+dir) = fromStart.at(p)+1;
          next.push_back(p+dir);
        }
      }
    }
    if (next.empty()) break;
    cur = next;
  }

  cur = vector<Point>{end};
  while (true) {
    next = vector<Point>();
    for (auto p : cur) {
      for (auto dir : URDL) {
        if (fromEnd.equalAt(p+dir, -1) && !g.equalAt(p+dir, '#')) {
          fromEnd.at(p+dir) = fromEnd.at(p)+1;
          next.push_back(p+dir);
        }
      }
    }
    if (next.empty()) break;
    cur = next;
  }


  // printDist(fromStart);
  // printDist(fromEnd);
  // cout << fromStart.at(end) << endl;

  vector<int> cheats;
  for (int i = 0; i < g.m; ++i) {
    for (int j = 0; j < g.n; ++j) {
      Point p(i, j);
      for (auto dir : vector<Point>{Point(-1, 0), Point(0, 1)}) {
        if (g.inBounds(p+2*dir) && g.at(p) != '#' && g.at(p+dir) == '#' && g.at(p+2*dir) != '#') {
          int saved = abs(fromStart.at(p)-fromStart.at(p+2*dir)) - 2;
          cheats.push_back(saved);
        }
      }
    }
  }

  sort(cheats.begin(), cheats.end());
  cout << cheats << endl;
  cout << cheats.size() << endl;

  int sum = 0;
  for (auto n : cheats) {
    if (n >= 100) {
      ++sum;
    }
  }

  cout << sum << endl;

  return 0;
}