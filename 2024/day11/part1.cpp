#include "helpers.h"

pair<bool, pair<long long, long long>> splitEvenDigits(long long n) {
  if (n == 0) return {false, pair(0, 0)};

  long long k = n, numDigits = 0;
  while (k != 0) {
    k = k / 10;
    ++numDigits;
  }
  long long power = pow(10, numDigits/2);
  return {numDigits%2 == 0, pair(n / power, n % power)};
}



long long solve(long long num, int blinks, vector<vector<long long>>& cache) {
  if (blinks == 0) return 1;

  long long ans;
  bool valid = num < cache.size();
  if (valid && cache[num][blinks] != -1) return cache[num][blinks];

  if (num == 0) {
    ans = solve(1, blinks-1, cache);
  } else {
    bool even;
    pair<long long, long long> digits;
    tie(even, digits) = splitEvenDigits(num);
    if (even) {
      ans = solve(digits.first, blinks-1, cache) + solve(digits.second, blinks-1, cache);
    } else {
      ans = solve(num*2024, blinks-1, cache);
    }
  }

  return valid? (cache[num][blinks] = ans): ans;
}

int main() {

  vector<long long> nums;
  long long data;
  while (cin >> data) nums.push_back(data);
  cout << nums;

  const int CACHE_SIZE = 10000;
  vector<vector<long long>> cache(CACHE_SIZE, vector<long long>(80, -1));

  long long sum = 0;
  for (auto n : nums) {
    cout << solve(n, 75, cache) << " ";
    sum += solve(n, 75, cache);
  }
  cout << endl << sum << endl;

  return 0;
}