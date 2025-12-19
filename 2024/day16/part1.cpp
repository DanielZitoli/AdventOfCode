#include "helpers.h"

struct dirDists {
  array<int, 4> dists;

  dirDists(int val) {
    dists.fill(val);
  }

  int get(int dir) { return dists[dir]; }

  bool relax(int dir, int val) {
    if (val < dists[dir]) {
      dists[dir] = val;
      return true;
    }
    return false;
  }
};

int encode(Point p, int dir, int m) {
  return 4*(m*p.x + p.y) + dir;
}

pair<Point, int> decode(int hash, int m) {
  int dir = hash % 4;
  hash /= 4;
  int j = hash % m;
  hash /= m;
  int i = hash;
  return pair(Point(i, j), dir); 
}

int main() {

  Grid<char> g;
  g.getInput();
  g.printGrid();

  Point start, end;

  for (int i = 0; i < g.m; ++i) {
    for (int j = 0; j < g.n; ++j) {
      if (g.at(i, j) == 'S') {
        start = Point(i, j);
      } else if (g.at(i, j) == 'E') {
        end = Point(i, j);
      }
    }
  }

  int MAX_DIST = 100000000;

  Grid<dirDists> dist(g.m, g.n, dirDists(MAX_DIST));
  dist.at(start).relax(1, 0); // relax start node with EAST (URDL[1]) to value 0
  dist.at(2, 2).relax(2, 2);
  dist.at(3, 2).relax(1, 3);
  dist.at(2, 3).relax(3, 4);
  dist.at(4, 4).relax(0, 7);
  map<int, int> pq;

  for (int i = 0; i < g.m; ++i) {
    for (int j = 0; j < g.n; ++j) {
      for (int dir = 0; dir < 4; ++dir) {
        pq.insert(pair<int, int>(encode(Point(i, j), dir, g.m), dist.at(i, j).get(dir)));
      }
    }
  }

  while (!pq.empty()) {
    // Get min dist node
    auto it = pq.begin();
    auto [p, dir] = decode(it->first, g.m);
    int optDist = it->second;
    pq.erase(it);

    cout << optDist << " " << p << " " << dir << endl;
  }

  cout << dist.at(end).dists << endl;
    
  return 0;
}