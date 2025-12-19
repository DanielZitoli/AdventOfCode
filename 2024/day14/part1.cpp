#include "helpers.h"

int main() {

  string line;
  int m, n, a, b;

  getline(cin, line);
  istringstream stream(line);
  stream >> m >> n;

  vector<int> quadrants(4, 0);
  char c;
  while (getline(cin, line)) {
    vector<int> nums = extractIntegers(line);

    // Actual solution
    Point p(nums[0], nums[1]), v(nums[2], nums[3]);
    Point final = p + 100*v;
    int x = ((final.x%m)+m)%m, y = ((final.y%n)+n)%n;
    bool up = x < m/2, down = x > m/2, left = y < n/2, right = y > n/2;
    if (up && left) ++quadrants[0];
    if (up && right) ++quadrants[1];
    if (down && left) ++quadrants[2];
    if (down && right) ++quadrants[3];
  }

  cout << quadrants << endl;
  cout << quadrants[0]*quadrants[1]*quadrants[2]*quadrants[3] << endl;

  return 0;
}