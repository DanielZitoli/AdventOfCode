#include "helpers.h"


bool canCalibrate(long long a, int i, vector<long long>& nums) {
  
  // if (nums[i]) {
  //   cout << "Here: " << i << endl;
  //   for (auto n : nums) {
  //     cout << n << " ";
  //   }
  //   cout << endl;
  // }
  if (i == nums.size()) return false;
  if (i+1 == nums.size()) return a == nums[i];
  if (a % nums[i] == 0 && canCalibrate(a/nums[i], i+1, nums)) {
    return true;
  }
  if (canCalibrate(a-nums[i], i+1, nums)) {
    return true;
  }
  long long ten = 10;
  long long temp = nums[i];
  while (temp != 0) {
    if (temp % ten == a % ten) {
      a /= ten;
      temp /= ten;
    } else {
      return false;
    }
  }
  return canCalibrate(a, i+1, nums);
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
      if (num == 0) cout << "HERE\n";
      nums.push_back(num);
    }
    reverse(nums.begin(), nums.end());
    
    if (canCalibrate(a, 0, nums)) {
      sum += a;
    }
  }

  cout << sum << endl;
}