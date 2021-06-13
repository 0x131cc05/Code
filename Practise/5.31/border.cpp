#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

int sa[N], x[N], y[N], c[N], m = 127, n;

void sort() {
    fill(c, c + m + 1, 0);
    for (int i = 1; i <= n; i++) c[x[i]]++;
    for (int i = 1; i <= m; i++) c[i] += c[i - 1];
    for (int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i]; 
}

char s[N];

vector<int> pos[20];

int layer;

void store() {

}

void build() {
    for (int i = 1; i <= n; i++) x[i] = s[i], y[i] = i;
    sort();
    for (int k = 1; k <= n; k <<= 1) {

    }
}