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
#include <cstring>

#define MAXLEN 1000000

using namespace std;

char str[MAXLEN];
unsigned long r0[MAXLEN], r1[MAXLEN], r2[MAXLEN];

int charToInt(char c) {
  int x = c - '0';
  if (x >= 0 && x<=9) {
    return x;
  } else {
    return -1;
  }
}

int main() {
  while (scanf("%s", str) != EOF) {
      unsigned long len = strlen(str);
      memset(r0, 0, sizeof(r0[0]) * len);
      memset(r1, 0, sizeof(r1[0]) * len);
      memset(r2, 0, sizeof(r2[0]) * len);
      int first = charToInt(str[0]);
      switch (first % 3) {
        case 0: r0[0] = 1; break;
        case 1: r1[0] = 1; break;
        case 2: r2[0] = 1; break;
      }
      for (unsigned long i = 1; i < len; i++) {
        int num = charToInt(str[i]);
        if (num == -1) {
          r0[i] = 0;
          r1[i] = 0;
          r2[i] = 0;
        } else {
          switch (num % 3) {
            case 0:
              r0[i] = r0[i-1] + 1;
              r1[i] = r1[i-1];
              r2[i] = r2[i-1];
              break;
            case 1:
              r0[i] = r2[i-1];
              r1[i] = r0[i-1] + 1;
              r2[i] = r1[i-1];
              break;
            case 2:
              r0[i] = r1[i-1];
              r1[i] = r2[i-1];
              r2[i] = r0[i-1] + 1;
              break;
          }
        }
      }

      unsigned long sum = 0;
      for (unsigned long i = 0; i < len; i++) {
        sum += r0[i];
      }
      printf("%ld\n", sum);
  }
}
