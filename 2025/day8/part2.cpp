#include "helpers.h"

double distance(vector<int> &i, vector<int> &j) {
  double sum = pow((i[0]-j[0]), 2) + pow((i[1]-j[1]), 2) + pow((i[2]-j[2]), 2); 
  return sqrt(sum);
}

int find(vector<int> &components, int i) {
  while (components[i] != i) {
    i = components[i];
  }
  return i;
}

bool union_(vector<int> &components, int i, int j) {
  // cout << i << " and " << j << endl;
  int parent_i = find(components, i), parent_j = find(components, j);
  if (parent_i != parent_j) {
    components[parent_i] = components[parent_j];
    return true;
  }
  return false;
}

void printCounts(vector<int> &components) {
  int n = components.size();
  vector<int> counts(n, 0);
  for (int i = 0; i < n; ++i) {
    ++counts[find(components, i)];
  }

  sort(counts.begin(), counts.end(), [](int a, int b) { return a > b; } );

  cout << counts;
}

int main() {

  string line;
  int k;
  getline(cin, line);
  stringstream sstream(line);
  sstream >> k;

  vector<vector<int>> points;
  while(getline(cin, line)) {
    points.push_back(extractIntegers(line));
  }

  int n = points.size();
  vector<vector<double>> distances(n, vector<double>(n, 0));

  
  vector<pair<int, int>> connections;
  for (int i = 0; i < n; ++i) {
    for (int j = i+1; j < n; ++j) {
      connections.push_back(pair(i, j));
      distances[i][j] = distance(points[i], points[j]);
      distances[j][i] = distances[i][j];
    }
  }

  sort(connections.begin(), connections.end(), [&distances](auto &p1, auto &p2) { 
    return distances[p1.first][p1.second] < distances[p2.first][p2.second]; 
  });

  vector<int> components(n, 0);
  for (int i = 0; i < n; ++i) components[i] = i;

  int a, b;
  long count = 0;
  for (int i = 0; i < connections.size(); ++i) {
    a = connections[i].first, b = connections[i].second;
    if (union_(components, a, b)) {
      ++count;
    }
    if (count == n-1) {
      cout << (long) points[a][0] * (long) points[b][0] << endl;
      break;
    }
  } 


  return 0;
}
