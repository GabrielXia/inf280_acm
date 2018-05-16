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


using namespace std;

// bruteforce
int main() {
  const float  PI=3.14159265358979f;
  int point, sx, sy, sz, ex, ey, ez;
  int pos[18];
  int index = 0;
  while(scanf("%d", &point) == 1) {
    if (point == 0) {
      break;
    }
    index ++;
    scanf("%d %d %d", &sx, &sy, &sz);
    scanf("%d %d %d", &ex, &ey, &ez);

    int[6] s;
    for (int i = 0; i < point; i++) {
      scanf("%d %d %d", &pos[3*i], &pos[3*i+1], &pos[3*i+2]);
      s[i] = i;
    }

    std::vector<Ball> v;
    float vMax = 0;
    do {
      for (int i = 0; i < point; i++) {
        Ball b(pos[3*i], pos[3*i+1], pos[3*i+2]);
        float r = b.minRToBox(sx, sy, sz, ex, ey, ez);
        if(r != 0) {
          for (auto it = v.cbegin(); it != v.cend(); it++) {
            r = min(r, minRTo(*it));
            if(r == 0) break;
          }
        }

        if(r > 0) {
          b.setR(r);
          v.push_back(b);
        }
      }

      float v = 0;
      for (auto it = v.cbegin(); it != v.cend(); it++) {
        v+= PI * 4 / 3 * pow(((*it).r), 3);
      }
      vMax = max(v, vMax);
    } while (next_permutation(s, s+ point);

   int result = round(abs(ex-sx) * abs(ey-sy) * abs(ez-sz) - vMax);
   printf("Box %d: %d\n", index, result);
  }
}

class Ball{
  int x;
  int y;
  int z;
  int r;
public:
  Ball(int, int, int);
  float distanceTo(Ball);
  float minRTo(Ball);
  void setR(float);
  float minRToBox(int, int, int, int, int, int);
}

Ball::Ball(int xx, int yy, int zz) {
  x = xx;
  y = yy;
  z = zz;
}

float Ball::distanceTo(Ball a) {
  return sqrt(pow((x - a.x),2) + pow((y - a.y), 2) + pow((z-a.z), 2));
}

float Ball::minRTo(Ball a) {
  float distance = distanceTo(a);
  if (distance <= a.r) {
    return 0;
  } else {
    return distance - a.r;
  }
}

void Ball::setR(float rr) {
  r = rr;
}

float Ball::minRToBox(int sx, int sy, int sz, int ex, int ey, int ez) {
  if ((x-sx)*(x-ex) >= 0 || (y-sy)*(y-ey) >=0 || (z-sz) * (z-ez) >=0) {
    return 0;
  } else {
    return min(abs(x-sx), abs(x-ex), abs(y-sy), abs(y-ey), abs(z-sz), abs(z-ez));
  }
}
