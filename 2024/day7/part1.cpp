#include "helpers.h"


bool canCalibrate(long long a, int i, vector<long long>& nums) {
  if (i == nums.size()) return false;
  if (i+1 == nums.size()) return a == nums[i];
  if (a % nums[i] == 0 && canCalibrate(a/nums[i], i+1, nums)) {
    return true;
  }
  if (canCalibrate(a-nums[i], i+1, nums)) {
    return true;
  }
  return false;
}

int main() {
  string line;

  long long sum = 0;

  while (getline(cin, line)) {
    long long a, num;
    char c;
    istringstream stream(line);
    stream >> a >> c;
    vector<long long> nums;
    while (stream >> num) {
      nums.push_back(num);
    }
    reverse(nums.begin(), nums.end());

    for (auto n : nums) cout << n << " ";
    cout << endl;
    if (canCalibrate(a, 0, nums)) {
      sum += a;
    }
  }

  cout << sum << endl;
}