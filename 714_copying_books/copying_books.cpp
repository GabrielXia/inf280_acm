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

// greedy
bool ifPossible(long* books, int m, long* people, int k, long long threshold) {
  long long sum = 0;
  int kieme = 0;
  for (int i = m-1; i >=0; i--) {
    sum+= books[i];
    if (sum > threshold) {
      return false;
    } else if (sum == threshold) {
      people[kieme] = i;
      kieme++;
      if (kieme == k  && i != 0) {
        return false;
      }
      sum = 0;
    } else if (i > 0 && sum + books[i-1] > threshold) {
       people[kieme] = i;
       kieme ++;
       if (kieme == k  && i != 0) {
         return false;
       }
       sum = 0;
   } else if (i == 0) {
     people[kieme] = 0;
   }
  }
  return true;
}

// binary search
int main() {
  int caseNum;
  scanf("%d", &caseNum);
  for (int i = 0; i < caseNum; i++) {
    int m,k;
    scanf("%d %d", &m, &k);
    long books[500];
    long people[500];
    long long sum = 0;
    for (int j = 0; j < m; j++) {
      scanf("%ld", &books[j]);
      sum += books[j];
    }

    long long s = 0;
    long long e = sum;
    long long mid;
    while (e - s > 1) {
      mid = (s+e)/2;
      bool result = ifPossible(books, m, people, k, mid);
      if (result) {
        e = mid;
      } else {
        s = mid;
      }
    }
    bool result = ifPossible(books, m, people, k, e);
    mid = result ? e : s;

    int index = 0;
    for (int j = 0; j < m; j++) {
      if (j == m -1) {
        printf("%ld\n", books[j]);
      } else {
        printf("%ld ", books[j]);
      }
      if (index < k - 1) {
        if(ifPossible(books+j+1, m - j - 1, people, k- index -1, mid)) {
          printf("/ ");
          index ++;
        }
      }
    }
  }
}
