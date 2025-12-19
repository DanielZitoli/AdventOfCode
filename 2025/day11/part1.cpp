#include "helpers.h"

int getId(map<string, int> &namesToId, vector<string> &idToNames, string source) {
  if (namesToId.find(source) == namesToId.end()) {
    int newId = idToNames.size();
    namesToId[source] = newId;
    idToNames.push_back(source);
  }
  return namesToId[source];
}


int main() {

  map<string, int> namesToId;
  vector<string> idToNames;
  vector<vector<int>> adj;

  string line;
  while(getline(cin, line)) {
    auto names = splitString(line, ' ');

    string source = names[0].substr(0, names[0].size()-1);
    int sourceId = getId(namesToId, idToNames, source);

    if (adj.size() <= sourceId) adj.resize(sourceId+1);

    for (int i = 1; i < names.size(); ++i) {
      int id = getId(namesToId, idToNames, names[i]);
      adj[sourceId].push_back(id); 
    }
  }

  cout << idToNames;
  cout << adj;

  int n = idToNames.size();

  vector<int> inDegree(n, 0);
  for (auto &node : adj) {
    for (auto neigh : node) ++inDegree[neigh];
  }

  cout << inDegree;

  stack<int> s;
  for (int i = 0; i < n; ++i) {
    if (inDegree[i] == 0) s.push(i);
  }

  // find topo order
  vector<int> order;
  while (!s.empty()) {
    int u = s.top(); s.pop();
    order.push_back(u);
    for (auto v : adj[u]) {
      --inDegree[v];
      if (inDegree[v] == 0) {
        s.push(v);
      }
    }
  }

  if (order.size() != n) cout << "GRAPH CONTAINS A CYCLE!" << endl;

  int youId = namesToId["you"], outId = namesToId["out"];
  vector<int> numPaths(n, 0);
  numPaths[outId] = 1;

  for (int i = n-1; i >= 0; --i) {
    int u = order[i];
    for (auto v : adj[u]) numPaths[u] += numPaths[v];
  }

  cout << numPaths;
  cout << "Answer: " << numPaths[youId] << endl;

  return 0;
}