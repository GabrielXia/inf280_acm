#include <stdio.h>
#include <list>
#include <algorithm>
#include <iostream>
#include <string>
#include <memory.h>
#include <cstdlib>
#include <climits>

using namespace std;

int main() {
  int caseNum = 0;
  scanf("%d", &caseNum);

  int table[100000];
  int history[300000];
  for (int i = 0; i < caseNum; i++) {
    getchar();
    int c, n;
    scanf("%d", &c);
    scanf("%d", &n);
    scanf("%d %d %d", &history[0], &history[1], &history[2]);
    table[0] = 2 * (history[0] + history[1]);
    for (int j = 1; j < n; j++) {
        scanf("%d %d %d", &history[j*3], &history[j*3+1], &history[j*3+2]);

        table[j] = table[j-1] + 2 * (history[j*3] + history[j*3+1]);
        int last = j-1;
        int weight = history[j*3+2] + history[j*3-1];
        while (weight <= c && last >= 0) {
          int new_pass = history[last*3] + history[last*3+1];
          for (int k = last; k < j; k++) {
            new_pass += (abs(history[k*3+3] - history[k*3]) + abs(history[k*3+4] - history[k*3+1]));
          }
          new_pass += (history[j*3] + history[j*3+1]);

          if (last == 0) {
            table[j] = min(table[j], new_pass);
          } else {
            table[j] = min(table[j], table[last-1] + new_pass);
          }

          // update
          last--;
          weight += history[last*3+2];
        }
    }

    printf("%d\n", table[n-1]);
    if (caseNum > i +1) {
      printf("\n");
    }
  }
}
