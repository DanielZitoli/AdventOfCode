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

int encode(vector<int>& nums, int index) {
  int base = 20, power = 1, result = 0;
  for (int i = 0; i < 4; ++i) {
    result += (nums[index+i]+9)*power;
    power *= base;
  }
  return result;
}

vector<int> decode(int code) {
  int base = 20;
  vector<int> result;
  for (int i = 0; i < 4; ++i) {
    result.push_back((code%base)-9);
    code /= base;
  }
  return result;
}

// returns a map that maps each sequence of 4 changes represented as encoded int, to the first 
// instance of that change pattern and the number it maps to
map<int, int> getSellingData(long long num, int iterations) {
  vector<int> changes, bananas{static_cast<int>(num)%10};
  int cur, prev = num;
  for (int i = 1; i < iterations; ++i) {
    cur = nextRandom(prev);
    changes.push_back((cur%10) - (prev%10));
    bananas.push_back(cur%10);
    prev = cur;
  }

  // cout << changes;
  // cout << bananas;

  map<int, int> result;
  for (int i = 0; i < changes.size()-3; ++i) {
    int code = encode(changes, i);
    int value = bananas[i+4];

    if (result.count(code) == 0) {
      result[code] = value;
    }
  }

  // for (auto& [key, value] : result) {
  //   cout << Point(key, value) << " ";
  // } cout << endl << endl;

  return result;
} 

int calculateSum(vector<map<int, int>>& sellingData, int code) {
  int sum = 0;
  for (auto& data : sellingData) {
    if (data.count(code)>0) sum += data[code];
  }
  return sum;
}

int main() {




  long long num;
  vector<map<int, int>> sellingData;
  set<int> combinedChangeCodes;
  while (cin >> num) {
    map<int, int> result = getSellingData(num, 2000);
    for (const auto& [key, value] : result) {
      combinedChangeCodes.insert(key);
    }
    sellingData.push_back(result);
  }

  // for (auto n : combinedChangeCodes) cout << n << " ";
  // cout << endl;

  int bestSum = 0;
  vector<int> bestCode;
  for (auto key : combinedChangeCodes) {
    int sum = calculateSum(sellingData, key);
    if (sum > bestSum) {
      bestSum = sum;
      bestCode = decode(key);
    }
  }

  cout << bestSum << endl;
  cout << bestCode;

  return 0;
}