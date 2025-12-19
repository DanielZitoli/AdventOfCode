#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <tuple>
#include <algorithm>
#include <sstream>
#include <ostream>
#include <istream>
#include <regex>
#include <numeric>



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

vector<Point> URDL{Point(-1, 0), Point(0, 1), Point(1, 0), Point(0, -1)};
vector<Point> eightDirs{Point(1, 0), Point(1, 1), Point(0, 1), Point(-1, 1), Point(-1, 0), Point(-1, -1), Point(0, -1), Point(1, -1)};


template <typename T>
struct Grid {
  Grid() {}
  Grid(int m, int n, T val): m{m}, n{n}, grid(m, vector<T>(n, val)) {}
  Grid(int m, int n): m{m}, n{n}, grid(m, vector<T>(n, T())) {}

  int m, n;
  vector<vector<T>> grid;

  void getInput() {
    string line;

    // Read lines until the end of input
    while (getline(cin, line)) {
      if (line.empty()) break;
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

  bool inBounds(int i, int j) const {
    return (i >= 0) && (i < m) && (j >= 0) && (j < n);
  }

  bool inBounds(Point p) const {
    return inBounds(p.x, p.y);
  }

  T& at(int i, int j) { 
    return grid[i][j]; 
  }

  T& at(Point p) {
    return at(p.x, p.y);
  }

  const T& at(int i, int j) const { 
    return grid[i][j]; 
  }

  const T& at(Point p) const {
    return at(p.x, p.y);
  }

  bool equalAt(int i, int j, T val) const {
    return inBounds(i, j) && at(i, j) == val;
  }

  bool equalAt(Point p, T val) const {
    return equalAt(p.x, p.y, val);
  }

};

// Number Theory
template <typename T>
T gcd(const T& a, const T& b) {
  if (zero(b)) return T(0);
  return gcd(b, a % b);
}

template <typename T>
std::tuple<T, T, T> extendedEuclid(const T& a, const T& b) {
  using triple = std::tuple<T, T, T>;
  if (zero(b)) return triple(a, 1, 0);
  T d, x, y;
  std::tie(d, x, y) = extendedEuclid(b, a % b); // prev = (d, x, y)
  return triple(d, y, x - ((a / b) * y));
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& vec) {
  for (auto& n : vec) os << n << " ";
  os << endl;
  return os;
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const array<T, N>& arr) {
  for (int i = 0; i < N; ++i) os << arr[i] << " ";
  os << endl;
  return os;
}

template <typename T, typename S>
std::ostream& operator<<(std::ostream& os, const pair<T, S>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}



// Parsing 

std::vector<int> extractIntegers(const std::string& input) {
    std::vector<int> numbers;
    std::regex numberRegex(R"(-?\d+)"); // Match integers (optional '-' followed by digits)
    std::sregex_iterator it(input.begin(), input.end(), numberRegex);
    std::sregex_iterator end;

    while (it != end) {
      numbers.push_back(std::stoi(it->str())); // Convert the match to an integer
      ++it;
    }

    return numbers;
}

vector<string> splitString(const string& s, char delimiter) {
    vector<string> result;
    string current;

    for (char c : s) {
        if (c == delimiter) {
            result.push_back(current);
            current.clear();
        } else {
            current += c;
        }
    }

    result.push_back(current); // last token
    return result;
}
