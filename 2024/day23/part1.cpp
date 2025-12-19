#include "helpers.h"


bool hasT(string a) {
  return a[0] == 't';
}

void dfsVisit(int u, const vector<vector<int>>& adj, vector<int>& cc, int component) {
  for (auto v : adj[u]) {
    if (cc[v] == 0) {
      cc[v] = component;
      dfsVisit(v, adj, cc, component);
    }
  }
}

pair<vector<int>, int> dfs(const vector<vector<int>>& adj) {
  int n = adj.size(), component = 1;
  vector<int> cc(n, 0);

  for (int u = 0; u < n; ++u) {
    if (cc[u] == 0) {
      cc[u] = component;
      dfsVisit(u, adj, cc, component);
      ++component;
    }
  }
  cout << "COMPONENTS: " << component-1 << endl;
  return pair(cc, component-1);
}

int main() {

  string line, a, b;
  map<string, int> nameToIndex;
  vector<string> nodes;
  vector<vector<int>> adj;
  int numNodes = 0;
  while (getline(cin, line)) {
    a = line.substr(0, 2), b = line.substr(3, 2);
    if (nameToIndex.count(a) == 0) {
      nameToIndex[a] = numNodes++;
      nodes.push_back(a);
      adj.push_back(vector<int>());
    }
    if (nameToIndex.count(b) == 0) {
      nameToIndex[b] = numNodes++;
      nodes.push_back(b);
      adj.push_back(vector<int>());
    }

    int index1 = nameToIndex[a], index2 = nameToIndex[b];
    adj[index1].push_back(index2);
    adj[index2].push_back(index1);
  }
  
  // cout << nodes;

  // for (const auto& [key, val] : nameToIndex) {
  //   cout << key << ": " << val << endl;
  // }

  // for (int i = 0; i < adj.size(); ++i) {
  //   cout << i << " - " << nodes[i] << ": ";
  //   for (auto n : adj[i]) cout << nodes[n] << " ";
  //   cout << endl;
  // }

  // cout << "Nodes with T: " << count_if(nodes.begin(), nodes.end(), hasT) << endl;

  // auto [cc, numComponents] = dfs(adj);

  // cout << cc;

  int singleT = 0, doubleT = 0, tripleT = 0;
  for (int u = 0; u < nodes.size(); ++u) {
    if (hasT(nodes[u])) {
      for (int i = 0; i < adj[u].size(); ++i) {
        for (int j = i+1; j < adj[u].size(); ++j) {
          int Ts = 0;
          if (find(adj[adj[u][i]].begin(), adj[adj[u][i]].end(), adj[u][j]) != adj[adj[u][i]].end()) {
            if (hasT(nodes[u])) ++Ts;
            if (hasT(nodes[adj[u][i]])) ++Ts;
            if (hasT(nodes[adj[u][j]])) ++Ts;
            if (Ts == 1) ++singleT;
            else if (Ts == 2) ++doubleT;
            else ++tripleT;
          }
        }
      }
    }
  }

  cout << "Nodes: " << nodes.size() << endl;

  cout << singleT << " " << doubleT << " " << tripleT << endl;
  int sum = 0;
  sum = singleT + (doubleT/2) + (tripleT/3);
  cout << sum << endl;
  
  return 0;
}