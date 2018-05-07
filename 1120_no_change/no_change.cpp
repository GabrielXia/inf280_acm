#include <stdio.h>
#include <list>
#include <algorithm>
#include <iostream>
#include <string>
#include <memory.h>

using namespace std;

int main() {

  int caseNum = 0;
  scanf("%d", &caseNum);
  int table[100000];
  for (int i = 0; i < caseNum; i++) {
    getchar();
    int x = 0;
    int num = 0;
    int v[5];
    scanf("%d %d", &x, &num);
    for (int j = 0; j < num; j++) {
      scanf("%d", &v[j]);
    }

    // remove order constraint
    for (int j = 1; j < num; j++) {
      v[j] += v[j-1];
    }

    memset(table, 0, sizeof(int)* x);
    for (int j = 0; j < num; j++) {
      table[v[j]-1] = 1;
    }

    for (int k = v[0]; k < x ; k++) {
      for (int j = 0; j < num; j++) {
        if (k - v[j] >= 0) {
          table[k] |= table[k - v[j]];
        }
      }
    }

    if (table[x-1] == 1) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }

    if (caseNum > i +1) {
      printf("\n");
    }
  }
  return 0;
}
