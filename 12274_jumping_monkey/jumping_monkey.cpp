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
#include <cstdint>
#include <set>
#include <queue>

#define NODEMAX 21

using namespace std;

// 1 is not sure, 0 represents sure for not
// true if we are show that in pos there is no monkey
bool isSureinPosition(int u, int pos) {
    return ((u & (1 <<pos)) == 0);
}

typedef struct Node Node;

struct Node {
    int state;
    int path;
    Node * last;
};

bool visited[1 << NODEMAX];
int last[1 << NODEMAX];
int lastShot[1 << NODEMAX];
int BFS(int root, int state_transform[NODEMAX], int n, list<int> * path) {
    queue<int> Q;
    memset(visited, false, sizeof(visited));
    memset(last, 0, sizeof(last));
    memset(lastShot, 0, sizeof(lastShot));
    Q.push(root);

    visited[root] = true;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        // look for adj of u
        // shoot at tree i
        if (u == 0) {
            int count = 0;
            int k = u;
            while (k != root) {
                count ++;
                path -> push_front(lastShot[k]);
                k = last[k];
            }
            return count;
        }
        for (int i = 0; i < n; i++) {
            int v = 0;
            if (u&(1<<i)) {
                // for adj of tree i
                for (int j = 0; j < n; j++) {
                    if ((u&(1<< j)) && j!=i) {
                        v |= state_transform[j];
                    }
                }

                if (!visited[v]) {
                    visited[v] = true;
                    last[v] = u;
                    lastShot[v] = i;
                    Q.push(v);
                }
            }
        }
    }
    return -1;
}

int main() {
    int n,m;
    while (scanf("%d %d", &n, &m) == 2) {
        if (n == 0 && m == 0) break;
        int state_transform[NODEMAX];
        memset(state_transform, 0, sizeof(state_transform));
        int x,y;
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &x, &y);
            state_transform[x] |= ((int) 1) << y;
            state_transform[y] |= ((int) 1) << x;
        }

        if(m > n-1) {
            printf("Impossible\n");
            continue;
        }
        // BFS
        int root = (1 << n) -1;
        list<int> path;
        int len = BFS(root, state_transform, n, &path);
        if (len == -1) {
            printf("Impossible\n");
        } else {
            printf("%d:", len);
            for (int i: path) {
                printf(" %d", i);
            }
            printf("\n");
        }
    }
}
