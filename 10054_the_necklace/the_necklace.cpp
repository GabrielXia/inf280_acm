#include <stdio.h>
#include <array>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <memory.h>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <math.h>
#include <utility>
#include <stack>
#define MAXNODE 50

int int main() {

  int T, N;
  scanf("%d", &T);

  int x, y;
  for (int i = 0; i < T; i++) {
    array<list<int>, MAXNODE> adj;
    scanf("%d", &N);
    for (int j = 0; j < N; j++) {
      scanf("%d %d", &x, &y);
      adj[x].push_back(y);
      adj[y].push_back(x);
    }

    vector<int> circuit;
    int v = y;
    stack<int> s;
    s.push(v);
    while (!s.empty()) {
      if (!adj[v].empty()) {
        s.push(v);
        int tmp = *adj[v].begin();
        adj[v].erase(adj[v].begin());
        adj[tmp].erase(find(adj[tmp].begin(), adj[tmp].end(), v));
        v = tmp;
      } else {
        circuit.push_back(v);
        v = s.top();
        s.pop();
      }
    }

  }

  return 0;
}
