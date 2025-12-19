#include "helpers.h"

int main() {

  string line;
  getline(cin, line);

  vector<pair<int, int>> fileBlocks, spaceBlocks; // block of size 'first' starting at index 'second'
  int index = 0, id = 0;
  for (int i = 0; i < line.size(); ++i) {
    int n = line[i]-'0';
    if (i%2 == 0) {
      fileBlocks.push_back(pair(n, index));
    } else {
      spaceBlocks.push_back(pair(n, index));
    }
    index += n;
  }

  vector<int> memory(index);
  for (int i = 0; i < fileBlocks.size(); ++i) {
    int fileSize, fileIndex;
    tie(fileSize, fileIndex) = fileBlocks[i];
    for (int j = 0; j < fileSize; ++j) {
      memory[fileIndex+j] = i;
    }
  }

  int file = fileBlocks.size()-1, fileSize, fileIndex, spaceSize, spaceIndex;

  for (int file = fileBlocks.size()-1; file >= 0; --file) {
    tie(fileSize, fileIndex) = fileBlocks[file];
    auto firstFit = find_if(spaceBlocks.begin(), spaceBlocks.end(), [fileSize, fileIndex](pair<int, int> p) { return (p.first >= fileSize) && (p.second < fileIndex); });
    if (firstFit != spaceBlocks.end()) {
      tie(spaceSize, spaceIndex) = *firstFit;
      // replace file with 0's
      for (int i = 0; i < fileSize; ++i) {
        memory[fileIndex+i] = 0;
      }
      // place file in open space
      for (int i = 0; i < fileSize; ++i) {
        memory[spaceIndex+i] = file;
      }
      firstFit->first -= fileSize;
      firstFit->second += fileSize;
    }

    // for (auto n : memory) cout << n;
    // cout << endl;
  }

  long long sum = 0;
  for (int i = 0; i < memory.size(); ++i) {
    sum += static_cast<long long>(i) * memory[i];
  }

  cout << endl << sum << endl;


  return 0;
}