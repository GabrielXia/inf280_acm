#include <stdio.h>
#include <list>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

bool contains(list<int> l, int element) {
  auto result = find(begin(l), end(l), element);
  if (result != end(l)) {
    return true;
  } else {
    return false;
  }
}

// devide long list to pre list, post list.
// we do not store all numbers in the list
int main(void) {
  int p = 0;
  int count = 0;
  while(scanf("%d", &p) == 1) {

    int c = 0;
    scanf("%d", &c);

    if (p == 0 && c ==0) {
      break;
    }

    list<int> pre = {};
    list<int> post = {};
    int number = 1;

    printf("Case %d:\n", ++count);

    char command;
    int index = 0;
    for (size_t j = 0; j < c; j++) {
      scanf(" %c", &command);
      if (command == 'N') {
        if(pre.size() == 0) {
          if (number > p) {
            int front = post.front();
            printf("%d\n", front);
            post.pop_front();
            post.push_back(front);
          } else {
            while (contains(post, number)) {
              number ++;
            }
            if (number > p) {
              int front = post.front();
              printf("%d\n", front);
              post.pop_front();
              post.push_back(front);
            } else {
              printf("%d\n", number);
              post.push_back(number);
              number ++;
            }
          }
        } else {
          int front = pre.front();
          printf("%d\n", front);
          pre.pop_front();
          post.push_back(front);
        }
      } else if (command == 'E') {
        getchar();
        scanf("%d", &index);

        // move it to the front
        if (contains(pre, index)) {
          pre.remove(index);
          pre.push_front(index);
        } else if(contains(post, index)) {
          post.remove(index);
          pre.push_front(index);
        } else {
          pre.push_front(index);
        }
      }
      //change line
      getchar();
    }
  }
}
