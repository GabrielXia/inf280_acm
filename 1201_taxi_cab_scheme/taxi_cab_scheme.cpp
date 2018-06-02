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
#include <map>
#include <queue>
#define INF 1000
#define MAXNODE 501
#define NIL 500

using namespace std;

bool BFS(int M, unsigned int *Dist, int PairX[MAXNODE], int PairY[MAXNODE], vector<int> Adj[MAXNODE]) {
    queue<int> Q;
    Dist[NIL] = INF;
    for(int x = 0; x < M; x++) {
        Dist[x] = (PairX[x] == NIL) ? 0 : INF;
        if (PairX[x] == NIL)
            Q.push(x);
    }
    while (!Q.empty()) { // find all shortest paths to NIL
        int x = Q.front(); Q.pop();
        if (Dist[x] < Dist[NIL]) // can this become a shorter path?
            for (auto y : Adj[x])
                if (Dist[PairY[y]] == INF) {
                    Dist[PairY[y]] = Dist[x] + 1; // update path length
                    Q.push(PairY[y]);
                }
    }
    return Dist[NIL] != INF; // any shortest path to NIL found?
}

bool DFS(int x, int *PairX, int *PairY, vector<int> Adj[MAXNODE], unsigned int *Dist) {
    if (x == NIL)
        return true; // reached NIL
    for (auto y : Adj[x])
        if (Dist[PairY[y]] == Dist[x] + 1 &&
            DFS(PairY[y], PairX, PairY, Adj, Dist)) { // follow trace of BFS
            PairX[x] = y; // add edge from x to y to matching
            PairY[y] = x;
            return true;
        }
    Dist[x] = INF;
    return false; // no augmenting path found
}

int main() {
    int N, M;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &M);
        int startTime[MAXNODE], endTime[MAXNODE], startPos[MAXNODE][2], endPos[MAXNODE][2];
        for (int j = 0; j < M; j++) {
            int h, m, sx, sy, ex, ey;
            scanf("%d:%d %d %d %d %d", &h, &m, &sx, &sy, &ex, &ey);
            startTime[j] = h * 60 + m;
            int dis = abs(sx - ex) + abs(sy - ey);
            endTime[j] = h * 60 + m + dis;
            startPos[j][0] = sx;
            startPos[j][1] = sy;
            endPos[j][0] = ex;
            endPos[j][1] = ey;
        }
        // build graph end -> start
        vector<int> Adj[MAXNODE];
        for (int j = 0; j < M; j++) {
            for (int k = j + 1; k < M; k++) {
                if (startTime[k] - endTime[j] > (abs(startPos[k][0]- endPos[j][0]) + abs(startPos[k][1] - endPos[j][1]))) {
                    Adj[j].push_back(k);
                }
            }
        }

        // hopcroft karp
        unsigned int Dist[MAXNODE];
        int PairX[MAXNODE];
        int PairY[MAXNODE];
        fill_n(PairX, MAXNODE, NIL);
        fill_n(PairY, MAXNODE, NIL);
        int Matching = 0;
        while (BFS(M, Dist, PairX, PairY, Adj)) {
            for (int x = 0; x < M; x++) {
                if (PairX[x] == NIL && DFS(x, PairX, PairY, Adj, Dist)) {
                    Matching ++;
                }
            }
        }
        int car = M - Matching;
        printf("%d\n", car);
    }
}
