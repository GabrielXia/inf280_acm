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
#include <map>
#include <queue>
#define MAXNODE 50

using namespace std;


int BFS(int root, bool path[MAXNODE][MAXNODE], int nodeNum) {
  queue<int> Q;
  bool visited[MAXNODE] = {};
  memset(visited, false, sizeof(visited[0]*MAXNODE));
  int distance[MAXNODE] = {};
  memset(distance, 0, sizeof(distance[0]*MAXNODE));
  Q.push(root);
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    if (visited[u]) continue;
    visited[u] = true;
    for (int i=0; i<nodeNum; i++) {
      if (path[u][i]) {
        distance[i] = distance[u] +1;
        Q.push(i);
      }
    }
  }

  int maxValue = 0;
  for (int i = 0; i < nodeNum; i++) {
    if(!visited[i]) return -1;
    if (distance[i] > maxValue) {
      maxValue = distance[i];
    }
  }
  return maxValue;
}

int main() {
    int p, r;
    bool path[MAXNODE][MAXNODE];
    int netWork = 0;
    while (scanf("%d %d", &p, &r) == 2) {
      if (p == 0 && r == 0) {
        break;
      }
      netWork ++;

      // read
      map<string, int> record = {};
      memset(path, false, sizeof(path[0][0])*MAXNODE*MAXNODE);
      int index = 0;
      for (int i = 0; i < r; i++) {
        char name1[50], name2[50];
        scanf("%s %s", name1, name2);
        if (record.find(name1) == record.end()) {
          record.insert(pair<string, int>(name1, index++));
        }
        if (record.find(name2) == record.end()) {
          record.insert(pair<string, int>(name2, index++));
        }
        int pos1 = record.find(name1)-> second;
        int pos2 = record.find(name2) -> second;
        path[pos1][pos2] = true;
        path[pos2][pos1] = true;
      }

      if(record.size() < p) {
        printf("Network %d: DISCONNECTED\n\n", netWork);
      }

      int result = 0;
      for (int i = 0; i < p; i++) {
        int maxDepth = BFS(i, path, p);
        if (maxDepth == -1) {
          printf("Network %d: DISCONNECTED\n\n", netWork);
          break;
        } else {
          if(result < maxDepth) {
            result = maxDepth;
          }
        }

        if (i == p-1) {
          printf("Network %d: %d\n\n", netWork, result);
        }
      }
    }

}
