#include "helpers.h"

struct Rule {
  string firstArg, op, secondArg;
  Rule() {}
  Rule(string a, string op, string b): firstArg{a}, op{op}, secondArg{b} {}

  bool performOp(bool a, bool b) {
    if (op == "XOR") return a ^ b;
    else if (op == "AND") return a && b;
    else if (op == "OR") return a || b;
    else {
      cout << "ERROR" << endl;
      return false;
    }
  }
};

// int opToCode(string op) {
//   if (op == "XOR") return 1;
//   else if (op == "AND") return 2;
//   else if (op == "OR") return 3;
//   else {
//     cout << "ERROR" << endl;
//     return -100;
//   }
// }

bool solve(string symbol, map<string, bool>& values, map<string, Rule>& rules) {
  if (values.count(symbol) > 0) {
    return values[symbol];
  }
  Rule r = rules.at(symbol);
  solve(r.firstArg, values, rules);
  solve(r.secondArg, values, rules);
  values[symbol] = r.performOp(values[r.firstArg], values[r.secondArg]);
  return values[symbol];
}

int main() {
  int XOR = 1, AND = 2, OR = 3;

  map<string, bool> values;
  map<string, Rule> rules;
  set<string> symbols;

  string line;
  while (getline(cin, line)) {
    if (line.empty()) break;
    // cout << line.substr(0, 3) << " - " << line[5] << endl;
    values[line.substr(0, 3)] = (line[5] == '1');
    symbols.insert(line.substr(0, 3));
  }

  while (getline(cin, line)) {
    istringstream stream(line);
    string a, op, b, arrow, output;
    stream >> a >> op >> b >> arrow >> output;

    // cout << pair(a, b) << " - " << opToCode(op) << " -> " << output;
    rules.insert(pair(output, Rule(a, op, b)));
    symbols.insert(output);
  }

  // for (auto& [key, val] : values) {
  //   cout << key << ": " << val << endl;
  // } cout << endl;

  // for (auto& [key, rule] : rules) {
  //   cout << rule.firstArg << " " << rule.op << " " << rule.secondArg << " -> "  << key << endl;
  // } cout << endl;

  vector<string> z;
  for (auto symbol : symbols) {
    if (symbol[0] == 'z') {
      z.push_back(symbol);
    }
  }
  sort(z.begin(), z.end());

  cout << z;

  long long result = 0, pow = 1;
  for (int i = 0; i < z.size(); ++i) {
    if (solve(z[i], values, rules)) {
      // result += static_cast<long long>(1<<i);
      result += pow;
      cout << "1";
    } else {
      cout << "0";
    }
    pow *= 2;
  } cout << endl;

  cout << result << endl;

  // for (auto [key, val] : values) {
  //   cout << key << ": " << val << endl;
  // }


}