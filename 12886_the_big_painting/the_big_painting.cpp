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
#include <map>
#define MAXLEN 2000

using namespace std;

int hp, wp, hm, wm;
char pattern[MAXLEN][MAXLEN], master[MAXLEN*MAXLEN], uniquePattern[MAXLEN][MAXLEN];
int afterLS[MAXLEN*MAXLEN];
int trie[MAXLEN*MAXLEN+2][2];
int fs = 0; // next free index in the trie
int endw[MAXLEN*MAXLEN+2]; // index of the end words in the trie
long long ns;
int pointer[MAXLEN*MAXLEN +2];
int shortcut[MAXLEN*MAXLEN +2];
int mapIndex = 0;
int p[MAXLEN];
int T[MAXLEN+1];
int vertical[MAXLEN*MAXLEN];

map<string, int> word2Index;

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

void build1() {
    memset(trie, 0 ,sizeof(trie[0][0])* (2 + wp * hp) * 2);
    memset(endw, 0, sizeof(endw[0])* (2 + wp * hp));
    memset(pointer, 0, sizeof(pointer[0])* (2 + wp * hp));
    memset(shortcut, 0, sizeof(shortcut[0]) * (2 + wp * hp));
    fs = 2;
    for (int i = 1; i <= mapIndex; i++) {
        insert_trie(i, uniquePattern[i-1], 1);
    }
}

void build2() {
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
}

void search() {
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
                long long startPos = i - strlen(uniquePattern[endw[posb]-1])+1;
                if (startPos % wm <= wm - wp) {
                    afterLS[startPos] = endw[posb];
                }
            }
            posb = shortcut[posb];
        } while (endw[posb]);
    }
}

int main() {
    while (scanf("%d %d %d %d", &hp, &wp, &hm, &wm) == 4) {
        word2Index.clear();
        mapIndex = 0;
        memset(pattern, 0, sizeof(pattern[0][0])*hp*MAXLEN);
        memset(master, 0, sizeof(master[0])*hm*wm);
        memset(afterLS, 0, sizeof(afterLS[0])*hm*wm);
        memset(uniquePattern, 0, sizeof(uniquePattern[0][0])*hp*MAXLEN);
        for(int i = 0; i < hp; i++) {
            int indexX = 0;
            for (int j = 0; j < wp; j++) {
                scanf(" %c", &pattern[i][indexX++]);
            }
            if(word2Index.find(pattern[i])==word2Index.end()) {
                word2Index.insert( pair<string, int>(pattern[i], mapIndex));
                for (int k=0; k < wp; k++) {
                    uniquePattern[mapIndex][k] = pattern[i][k];
                }
                mapIndex++;
            }
        }
        long long index = 0;
        for (long long i= 0; i < hm * wm; i ++) {
            scanf(" %c", &master[index++]);
        }
        ns = index;

        // Aho Corasick
        build1();
        build2();
        search();

        // use kmp to find the unique pattern vertically
        for (int x = 0; x < wm; x ++) {
          for (int y = 0; y < hm; y++) {
            vertical[x* hm + y] = afterLS[y * wm + x];
          }
        }
        int np = hp;
        for (int i = 0; i < np; i++) {
          p[i] = word2Index.find(pattern[i])->second +1;
        }
        T[0] = -1;
        int cnd = 0;
        for (int i = 1; i <= np; i++) {
          T[i] = cnd;
          while (cnd >= 0 && p[cnd] != p[i])
            cnd = T[cnd];
          cnd++;
        }
        int res = 0;
        cnd = 0;
        for (long long i = 0; i <= hm * wm; i++) {
          while (cnd >= 0 && p[cnd] != vertical[i])
            cnd = T[cnd];
          cnd++;
          if (cnd == np) {
              if((i-np+1) % hm <= hm - hp) {
              res ++;
              cnd = T[cnd];
            }
          }
        }
        printf("%d\n", res);
    }
}
