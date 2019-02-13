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
#include <bitset>

using namespace std;

unsigned long long table[55];

unsigned long long countOneUntil(unsigned long long n) {
    unsigned long long res = 0;
    unsigned count1 = 0;
    for (int i = 54; i >= 0; i--) {
        if (n&(((unsigned long long)1)<<i)) {
            res += table[i];
            res += (unsigned long long)1;
            res += count1 * ((unsigned long long)pow(2, i));
            count1++;
        }
    }
    return res;
}


int main() {
    unsigned long long a, b;
    table[0] = 0;
    table[1] = 1;
    for (int i = 2; i < 55; i++) {
        table[i] = 2 * table[i-1] + pow(2, i-1);
    }
    while (scanf("%llu %llu", &a, &b) == 2) {
        unsigned long long big = countOneUntil(b);
        unsigned long long small = countOneUntil(a-1);
        printf("%llu\n", big-small);
    }
}
