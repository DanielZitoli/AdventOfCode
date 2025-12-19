#include "helpers.h"

int getCombo(int operand, int a, int b, int c) {
  if (operand < 4) return operand;
  if (operand == 4) return a;
  if (operand == 5) return b;
  if (operand == 6) return c;
  return -100;
}

int main() {

  int a, b, c, num;
  string line1, line2, line3;
  getline(cin, line1), getline(cin, line2), getline(cin, line3);
  istringstream stream1(line1.substr(11)), stream2(line2.substr(11)), stream3(line3.substr(11));
  stream1 >> a; stream2 >> b; stream3 >> c;
  getline(cin, line1); getline(cin, line1);
  vector<int> nums = extractIntegers(line1);

  cout << a << " " << b << " " << c << endl << nums << endl;

  int i = 0;
  int k = 0;
  while (i < nums.size()) {
    ++k;
    int opcode = nums[i], operand = nums[i+1];

    if (opcode == 0) {
      a = a / (1 << getCombo(operand, a, b, c));
    }
    if (opcode == 1) {
      b ^= operand;
    }
    if (opcode == 2) {
      b = getCombo(operand, a, b, c) % 8;
    }
    if (opcode == 3) {
      if (a!=0) i = operand-2;
    }
    if (opcode == 4) {
      b = b ^ c;
    }
    if (opcode == 5) {
      cout << (getCombo(operand, a, b, c)%8) << ",";
    }
    if (opcode == 6) {
      b = a / (1 << getCombo(operand, a, b, c));
    }
    if (opcode == 7) {
      c = a / (1 << getCombo(operand, a, b, c));
    }
    i+=2;
  }
  
  cout << endl << k << endl;

  return 0;
}