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
#define qMax 9
#define NODEMAX 1000
#define COSTMAX 18000000000

using namespace std;

map<int, pair<int, unsigned int>> Sets; // map to parent & rank
void MakeSet(int x) {
    Sets.insert(make_pair(x, make_pair(x, 0)));
}
int Find(int x) {
    if (Sets[x].first == x) return x; // Parent == x ?
    else return Sets[x].first = Find(Sets[x].first); // Get Parent
}
void Union(int x, int y) {
    int parentX = Find(x), parentY = Find(y);
    int rankX = Sets[parentX].second, rankY = Sets[parentY].second;
    if (parentX == parentY) return;
    else if (rankX < rankY)
        Sets[parentX].first = parentY;
    else
        Sets[parentY].first = parentX;
    if (rankX == rankY)
        Sets[parentX].second++;
}

int main() {
    int caseNum;
    scanf("%d", &caseNum);
    int n,q;
    int subnetPrice[qMax];
    int num_in_net;
    int node;
    int pos[NODEMAX][2];
    for (int i = 0; i < caseNum; i++) {
        getchar();
        scanf("%d %d", &n, &q);
        array<list<int>, qMax> subnet;
        for (int j = 0; j < q; j++) {
            scanf("%d %d", &num_in_net, &subnetPrice[j]);
            for (int k = 0; k < num_in_net; k++) {
                scanf("%d", &node);
                subnet[j].push_back(node);
            }
        }
        for (int j = 0; j < n; j++) {
            scanf("%d %d", &pos[j][0], &pos[j][1]);
        }
        vector<pair<int, pair<int, int> > > Edges;
        for (int j = 0; j < n; j++) {
            for (int k = j+1; k < n; k++) {
                long distance = pow(pos[j][0] - pos[k][0], 2) + pow(pos[j][1] - pos[k][1], 2);
                Edges.push_back(make_pair(distance, make_pair(j, k)));
            }
        }

        // kruskal for the first time without subnet
        Sets.clear();
        for (int j = 0; j < n; j++) {
            MakeSet(j);
        }
        sort(Edges.begin(), Edges.end());
        vector<pair<int, pair<int, int> > > A;
        for(auto tmp : Edges) {
          auto edge = tmp.second;
          if (Find(edge.first) != Find(edge.second)) {
            Union(edge.first, edge.second); // update Union-Find
            A.push_back(tmp); // include edge in MST
          }
        }

        // only consider edges that chosen by algo
        sort(A.begin(), A.end());
        long long cMin = COSTMAX;
        for (int s = 0; s < (1 << q); s++) {
            long long c = 0;
            Sets.clear();
            for (int j = 0; j < n; j++) {
                MakeSet(j);
            }
            for (int j = 0; j < q; j++) {
                if (s & (1 << j)) {
                    c += subnetPrice[j];
                    for(auto tmp: subnet[j]) {
                        Union(subnet[j].front()-1, tmp-1);
                    }
                }
            }

            for(auto tmp : A) {
                auto edge = tmp.second;
                if (Find(edge.first) != Find(edge.second)) {
                    Union(edge.first, edge.second);
                    c += tmp.first;
                }
            }
            cMin = min(c, cMin);
        }

        printf("%lld\n", cMin);
        if (i != caseNum -1) printf("\n");
    }
}
