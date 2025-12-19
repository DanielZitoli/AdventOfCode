#include "helpers.h"


int solve(int Ax, int Ay, int Bx, int By, int x, int y) {
  int A = (x / Ax)+1, B = 0, minCost = 10000;
  while (A >= 0) {
    if ((A*Ax + B*Bx) == x && (A*Ay + B*By) == y) minCost = min(minCost, 3*A + B);
    --A;
    while (A*Ax + B*Bx < x) ++B;
  }
  if (minCost == 10000) return 0;
  else return minCost;
} 


int main() {
  int sum = 0;
  while (true) {
    string line, buffer(100, '\0');
    int Ax, Ay, Bx, By, x, y;
    if (!getline(cin, line)) break;
    istringstream stream(line);
    stream.read(&buffer[0], 12);
    stream >> Ax;
    stream.read(&buffer[0], 4);
    stream >> Ay;
    getline(cin, line);
    stream = istringstream(line);
    stream.read(&buffer[0], 12);
    stream >> Bx;
    stream.read(&buffer[0], 4);
    stream >> By;
    getline(cin, line);
    stream = istringstream(line);
    stream.read(&buffer[0], 9);
    stream >> x;
    stream.read(&buffer[0], 4);
    stream >> y;
    getline(cin, line);

    // cout << vector<int>{Ax, Ay, Bx, By, x, y};
    cout << solve(Ax, Ay, Bx, By, x, y) << endl;
    sum += solve(Ax, Ay, Bx, By, x, y);
  }

  cout << sum << endl;
  
  return 0;
}