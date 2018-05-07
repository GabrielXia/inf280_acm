#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main(void) {
  int nx = 0;
  while(scanf("%d", &nx) == 1) {
    int ny = 0;
    float w = 0;
    scanf("%d", &ny);
    scanf("%f", &w);

    vector<float> length = {};
    vector<float> wide = {};

    int i = 0;
    float value = 0;
    for(i=0; i < nx; i++){
      scanf("%f", &value);
      length.push_back(value);
    }
    for(i=0; i < ny; i++){
      scanf("%f", &value);
      wide.push_back(value);
    }

    // tri
    sort(length.begin(), length.end());
    sort(wide.begin(), wide.end());

    string answer("YES");

    // end
    if (nx == 0 && ny == 0 && w==0.0) {
      break;
    }

    for(i=0; i < nx; i++){
      if (i == 0) {
        if(length[i] - w/2 > 0 || length[1] - length[0] > w) {
          answer = "NO";
          break;
        }
      } else if ( i == nx -1) {
        if (length[i] + w/2 < 75) {
          answer = "NO";
          break;
        }
      } else {
        if (length[i + 1] - length[i] > w) {
          answer = "NO";
          break;
        }
      }
    }

    for(i=0; i < ny; i++){
      if (i == 0) {
        if(wide[i] - w/2 > 0 || wide[1] - wide[0] > w) {
          answer = "NO";
          break;
        }
      } else if ( i == ny -1) {
        if (wide[i] + w/2 < 100) {
          answer = "NO";
          break;
        }
      } else {
        if (wide[i + 1] - wide[i] > w) {
          answer = "NO";
          break;
        }
      }
    }

    std::cout << answer << '\n';
    //std::cout << length[0] << '\n';
  }
}
