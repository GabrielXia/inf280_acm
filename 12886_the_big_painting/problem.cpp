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
#include <cstdint>
#include <set>
#include <queue>
#include <cstring>
#define MAXLEN 2000

using namespace std;

int hp, wp, hm, wm;
char pattern[MAXLEN][MAXLEN], master[MAXLEN*MAXLEN];
int trie[MAXLEN*MAXLEN+2][2];
int fs; // next free index in the trie
int endw[MAXLEN*MAXLEN+2]; // index of the end words in the trie
long long ns;


// i index of the word
// s content
// n index of the node in the trie
void insert_trie(int i, char *s, int n) {
  unsigned char x = s[0];
  if (!x) { endw[n] = i; return; }
  if (x == 'x') {
    x = 0;
  } else if (x == 'o'){
    x = 1;
  }
  if (!trie[n][x]) // si pas d'arête étiquetée x depuis n...
    trie[n][x] = fs++; // ... on crée un nouveau nœud cible
  return insert_trie(i, s+1, trie[n][x]);
}

void aho_corasick() {
    memset(trie, 0 ,sizeof(trie));
    memset(endw, 0, sizeof(endw));
    fs = 2;
    for (int i = 1; i <= hp; i++) {
      insert_trie(i, pattern[i-1], 1);
    }

    // build the pointers
    int pointer[MAXLEN*MAXLEN +2];
    int shortcut[MAXLEN*MAXLEN +2];
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
      int n = q.front();
      q.pop();
      //TODO
      for(unsigned char x=0; x < 2; x++) {
        int n2 = trie[n][x];
        if (!n2) {
          continue;
        }

        // pointer
        int p = pointer[n];
        while (p && !trie[p][x]) {
          p = pointer[p];
        }
        if (!p) {
          pointer[n2] = 1;
        } else {
          pointer[n2] = trie[p][x];
        }

        // raccourci
        if (endw[pointer[n2]]) {
          shortcut[n2] = pointer[n2];
        } else {
          shortcut[n2] = shortcut[pointer[n2]];
        }
        q.push(n2);
      }
    }

    // search
    int pos = 1;
    array<set<long long>, MAXLEN> results;
    for (long long i = 0; i < ns; i++) {
      unsigned char x = master[i];
      if (x == 'x') {
        x = 0;
      } else if (x == 'o'){
        x = 1;
      }

      while (pos && !trie[pos][x]) {
        pos = pointer[pos];
      }
      pos = trie[pos][x];
      if (!pos) {
        pos = 1;
      }

      int posb = pos;
      do {
        if(endw[posb]) {
          if (posb%wm < wm - wp)
          printf("match of %s at %d\n", pattern[endw[posb]-1], i - strlen(pattern[endw[posb]-1])+1);
        }
        posb = shortcut[posb];
      } while (endw[posb]);
    }
}

int main() {
  while (scanf("%d %d %d %d", &hp, &wp, &hm, &wm) == 4) {
    int indexY = 0;
    for(int i = 0; i < hp; i++) {
      int indexX = 0;
      for (int j = 0; j < wp; j++) {
        scanf(" %c", &pattern[indexY][indexX++]);
      }
      indexY++;
    }
    long long index = 0;
    for (long long i= 0; i < hm * wm; i ++) {
      scanf(" %c", &master[index++]);
    }
    ns = index;

    // Aho Corasick
    aho_corasick();
  }
}
