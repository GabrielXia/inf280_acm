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
#include <unordered_set>
#include <utility>
#define MAXNODE 50
#define PERIODE 5040

using namespace std;

struct myHash {
    size_t operator()(pair<int, int> node) const {
        return static_cast<size_t>(node.first * 2501 + node.second);
    }
};

bool ifPossible(int x, int y, int t, int road, int freq, int N) {
  if ((x >= N)||(y >= N)||(x<0)||(y < 0)) return false;
  if (freq == 0) return (road == 1) ? true:false;
  if (t / freq % 2 != road) {
    return true;
  }
  return false;
}

int BFS(pair<int, int> root, int road[MAXNODE][MAXNODE], int freq[MAXNODE][MAXNODE], int N) {
  unordered_set<pair<int,int>, myHash> s;
  queue<pair<int,int>> q;
  q.push(root);
  while (!q.empty()) {
    pair<int,int> u = q.front();
    q.pop();
    auto it = s.find(u);
    if (it != s.end()) {
      continue;
    }
    s.insert(u);

    int x = u.second / MAXNODE;
    int y = u.second % MAXNODE;
    int t = u.first;

    // check
    if (u.second == (N-1)* MAXNODE + N-1) return u.first;

    // stay
    int t_n = (t + 1) % PERIODE;
    if (ifPossible(x, y, t_n, road[x][y], freq[x][y], N)) {
      q.push(make_pair(t_n, x*MAXNODE+y));
    }
    // left
    if (ifPossible(x, y-1, t_n, road[x][y-1], freq[x][y-1], N)) {
      q.push(make_pair(t_n, x*MAXNODE+y-1));
    }
    // right
    if (ifPossible(x, y+1, t_n, road[x][y+1], freq[x][y+1], N)) {
      q.push(make_pair(t_n, x*MAXNODE+y+1));
    }
    // up
    if (ifPossible(x-1, y, t_n, road[x-1][y], freq[x-1][y], N)) {
      q.push(make_pair(t_n, (x-1)*MAXNODE+y));
    }
    // down
    if (ifPossible(x+1, y, t_n, road[x+1][y], freq[x+1][y], N)) {
      q.push(make_pair(t_n, (x+1)*MAXNODE+y));
    }
  }
  return -1;
}

int main() {
  int N;
  int road[MAXNODE][MAXNODE];
  int freq[MAXNODE][MAXNODE];
  int caseNum = 0;
  while (scanf("%d", &N) == 1) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        char y;
        scanf(" %c", &y);
        if (y == '.') {
          road[i][j] = 1;
        } else {
          road[i][j] = 0;
        }
      }
      getchar();
    }
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        char x;
        scanf(" %c", &x);
        freq[i][j] =  x - '0';
      }
      getchar();
    }

    if (caseNum != 0) {
      printf("\n");
    }
    caseNum ++;
    int t = BFS(make_pair(0,0), road, freq, N);
    if (t == -1) {
      printf("NO\n");
    } else {
      printf("%d\n", t);
    }
    getchar();
  }
}
