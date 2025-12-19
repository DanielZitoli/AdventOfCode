#include "helpers.h"

long long getComplexity(string code) {
  return 0;
}

int main() {

  string line;
  long long sum = 0, numeric, complexity;
  while (getline(cin, line)) {
    istringstream stream(line);
    stream >> numeric;

    complexity = getComplexity(line);
    // cout << complexity << endl;
    sum += (complexity * numeric);
  }

  cout << sum << endl;

}