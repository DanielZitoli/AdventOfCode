#include "helpers.h"

int main() {

  vector<string> lines;
  vector<string> ops;
  string line;
  while (getline(cin, line)) {
    if (line[0] == '+' || line[0] == '*') {
      ops = splitString(line, ' ');
    } else {
      lines.push_back(line);
    }
  }

  
  
  long total = 0, ans;
  int opIndex = 0;
  if (ops[opIndex] == "+") ans = 0;
  else ans = 1;

  vector<string> nums;
  for (int i = 0; i < lines[0].size(); ++i) {
    string col;
    for (int j = 0; j < lines.size(); ++j) {
      col += lines[j][i];
    }

    cout << col << endl;

    if(col.find_first_not_of(' ') == string::npos) {
      total += ans;
      cout << "here: " << ans << endl;
      ++opIndex;
      if (ops[opIndex] == "+") ans = 0;
      else ans = 1;
    } else {
      long num = stol(col);
      if (ops[opIndex] == "+") ans += num;
      else ans *= num;
    }
  }
  total += ans;

  cout << total << endl;
  return 0;
}