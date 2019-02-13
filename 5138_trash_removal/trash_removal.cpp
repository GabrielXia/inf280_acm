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
#define MAX 100
#define MAXDIST 200000000
#define EPS 0.0000001

using namespace std;

int startX = 0;
int startY = 0;

struct point {
    double x, y;
    point() {
        x=0.0; y=0.0;
    }
    point(double in_x, double in_y): x(in_x), y(in_y) {}
    bool operator == (point pt2) const {
        return (fabs(x - pt2.x) < EPS
                && (fabs(y - pt2.y) < EPS));
    }

    double distance2To(point pt2) {
        return pow((x-pt2.x), 2) + pow((y-pt2.y), 2);
    }

    double norm2() {
        return x*x + y *y;
    }

    double productScale(point p2) {
        return x * p2.x + y * p2.y;
    }

    point getDirection(point p2) {
        return point(p2.x - x, p2.y -y);
    }

    int crossProduct(point p2) {
        return x * p2.y - p2.x * y;
    }

    double distance2To(point p2, point p3) {
        point p2p1 = p2.getDirection(*this);
        point p2p3 = p2.getDirection(p3);
        point p1p3 = getDirection(p3);
        if (p2p3.productScale(p2p1) >= 0 && p1p3.productScale(p2p3) >=0) {
            return ((double)pow(p1p3.crossProduct(p2p3), 2)) / p2p3.norm2();
        } else {
            //return min(p2p1.norm2(), p1p3.norm2());
            return ((double)pow(p1p3.crossProduct(p2p3), 2)) / p2p3.norm2();
        }
    }

    bool operator < (point m)const {
        if(x == startX) return false;
        if(m.x == startX) return true;
        return ((double) y - startY) / ((double) x - startX) < ((double) m.y - startY) / ((double) m.x - startX);
    }
};

// positive if turn to left
int turnDirection(point p1, point p2, point p3) {
    point p1p2 = p1.getDirection(p2);
    point p2p3 = p2.getDirection(p3);
    return p1p2.crossProduct(p2p3);
}

int main() {
    int N, x, y;
    int caseNum = 0;
    while (scanf("%d", &N) == 1) {
        if (N == 0) {
            break;
        }
        list<point> points;
        int minLeftX = 10001, minLeftY = 10001, leftIndex;

        for (int i = 0; i < N; i++) {
            scanf("%d %d", &x, &y);
            points.push_back(point(x, y));
            if (x == minLeftX) {
              if (y < minLeftY) {
                leftIndex = i;
                minLeftX = x;
                minLeftY = y;
              }
            } else if (x < minLeftX) {
              leftIndex = i;
              minLeftX = x;
              minLeftY = y;
            }
        }

        // Graham
        auto iter = points.begin();
        advance(iter, leftIndex);
        startX = iter->x;
        startY = iter->y;
        points.erase(iter);

        points.sort();

        list<point> enveloppe;
        enveloppe.push_back(point(startX, startY));
        enveloppe.push_back(*(points.begin()));
        for (auto iter = ++points.begin(); iter != points.end(); iter++) {
            point mi = *iter;
            point p1 = enveloppe.back();
            auto iter2 = enveloppe.end();
            advance(iter2, -2);
            point p2 = *iter2;
            while(enveloppe.size() >=2 && turnDirection(p2, p1, mi) < 0) {
                enveloppe.pop_back();
                p1 = enveloppe.back();
                auto iter2 = enveloppe.end();
                advance(iter2, -2);
                p2 = *iter2;
            }
            enveloppe.push_back(mi);
        }

        double minDis = MAXDIST;
        for (auto iter2 = enveloppe.begin(); iter2 != enveloppe.end(); iter2++) {
          double maxDis = 0;
          point p2 = *iter2;
          point p3;
          auto iter3 = iter2;
          advance(iter3, 1);
          if (iter3 == enveloppe.end()) {
              p3 = enveloppe.front();
          } else {
              p3 = *iter3;
          }
          for (auto p1 : enveloppe) {
            if (p1 == p2 || p1 == p3) {
              continue;
            }
            double distance = p1.distance2To(p2, p3);
            if (distance > maxDis) {
                maxDis = distance;
            }
          }
          if(maxDis < minDis) minDis = maxDis;
        }
        printf("Case %d: %.2f\n", ++caseNum, sqrt(minDis));
    }
}
