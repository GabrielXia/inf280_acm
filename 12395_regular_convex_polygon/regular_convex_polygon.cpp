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
#define EPS 0.000001
#define PI 3.14159265359

using namespace std;

// can be copied for the test
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
};

void getAngles(point p1, point p2, point p3, double *angles) {
  double ang[3];
  double xx = p1.distance2To(p2);
  double yy = p1.distance2To(p3);
  double zz = p2.distance2To(p3);
  double x = sqrt(xx);
  double y = sqrt(yy);
  double z = sqrt(zz);
  ang[0] = acos((xx + yy - zz) / (2*x*y));
  ang[1] = acos((xx + zz -yy) / (2*x*z));
  ang[2] = acos((yy + zz - xx) /(2*y*z));
  for(int i = 0; i < 3; i++) {
    if(ang[i] > PI / 2) {
      angles[i] = 2 * PI - 2 * ang[i];
    } else {
      angles[i] = 2 * ang[i];
    }
  }
}

bool divied(double d1, double d2) {
  //printf("%lf %lf %lf\n", d1, d2, remainder(d1 ,d2));
  return fabs(remainder(d1 ,d2)) < EPS * d2;
}

int main() {
  double x, y;
  point p1, p2, p3;
  while (scanf("%lf %lf", &x, &y) == 2) {
    p1 = point(x, y);
    scanf("%lf %lf", &x, &y);
    p2 = point(x ,y);
    scanf("%lf %lf", &x, &y);
    p3 = point(x ,y);
    double angles[3];

    getAngles(p1, p2, p3, angles);

    double angle;
    for(int i = 3; i <= 1000; i++) {
      angle = 2 * PI / i;
      if (divied(angles[0], angle) && divied(angles[1], angle) && divied(angles[2], angle)) {
        printf("%d\n", i);
        break;
      }
    }
  }
}
