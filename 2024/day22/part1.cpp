#include "helpers.h"

long long mix(long long a, long long b) {
  return a^b;
}

long long prune(long long a) {
  return a % 16777216;
}

long long nextRandom(long long init) {
  init = prune(mix(init, init*64));
  init = prune(mix(init, init/32));
  init = prune(mix(init, init*2048));
  return init;
}

long long iterate(long long init, int n) {
  while (n--) {
    init = nextRandom(init);
  }
  return init;
}

int main() {

  long long sum = 0, num;
  while (cin >> num) {
    cout << num << ": " << iterate(num, 2000) << endl;
    sum += iterate(num, 2000);
  }

  cout << sum << endl;

  return 0;
}