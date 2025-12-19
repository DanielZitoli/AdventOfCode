#include "helpers.h"

Point getDir(char c) {
  if (c == '^') {
    return Point(-1, 0);
  } else if (c == '>') {
    return Point(0, 1);
  } else if (c == 'v') {
    return Point(1, 0);
  } else if (c == '<') {
    return Point(0, -1);
  } else {
    cout << "ERROR!" << endl;
    return Point();
  }
}

void makeMove(Grid<char>& g, Point& cur, const Point& dir) {
  Point next = cur+dir;
  if (g.at(next) == '.') {
    g.at(next) = '@';
    g.at(cur) = '.';
    cur = next;
  } else if (g.at(next) == 'O') {
    int i = 2;
    while (g.inBounds(cur + i*dir)) {
      if (g.at(cur + i*dir) == '.') {
        g.at(cur + i*dir) = 'O';
        g.at(next) = '@';
        g.at(cur) = '.';
        cur = next;
        break;
      } else if (g.at(cur + i*dir) == '#') {
        break;
      }
      ++i;
    }
  }
}

int main() {

  Grid<char> g;
  g.getInput();
  g.printGrid();

  Point robot;
  for (int i = 0; i < g.m; ++i) {
    for (int j = 0; j < g.n; ++j) {
      if (g.at(i, j) == '@') {
        robot = Point(i, j);
      }
    }
  }

  cout << robot << endl;

  string line;
  while (getline(cin, line)) {
    for (auto c : line) {
      makeMove(g, robot, getDir(c));
      // cout << c << endl; g.printGrid();
    }
  }

  int sum = 0;
  for (int i = 0; i < g.m; ++i) {
    for (int j = 0; j < g.n; ++j) {
      if (g.at(i, j) == 'O') {
        sum += (i*100 + j);
      }
    }
  }

  cout << sum << endl;

  return 0;
}