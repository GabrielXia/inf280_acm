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
    return (u & (((int) 1) <<pos)) == 0;
}

typedef struct Node Node;

struct Node {
    int state;
    int path;
    Node * last;
};

bool visited[((int)1) << NODEMAX];

int BFS(int root, int state_transform[NODEMAX], int n, list<int> * path) {
    queue<Node> Q;
    memset(visited, false, sizeof(visited));
    Q.push({root, 100, nullptr});
    visited[root] = true;
    while (!Q.empty()) {
        Node * node = & Q.front();
        int u = node -> state; Q.pop();
        // check if u is final state
        if (u == 0) {
            int count = 0;
            while ((node->path) != 100) {
                count ++;
                path -> push_front(node -> path);
                node = node -> last;
            }
            return count;
        }
        // look for adj of u
        // shoot at tree i
        for (int i = 0; i < n; i++) {
            int v = 0;
            if (! isSureinPosition(u, i)) {
                // for adj of tree i
                int uNew = u & (~(((int) 1) << i));
                for (int j = 0; j < n; j++) {
                    if (!isSureinPosition(uNew, j) && j!=i) {
                        v |= state_transform[j];
                    }
                }
                if (!visited[v]) {
                    Q.push({v, i, node});
                    visited[v] = true;
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
        memset(state_transform, 0, sizeof(int)*NODEMAX);
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
        int root = (((int) 1) << n) -1;
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
