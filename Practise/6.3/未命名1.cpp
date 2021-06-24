#include <bits/stdc++.h>
using namespace std;

int k;

int calc(int cir, int x, int y) {
    if ((y + 1) % cir == x) 
        return k;
    return k - 1;
}

int val[N];

void push(int cir, int x) {
    sum += k - 1, val[(x - 1 + cir) % cir]++; 
}

int val1[N][N];

void push(int cir, int x, int y) {
    
}

int calc(int cir, int x, int y, int z, int w) {
    if (x == y) {
        if ((max(z, w) + 1) % cir == x) 
            return k * (k + 1) / 2 - 1;
        else return k * (k - 1) / 2 - 1;
    } else {
        if (x < y) {
            if ((w + 1) % cir == y || (z + 1) % cir == x || 
                (z >= y - 1 && (w >= x - 1 || (w == cir - 1 && x == 0))))
                    
        }
        
         
    }
}


