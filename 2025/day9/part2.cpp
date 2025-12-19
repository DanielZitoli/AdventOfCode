#include "helpers.h"

using P = pair<long, long>;

struct Square {
  Square(P &p1, P &p2): x1(min(p1.first, p2.first)), x2(max(p1.first, p2.first)), 
                        y1(min(p1.second, p2.second)), y2(max(p1.second, p2.second)) {}

  int x1, x2, y1, y2;

  bool containsPoint(P &p) {
    return (x1 < p.first && p.first < x2 && y1 < p.second && p.second < y2);
  }

  bool containsLine(P &p1, P &p2) {
    if (p1.first == p2.first) { //vertical
      return (x1 < p1.first && p1.first < x2) && (max(p1.second, p2.second) > y1) && (min(p1.second, p2.second) < y2);
    } else { // horizontal
      return (y1 < p1.second && p1.second < y2) && (max(p1.first, p2.first) > x1) && (min(p1.first, p2.first) < x2);
    }
  }
  
};


int main() {

  string line;
  vector<P> points;

  while(getline(cin, line)) {
    auto nums = extractIntegers(line);
    points.push_back(pair(nums[0], nums[1]));
  }


  long largest = 0;
  int n = points.size();
  for (int i = 0; i < n; ++i) {
    for (int j = i+1; j < n; ++j) {
      long area = (abs(points[i].first-points[j].first)+1)*(abs(points[i].second-points[j].second)+1);
      Square s(points[i], points[j]);
      bool isValid = true;
      for (int k = 0; k < n; ++k) {
        if (s.containsPoint(points[k]) || s.containsLine(points[k], points[(k+1)%n])) {
          isValid = false;
          break;
        }
      }

      if (isValid) {
        largest = max(largest, area);
      }
    }
  }

  cout << largest << endl;
 

  return 0;
}