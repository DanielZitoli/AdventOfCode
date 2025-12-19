#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <tuple>
#include <algorithm>
#include <sstream>
#include <ostream>
#include <istream>
#include <array>
#include <cmath>


using namespace std;


struct Point {
  int x, y;

  Point(): x(0), y(0) {}
  Point(int a, int b): x(a), y(b) {}

  Point operator-() const { return Point(-x, -y); }

  Point& operator+=(const Point& p) {
    x += p.x;
    y += p.y;
    return *this;
  }

  Point& operator-=(const Point& p) {
    x -= p.x;
    y -= p.y;
    return *this;
  }

  Point& operator*=(double t) {
    x *= t;
    y *= t;
    return *this;
  }

  Point& operator/=(double t) {
    return *this *= 1/t;
  }

  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
  bool operator!=(const Point& other) const {
    return !(*this == other);
  }
};

// Point Utilities
inline ostream& operator<<(ostream& out, const Point& p) {
  return out << "(" << p.x << ", " << p.y << ")";
}

inline Point operator+(const Point& p1, const Point& p2) {
  return Point(p1.x + p2.x, p1.y + p2.y);
}

inline Point operator-(const Point& p1, const Point& p2) {
  return Point(p1.x - p2.x, p1.y - p2.y);
}

inline Point operator*(double t, const Point& p) {
  return Point(t*p.x, t*p.y);
}

inline Point operator*(const Point& p, double t) {
  return t * p;
}

inline Point operator/(const Point& p, double t) {
  return (1/t) * p;
}

template <typename T>
struct Grid {
  Grid() {}
  Grid(int m, int n, T val): m{m}, n{n}, grid(m, vector<T>(n, val)) {}
  Grid(int m, int n): m{m}, n{n}, grid(m, vector<T>(n, T())) {}

  vector<vector<T>> grid;
  int m, n;

  void getInput() {
    string line;

    // Read lines until the end of input
    while (getline(cin, line)) {
      istringstream stream(line);
      T data;
      vector<T> row;
      while (stream >> data) {
        row.push_back(data);
      }
      grid.push_back(row);
    }

    m = grid.size();
    n = grid[0].size();
  }

  void printGrid() {
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        cout << grid[i][j];
      }
      cout << endl;
    }
  }

  bool inBounds(int i, int j) {
    return (i >= 0) && (i < m) && (j >= 0) && (j < n);
  }

  bool inBounds(Point p) {
    return inBounds(p.x, p.y);
  }

  T& at(int i, int j) { 
    return grid[i][j]; 
  }

  T& at(Point p) {
    return at(p.x, p.y);
  }

  bool equalAt(int i, int j, T val) {
    return inBounds(i, j) && at(i, j) == val;
  }

  bool equalAt(Point p, T val) {
    return equalAt(p.x, p.y, val);
  }

};


template <typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& vec) {
  for (auto& n : vec) os << n << " ";
  os << endl;
  return os;
}

template <typename T, typename S>
std::ostream& operator<<(std::ostream& os, const pair<T, S>& p) {
    os << "(" << p.first << ", " << p.seond << ")";
    return os;
}
