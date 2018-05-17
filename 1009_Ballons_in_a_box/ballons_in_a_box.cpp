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

class Ball{
public:
    int x;
    int y;
    int z;
    double r;
    Ball(int, int, int);
    double distanceTo(Ball);
    double minRTo(Ball);
    void setR(double);
    double minRToBox(int, int, int, int, int, int);
};

Ball::Ball(int xx, int yy, int zz) {
    x = xx;
    y = yy;
    z = zz;
}

double Ball::distanceTo(Ball a) {
    return sqrt(pow((x - a.x),2) + pow((y - a.y), 2) + pow((z-a.z), 2));
}

double Ball::minRTo(Ball a) {
    double distance = distanceTo(a);
    if (distance <= a.r) {
        return 0;
    } else {
        return distance - a.r;
    }
}

void Ball::setR(double rr) {
    r = rr;
}

double Ball::minRToBox(int sx, int sy, int sz, int ex, int ey, int ez) {
    if ((x-sx)*(x-ex) >= 0 || (y-sy)*(y-ey) >=0 || (z-sz) * (z-ez) >=0) {
        return 0;
    } else {
        return min({abs(x-sx), abs(x-ex), abs(y-sy), abs(y-ey), abs(z-sz), abs(z-ez)});
    }
}

// bruteforce
int main() {
    const double  PI= acos(-1.0);
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

        int s[6];
        for (int i = 0; i < point; i++) {
            scanf("%d %d %d", &pos[3*i], &pos[3*i+1], &pos[3*i+2]);
            s[i] = i;
        }
        std::vector<Ball> v;
        double vMax = 0;
        do {
            v.clear();
            for (int i = 0; i < point; i++) {
                Ball b(pos[3*s[i]], pos[3*s[i]+1], pos[3*s[i]+2]);
                double r = b.minRToBox(sx, sy, sz, ex, ey, ez);
                if(r != 0) {
                    for (auto it = v.cbegin(); it != v.cend(); it++) {
                        r = min(r, b.minRTo(*it));
                        if(r == 0) break;
                    }
                }

                if(r > 0) {
                    b.setR(r);
                    v.push_back(b);
                }
            }

            double volume = 0;
            for (auto it = v.cbegin(); it != v.cend(); it++) {
                volume+= PI * 4. / 3 * pow(((*it).r), 3);
            }
            vMax = max(volume, vMax);
        } while (next_permutation(s, s+ point));

        int result = round(abs(ex-sx) * abs(ey-sy) * abs(ez-sz) - vMax);
        printf("Box %d: %d\n\n", index, result);
    }
}
