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
#include <list>
#define MAXNODE 51

using namespace std;

int main() {
    int T, N;
    scanf("%d", &T);
    int x, y;
    int index = 0;
    for (int i = 0; i < T; i++) {
        array<list<int>, MAXNODE> adj;
        scanf("%d", &N);
        int first, second;
        for (int j = 0; j < N; j++) {
            scanf("%d %d", &x, &y);
            if (j == 0) {
              first = x;
              second = y;
            }
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        vector<int> circuit;

        stack<int> s;
        int v = first;
        s.push(v);
        s.push(v);
        adj[v].erase(find(adj[v].begin(), adj[v].end(), second));
        adj[second].erase(find(adj[second].begin(), adj[second].end(), v));
        v = second;
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
        index ++;
        printf("Case #%d\n", index);
        if ((*circuit.begin()) != (*(circuit.end()-1))) {
            printf("some beads may be lost\n");
        } else {
            for(int k = (int)circuit.size()-1; k > 0; k--) {
                printf("%d %d\n", circuit.at(k), circuit.at(k-1));
            }
        }
        if (index != T) {
          printf("\n");
        }
    }
    return 0;
}
