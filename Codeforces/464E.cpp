#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

struct node {
    int ct, ls, rs;
} T[N << 2];

int ncnt;

int build(int l, int r) {
    int rt = ++ncnt; T[rt].ct = T[rt].ls = T[rt].rs = 0;
    if (l == r) return rt;
    int mid = (l + r) >> 1;

}
// 没意思，不写了