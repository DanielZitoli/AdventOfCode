#include "helpers.h"

long long solve(long long Ax, long long Ay, long long Bx, long long By, long long x, long long y) {
  if (x % get<0>(extendedEuclid(Ax, Bx)) != 0 || y % get<0>(extendedEuclid(Ay, By)) != 0) return 0;


  long long d, a, b;
  tie(d, a, b) = extendedEuclid(Ax, Bx);
  bool validX = x % d == 0;
  cout << "(" << d << " " << a << " " << b <<  ")" << endl;
  tie(d, a, b) = extendedEuclid(Ay, By);
  bool validY = y % d == 0;
  cout << (validX && validY) << endl;
  return 0;
} 


int main() {
  long long sum = 0, extra = 10000000000000;

  while (true) {
    string line, buffer(100, '\0');
    long long Ax, Ay, Bx, By, x, y;
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

    cout << vector<long long>{Ax, Ay, Bx, By, x, y};
    sum += solve(Ax, Ay, Bx, By, x+extra, y+extra);
  }

  cout << sum << endl;
  
  return 0;
}