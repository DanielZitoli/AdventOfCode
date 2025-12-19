#include "helpers.h"

std::vector<int> append(const vector<int>& vec, int value) {
  std::vector<int> newVec(vec); // Copy the original vector
  newVec.push_back(value);     // Append the new element
  return newVec;
}

bool isSubset(const vector<int>& A, const vector<int>& B) {
  for (int x : A) {
    if (find(B.begin(), B.end(), x) == B.end()) {
      return false; // Element in A not found in B
    }
  }
  return true; // All elements of A are in B
}

void largestClique(const vector<vector<int>>& adj) {
  vector<vector<int>> cur, next;
  for (int u = 0; u < adj.size(); ++u) {
    for (auto v : adj[u]) {
      cur.push_back(vector<int>{u, v});
    }
  }
  int size = 2;
  while (!cur.empty()) {
    for (auto& clique : cur) {
      int u = clique[0];
      for (auto v : adj[u]) {
        if (isSubset(clique, adj[v])) {
          next.push_back(append(clique, v));
        }
      }
    }

    cout << "size " << size <<  ": " << cur[0];
    cout << "cliques of size " << size++ << ": " << cur.size() << endl;
    cur = next;
  }
}

long long encode(const vector<int>& nums, int base) {
  long long sum = 0, power = 1;
  for (int i = 0; i < nums.size(); ++i) {
    sum += (nums[i]*power);
    power *= base;
  }
  return sum;
}

vector<int> decode(long long num, int base) {
  vector<int> result;
  while (num != 0) {
    result.push_back(num%base);
    num /= base;
  }
  return result;
}

vector<int> add(const vector<int>& vec, int value) {
  vector<int> newVec(vec); // Copy the original vector
  newVec.push_back(value); // Append the new element
  sort(newVec.begin(), newVec.end());
  return newVec;
}

vector<int> intersect(const vector<int>& vec1, const vector<int>& vec2) {
  set<int> nums(vec1.begin(), vec1.end());
  vector<int> result;
  for (auto n : vec2) {
    if (nums.count(n) > 0) {
      result.push_back(n);
    }
  }
  return result;
}

void largestCliqueSet(const vector<vector<int>>& adj, const vector<string>& nodes) {
  int n = adj.size();
  set<long long> cur;
  for (int u = 0; u < n; ++u) {
    for (auto v : adj[u]) {
      if (u < v) {
        cur.insert(encode(vector<int>{u, v}, n));
      }
    }
  }
  int size = 2;
  while (!cur.empty()) {
    set<long long> next;
    for (auto& key : cur) {
      vector<int> clique = decode(key, n);
      int u = clique[0];
      for (auto v : adj[u]) {
        if (isSubset(clique, adj[v])) {
          next.insert(encode(add(clique, v), n));
        }
      }
    }

    vector<int> bestClique = decode(*cur.begin(), n);
    cout << "size " << size <<  ": " << bestClique;
    cout << "cliques of size " << size++ << ": " << cur.size() << endl;
    cout << "name of nodes: "; for_each(bestClique.begin(), bestClique.end(), [&nodes](int a){ cout << nodes[a] << " "; });
    cout << endl;
    cur = next;
  }
}

void BronKerbosch(vector<int> R, vector<int> P, vector<int> X, const vector<vector<int>>& adj, vector<int>& optClique) {
  if (P.empty() && X.empty()) {
    if (R.size() > optClique.size()) {
      optClique = R;
    }
    return;
  }
  int u = (P.empty())? X[0]: P[0];
  for (auto v : P) {
    if (find(adj[u].begin(), adj[u].end(), v) == adj[u].end()) {
      BronKerbosch(add(R, v), intersect(P, adj[v]), intersect(X, adj[v]), adj, optClique);
      // auto it = find(P.begin(), P.end(), v);
      // P.erase(it);
      P.erase(remove(P.begin(), P.end(), v), P.end());
      X.push_back(v);
    }
  }
}

vector<int> RunBronKerbosch(const vector<vector<int>>& adj) {
  vector<int> nodes(adj.size());
  for (int i = 0; i < adj.size(); ++i) nodes[i] = i;
  vector<int> optClique;
  BronKerbosch(vector<int>(), nodes, vector<int>(), adj, optClique);
  return optClique;
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

  int n = nodes.size();
  cout << n << endl;

  // vector<int> nums{1, 5, 3, 9, 7};
  // cout << add(nums, 4);

  // vector<int> vec1{1, 5, 3, 11, 9, 7}, vec2{1, 7, 8, 2, 10, 5};
  // cout << intersect(vec1, vec2);

  cout << RunBronKerbosch(adj);

  auto clique = RunBronKerbosch(adj);
  vector<string> lanParty;
  for (auto u : clique) lanParty.push_back(nodes[u]);
  sort(lanParty.begin(), lanParty.end());
  for (auto name : lanParty) cout << name << ",";
  cout << endl;




  // largestCliqueSet(adj, nodes);



  // int singleT = 0, doubleT = 0, tripleT = 0;
  // for (int u = 0; u < nodes.size(); ++u) {
  //   if (hasT(nodes[u])) {
  //     for (int i = 0; i < adj[u].size(); ++i) {
  //       for (int j = i+1; j < adj[u].size(); ++j) {
  //         int Ts = 0;
  //         if (find(adj[adj[u][i]].begin(), adj[adj[u][i]].end(), adj[u][j]) != adj[adj[u][i]].end()) {
  //           if (hasT(nodes[u])) ++Ts;
  //           if (hasT(nodes[adj[u][i]])) ++Ts;
  //           if (hasT(nodes[adj[u][j]])) ++Ts;
  //           if (Ts == 1) ++singleT;
  //           else if (Ts == 2) ++doubleT;
  //           else ++tripleT;
  //         }
  //       }
  //     }
  //   }
  // }
  
  return 0;
}