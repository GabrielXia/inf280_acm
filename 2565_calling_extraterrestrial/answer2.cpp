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

#define MAX 100001

using namespace std;

long long searchMax(vector<long long> v, long long startIndex, long long maxValue) {
    long long s = startIndex;
    long long e = v.size() -1;
    if(maxValue < v.at(s)) return 0;
    if(maxValue >= v.at(e)) return v.at(e);
    if(e == s) {
        if (v.at(s) <= maxValue) {
            return v.at(s);
        } else {
            return 0;
        }
    }
    while (e - s > 1) {
        long long m = (e + s) / 2;
        if (v.at(m) > maxValue) {
            e = m;
        } else if(v.at(m) < maxValue) {
            s = m;
        } else return maxValue;
    }
    if(v.at(e) == maxValue) return maxValue;
    return v.at(s);
}

int main() {
    long long m;
    long long a, b;
    bitset<MAX> P;
    vector<long long> premiers;
    P.set();
    P[0] = P[1] = 0;
    for (long long i = 0; i < MAX; i++) {
        if (P[i]) {
            for (long long j = i*i; j < MAX; j+=i) {
                P[j] = 0;
            }
            premiers.push_back(i);
        }
    }
    while (scanf("%lld %lld %lld", &m, &a, &b) == 3) {
        if (a == 0 && b == 0 && m == 0) break;
        long long pq = 0;
        long long pMax, qMax;
        long long size = premiers.size();
        for (long long i = 0; i < size; i++) {
            long long p = premiers.at(i);
            if(p * p > m) break;
            long long sup = min((b * p) / a, m / p) ;
            long long q = searchMax(premiers, i, sup);
            if(p*q > pq) {
                pMax = p;
                qMax = q;
                pq = p *q;
            }
        }
        printf("%lld %lld\n", pMax, qMax);
    }
}
