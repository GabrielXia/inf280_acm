#include <stdio.h>
#include <array>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <string>
#include <memory.h>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <math.h>
#include <map>
#include <queue>
#define MAXN 500
#define MAXLEN 500000

using namespace std;

unsigned int Dijkstra(int root, int des, unsigned int path[MAXN][MAXN], int N, array<list<int>, MAXN> * last) {
    unsigned int Dist[MAXN];
    typedef pair<unsigned int, int> WeightNode; // weight goes first
    priority_queue<WeightNode, vector<WeightNode>, greater<WeightNode> > Q;
    fill_n(Dist, MAXN, MAXLEN);
    Dist[root] = 0;
    Q.push(make_pair(0, root));
    while (!Q.empty()) {
        int u = Q.top().second; // get node with least priority
        Q.pop();
        for (int v = 0; v < N; v++) {
            if (path[u][v] != MAXLEN) {
                unsigned int w = path[u][v];
                if (Dist[v] > Dist[u] + w) {
                    Dist[v] = Dist[u] + w;
                    Q.push(make_pair(Dist[v], v));
                    (*last).at(v).clear();
                    (*last).at(v).push_back(u);
                } else if (Dist[v] == Dist[u] + w) {
                    (*last).at(v).push_back(u);
                }
            }
        }
    }
    return Dist[des];
}

void removePath(int node, unsigned int  path[MAXN][MAXN], array<list<int>, MAXN> * last) {
    for (int l: last->at(node)) {
        path[l][node] = MAXLEN;
        removePath(l, path, last);
    }
}

int main() {
    int N,M,S,D,s,d;
    unsigned int w;
    unsigned int path[MAXN][MAXN];
    while (scanf("%d %d", &N, &M) == 2) {
        if (N == 0 && M ==0) {
            break;
        }
        scanf("%d %d", &S, &D);
        for (int i = 0; i < MAXN; i++) {
            fill_n(path[i], MAXN, MAXLEN);
        }
        for (int i = 0; i < M; i++) {
            scanf("%d %d %u", &s, &d, &w);
            path[s][d] = w;
        }

        array<list<int>, MAXN> last;
        Dijkstra(S, D, path, N, &last);

        removePath(D, path, &last);

        unsigned int result = Dijkstra(S, D, path, N, &last);
        if (result == MAXLEN) {
            printf("-1\n");
        } else {
            printf("%d\n", result);
        }
    }
    return 0;
}
