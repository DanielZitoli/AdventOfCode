#include "helpers.h"

Point dfs(Point p, const Grid<char>& g, Grid<int>& visited, Grid<int>& cc, vector<array<vector<Point>, 4>>& edges) {
  visited.at(p) = 1;
  Point info(1, 0);
  for (int i = 0; i < URDL.size(); ++i) {
    Point dir = URDL[i];
    if (g.equalAt(p+dir, g.at(p))) {
      if (!visited.at(p+dir)) {
        cc.at(p+dir) = cc.at(p);
        info += dfs(p+dir, g, visited, cc, edges);
      }
    } else {
      info += Point(0, 1);
      edges[cc.at(p)][i].push_back(p);
    }
  }
  return info;
}

int countSegments(const vector<int>& nums) {
  int prev = nums[0]-1, segments = 1;
  for (int i = 0; i < nums.size(); ++i) {
    if (nums[i] != prev+1) ++segments;
    prev = nums[i];
  }
  return segments;
}

int calculatePerim(array<vector<Point>, 4>& edges) {
  int walls = 0;
  for (int i = 0; i < 4; i++) {
    map<int, vector<int>> edgeMap;
    if (i % 2 == 0) {
      for (auto p : edges[i]) {
        edgeMap[p.x].push_back(p.y);
      }
    } else {
      for (auto p : edges[i]) {
        edgeMap[p.y].push_back(p.x);
      }
    }
    for (auto& [key, value] : edgeMap) { // Structured bindings (C++17+)
      cout << value;
      sort(value.begin(), value.end());
      walls += countSegments(value);
    }
  }
  return walls;
}

int main() {

  // cout << countSegments(vector<int>{1, 2, 3, 5, 6, 7, 9, 10}) << endl;
  // cout << countSegments(vector<int>{1, 2}) << endl;
  // cout << countSegments(vector<int>{1, 3}) << endl;

  Grid<char> g;
  g.getInput();
  g.printGrid();

  Grid<int> visited(g.m, g.n);
  Grid<int> cc(g.m, g.n);
  vector<array<vector<Point>, 4>> edges;

  int sum = 0, area, perim;

  int component = 0;
  for (int i = 0; i < g.m; ++i) {
    for (int j = 0; j < g.n; ++j) {
      if (!visited.at(i, j)) {
        cc.at(i, j) = component++;
        edges.push_back(array<vector<Point>, 4>());
        Point info = dfs(Point(i, j), g, visited, cc, edges);
        area = info.x;
        perim = calculatePerim(edges[component-1]);
        // cout << area << " " << perim << " " << area * perim << endl;
        sum += area * perim;
      }
    }
  }

  // cc.printGrid();

  cout << endl << edges[0];

  cout << sum << endl;

  return 0;
}