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
#include <iterator>
#include <set>
#define EPS 0.000000001
#define NUMMAX 100000

using namespace std;

int startX = 0;
int startY = 0;

struct point {
    double x, y;
    double k;
    point() {
        x=0.0; y=0.0;
    }
    point(double in_x, double in_y) {
      x = in_x;
      y = in_y;
      k = this -> getK();
    }

    bool operator == (point pt2) const {
        return (fabs(x - pt2.x) < EPS
                && (fabs(y - pt2.y) < EPS));
    }

    double getK() const {
        if (fabs(x - startX) < EPS) {
            return -2000;
        } else {
            return ((double) y - startY) / ((double) x -startX);
        }
    }

    bool operator < (point p2) const {
        // if (fabs(x - startX) < EPS && fabs(p2.x - startX) < EPS) {
        //     return false;
        // } else if(fabs(x - startX) < EPS) {
        //     return true;
        // } else if(fabs(p2.x - startX) < EPS) {
        //     return false;
        // } else {
        //     double k1 = ((double) y - startY) / ((double) x -startX);
        //     double k2 = ((double) p2.y - startY) / ((double) p2.x -startX);
        //     return k1 < k2;
        // }
        return this -> k < p2.k;
    }
};

// strict < target
long long findStrictSmall(vector<point> v, long long start, long long end, double target) {
    if (v.size() == 0 || end - start < 0) return 0;
    if (v.at(end).k < target) return v.size();
    long long s = start;
    long long e = end;
    while (e - s > 1) {
        long long m = (e + s) / 2;
        double k = v.at(m).k;
        if (k < target) {
            s = m;
        } else{
            e = m;
        }
    }
    double k = v.at(s).k;
    if (fabs(k - target) < EPS) {
        return s;
    } else return s + 1;
}

long long findStrictBig(vector<point> v, long long start, long long end, double target) {
    if (v.size() == 0 || end - start < 0) return 0;
    if (v.at(start).k > target) return v.size();
    long long s = start;
    long long e = end;
    while (e - s > 1) {
        long long m = (e + s) / 2;
        double k = v.at(m).k;
        if (k <= target) {
            s = m;
        } else{
            e = m;
        }
    }
    double k = v.at(e).k;
    if (fabs(k - target) < EPS) {
        return end - start - e;
    } else return end - start + 1 - e;
}

int main() {
    long long N;
    while (scanf("%lld", &N) == 1) {
        int x, y;
        scanf("%d %d", &startX, &startY);
        if (N == 1) {
            printf("1 1\n");
            continue;
        }
        vector<point> upRight;
        vector<point> upLeft;
        vector<point> downRight;
        vector<point> downLeft;
        vector<point> theSame;
        set<double> uniqueK;
        for (long long i = 1; i < N; i++) {
            scanf("%d %d", &x, &y);
            if(x == startX && y == startY) {
                theSame.push_back(point(x, y));
            } else if (x > startX && y > startY) {
                upRight.push_back(point(x, y));
            } else if(x <= startX && y>= startY) {
                point pp(x, y);
                uniqueK.insert(pp.k);
                upLeft.push_back(pp);
            } else if (x >= startX && y<= startY) {
                point pp(x, y);
                uniqueK.insert(pp.k);
                downRight.push_back(pp);
            } else {
                downLeft.push_back(point(x, y));
            }
        }
        sort(upLeft.begin(), upLeft.end());
        sort(downRight.begin(), downRight.end());

        long long best = upRight.size() + upLeft.size() + downRight.size();
        long long worst = upRight.size() + theSame.size();
        long long index4 = 0;
        long long index2 = 0;
        long long count = 0;
        long long bigger4;
        long long smaller2;
        if (downRight.size() == 0) {
          best = upRight.size();
        } else {
          while (index4 < downRight.size()) {
            while (index4 < downRight.size()-1 && fabs(downRight.at(index4).k - downRight.at(index4+1).k) < EPS) {
              index4 ++;
            }
            bigger4 = downRight.size() -1 - index4;
            while (index2 < upLeft.size() && upLeft.at(index2).k < downRight.at(index4).k - EPS) {
              index2 ++;
            }
            smaller2 = index2;
            if(upRight.size() + bigger4 + smaller2 < best) best = upRight.size() + bigger4 + smaller2;
            index4++;
          }
        }

        index2 = 0;
        index4 = 0;
        long long bigger2;
        long long smaller4;
        if (upLeft.size() == 0) {
          worst = N - downLeft.size();
        } else {
          while (index2 < upLeft.size()) {
            while (index2 < upLeft.size()-1 && fabs(upLeft.at(index2).k - upLeft.at(index2+1).k) < EPS) {
              index2 ++;
            }
            bigger2 = upLeft.size() -1 -index2;
            while (index4 < downRight.size() && downRight.at(index4).k < upLeft.at(index2).k - EPS) {
              index4 ++;
            }
            smaller4 = index4;
            if (N - (downLeft.size() + bigger2 + smaller4) > worst) {
              worst = N - (downLeft.size() + bigger2 + smaller4);
            }
            index2 ++;
          }
        }
        printf("%lld %lld\n", best + 1, worst );
    }
}
