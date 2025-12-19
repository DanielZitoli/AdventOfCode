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

bool canMoveVertical(Grid<char>& g, const Point& cur, const Point& dir) {
  if (g.at(cur) == '[') {
    Point right(0, 1);
    return (g.at(cur+dir) == '.' || (g.at(cur+dir) != '#' && canMoveVertical(g, cur+dir, dir))) && 
    (g.at(cur+dir+right) == '.' || (g.at(cur+dir+right) != '#' && canMoveVertical(g, cur+dir+right, dir)));
  } else {
    Point left(0, -1);
    return (g.at(cur+dir) == '.' || (g.at(cur+dir) != '#' && canMoveVertical(g, cur+dir, dir))) && 
    (g.at(cur+dir+left) == '.' || (g.at(cur+dir+left) != '#' && canMoveVertical(g, cur+dir+left, dir)));
  }
}

void makeMoveVertical(Grid<char>& g, const Point& cur, const Point& dir) {
  if (g.at(cur) == '[') {
    Point right(0, 1);
    if (g.at(cur+dir) != '.') {
      makeMoveVertical(g, cur+dir, dir);
    } 
    if (g.at(cur+dir+right) != '.') {
      if (g.at(cur+right+dir) == '[') makeMoveVertical(g, cur+dir+right, dir);
    }
    g.at(cur+dir) = '['; 
    g.at(cur+dir+right) = ']';
    g.at(cur) = '.'; 
    g.at(cur+right) = '.';
  } else {
    Point left(0, -1);
    if (g.at(cur+dir) != '.') {
      makeMoveVertical(g, cur+dir, dir);
    }
    if (g.at(cur+dir+left) != '.') {
      if (g.at(cur+dir+left) == ']') makeMoveVertical(g, cur+dir+left, dir);
    }
    g.at(cur+dir+left) = '[';
    g.at(cur+dir) = ']'; 
    g.at(cur) = '.'; 
    g.at(cur+left) = '.';
  }
}

void makeMove(Grid<char>& g, Point& cur, const Point& dir) {
  Point next = cur+dir;
  if (g.at(next) == '.') {
    g.at(next) = '@';
    g.at(cur) = '.';
    cur = next;
  } else if (g.at(next) == '[' || g.at(next) == ']') {
    bool horizontal = (find(URDL.begin(), URDL.end(), dir)-URDL.begin()) % 2 == 1;
    if (horizontal) {
      int i = 2;
      while (g.inBounds(cur + i*dir)) {
        if (g.at(cur + i*dir) == '.') {
          for (int j = i; j >= 1; --j) {
            g.at(cur + j*dir) = g.at(cur + (j-1)*dir);
          }
          g.at(cur) = '.';
          cur = next;
          break;
        } else if (g.at(cur + i*dir) == '#') {
          break;
        }
        ++i;
      }
    } else {
      if (canMoveVertical(g, cur+dir, dir)) {
        makeMoveVertical(g, cur+dir, dir);
        g.at(cur+dir) = '@';
        g.at(cur) = '.';
        cur = next;
      }
    }
  }
}

int main() {

  Grid<char> smallGrid;
  smallGrid.getInput();
  smallGrid.printGrid();

  Grid<char> g(smallGrid.m, 2*smallGrid.n);

  for (int i = 0; i < smallGrid.m; ++i) {
    for (int j = 0; j < smallGrid.n; ++j) {
      if (smallGrid.at(i, j) == '#') {
        g.at(i, 2*j) = '#';
        g.at(i, 2*j+1) = '#';
      } else if (smallGrid.at(i, j) == '.') {
        g.at(i, 2*j) = '.';
        g.at(i, 2*j+1) = '.';      
      } else if (smallGrid.at(i, j) == 'O') {
        g.at(i, 2*j) = '[';
        g.at(i, 2*j+1) = ']';      
      } else {
        g.at(i, 2*j) = '@';
        g.at(i, 2*j+1) = '.';      
      }
    }
  }

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
      if (g.at(i, j) == '[') {
        sum += (i*100 + j);
      }
    }
  }

  cout << sum << endl;

  return 0;
}