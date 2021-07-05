#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

struct tree {
    int ch[2][N], sz[N], c[N], ncnt, rt; double key[N];

    void clr() {
        ncnt = 0, rt = 0, c[0] = key[0] = -1;
    }
    
    void pushup(int rt) { 
        sz[rt] = sz[ch[0][rt]] + sz[ch[1][rt]] + 1; 
    }

    bool fuck(int rt) { 
        return sz[ch[0][rt]] > 0.7 * sz[rt] || sz[ch[1][rt]] > 0.7 * sz[rt]; 
    }

    int p[N], tot;
    void getNode(int rt) {
        if (!rt) return;
        getNode(ch[0][rt]), p[++tot] = rt, getNode(ch[1][rt]);
    }

    int get(int pos) {
        return c[ncnt - pos + 1];
    }

    void rebuild(int &rt, int l, int r, double valL, double valR) {
        if (l > r) return rt = 0, void();
        int mid = (l + r) >> 1; double val = (valL + valR) / 2;
        rt = p[mid], key[rt] = val;
        rebuild(ch[0][rt], l, mid - 1, valL, val);
        rebuild(ch[1][rt], mid + 1, r, val, valR);
        pushup(rt);
    }

    void check(int &rt, double valL, double valR) {
        if (!fuck(rt)) return;
        tot = 0, getNode(rt), rebuild(rt, 1, tot, valL, valR);
    }

    bool cmp(int x, int y) {
        if (c[x] != c[y]) return c[x] < c[y];
        return key[x - 1] < key[y - 1];
    }

    void insert(int &rt, int x, double valL, double valR) {
        if (!rt) {
            rt = x, sz[rt] = 1, key[rt] = (valL + valR) / 2;
            ch[0][rt] = ch[1][rt] = 0;
            return;
        }
        if (cmp(x, rt)) insert(ch[0][rt], x, valL, key[rt]);
        else insert(ch[1][rt], x, key[rt], valR);
        pushup(rt), check(rt, valL, valR);
    }

    void remove(int &rt, int x) {
        assert(rt);
        if (rt == x) {
            if (ch[0][rt] == 0 || ch[1][rt] == 0) rt = ch[0][rt] | ch[1][rt];
            else {
                int cur = ch[0][rt], lst = rt;
                while (ch[1][cur]) lst = cur, cur = ch[1][cur], sz[lst]--;
                if (lst == rt) ch[1][cur] = ch[1][rt];
                else ch[1][lst] = ch[0][cur], ch[0][cur] = ch[0][rt], ch[1][cur] = ch[1][rt];
                rt = cur, pushup(rt);
            }
            return;
        }
        if (cmp(x, rt)) remove(ch[0][rt], x);
        else remove(ch[1][rt], x);
        pushup(rt);
    }

    void pushFront(int t) {
        ncnt++, c[ncnt] = t, insert(rt, ncnt, 0, 1);
    }

    void popFront() {
        remove(rt, ncnt--);
    }

    int query(int rt, int str[], int n) {
        if (!rt) return 0;
        int res = 0;
        for (int i = 1; i <= n; i++) 
            if (c[rt - i + 1] != str[i]) 
                { res = c[rt - i + 1] < str[i]; break; }
         if (res) return sz[ch[0][rt]] + 1 + query(ch[1][rt], str, n);
         return query(ch[0][rt], str, n);
    }

    int query(int str[], int n) {
        int t = str[n + 1]; str[n + 1] = 1e9;
        int res = query(rt, str, n + 1) - query(rt, str, n);
        str[n + 1] = t;
        return res;
    }
};

int match(int A[], int n, int B[], int m) { // A in B; 1-base
    static int nxt[N * 2]; nxt[1] = 0;
    for (int i = 2; i <= n; i++) {
        int t = nxt[i - 1];
        while (t && A[t + 1] != A[i]) t = nxt[t];
        nxt[i] = t + (A[t + 1] == A[i]);
    }
    int res = 0; int lst = A[n + 1]; A[n + 1] = 1e9;
    for (int i = 1, cur = 0; i <= m; i++) {
        while (cur && A[cur + 1] != B[i]) cur = nxt[cur];
        cur += A[cur + 1] == B[i];
        if (cur == n) res++;
    }
    A[n + 1] = lst;
    return res;
}

struct tcurts {
    tree lft, rgt;

    int str[N * 2], L = N, R = N, M = N;

    void init(int s[], int n) {
        R = L + n - 1;
        for (int i = 1; i <= n; i++) str[i + L - 1] = s[i];
    }

    void build() {
        int mid = (L + R) >> 1;
        lft.clr(), rgt.clr(), M = mid;
        for (int i = mid; i >= L; i--) lft.pushFront(str[i]);
        for (int i = mid + 1; i <= R; i++) rgt.pushFront(str[i]);
    }

    void pushBack(int c) {
        rgt.pushFront(c), str[++R] = c;
    }

    void popBack() {
        if (R == M + 1) build();
        rgt.popFront(), R--;
    }

    void pushFront(int c) {
        lft.pushFront(c), str[--L] = c;
    }

    void popFront() {
        if (L == M) build();
        lft.popFront(), L++;
    }

    int query(int s[], int n) {
        static int tmp[N * 2]; int m = 0;
        for (int i = max(L, M - n + 2); i <= min(R, M + n - 1); i++) 
            tmp[++m] = str[i];
        int res = match(s, n, tmp, m);
        if (M - L + 1 >= n) res += lft.query(s, n);
        if (R - M >= n) {
            reverse(s + 1, s + n + 1);
            res += rgt.query(s, n);
            reverse(s + 1, s + n + 1);
        }
        return res;
    }

    int front() {
        return str[L];
    }

    int back() {
        return str[R];
    }
} pre, suf;

int tot;

void build(int s[], int n) {
    int mid = n / 2; tot = n;
    pre.init(s, mid), suf.init(s + mid, n - mid);
    pre.build(), suf.build(); 
}

void moveR() {
    suf.pushFront(pre.back()), pre.popBack();
}

void moveL() {
    pre.pushBack(suf.front()), suf.popFront();
}

void pushBack(int t) {
    suf.pushBack(t);
    if (tot & 1) moveL();
    tot++;
}

void pushFront(int t) {
    pre.pushFront(t);
    if (!(tot & 1)) moveR();
    tot++;
}

void popBack() {
    suf.popBack();
    if (!(tot & 1)) moveR();
    tot--;
}

void popFront() {
    pre.popFront();
    if (tot & 1) moveL();
    tot--;
}

void pushMid(int t) {
    if (tot & 1) pre.pushBack(t);
    else suf.pushFront(t);
    tot++;
}

void popMid() {
    suf.popFront();
    if (!(tot & 1)) moveR();
    tot--;
}

int query(int s[], int n) {
    int res = pre.query(s, n) + suf.query(s, n);
    static int tmp[N * 2]; int m = 0;
    for (int i = max(pre.L, pre.R - n + 2); i <= pre.R; i++) tmp[++m] = pre.str[i];
    for (int i = suf.L; i <= min(suf.R, suf.L + n - 2); i++) tmp[++m] = suf.str[i];
    res += match(s, n, tmp, m);
    return res;
}

char s[N * 10]; int hh[N];

int main() {
    scanf("%s", s + 1); int n = strlen(s + 1);
    for (int i = 1; i <= n; i++) hh[i] = s[i] - 'a';
    build(hh, n);
    int q; scanf("%d", &q);
    while (q--) {
        char op[20]; scanf("%s", op + 1);
        if (op[1] == 'Q') {
            scanf("%s", s + 1); int m = strlen(s + 1);
            if (m > tot) { puts("0"); continue; }
            for (int i = 1; i <= m; i++) hh[i] = s[i] - 'a';
            printf("%d\n", query(hh, m));
        } else {
            if (op[1] == 'I') {
                scanf("%s", s + 1); 
                int t = s[1] - 'a';
                if (op[8] == 'L') pushFront(t);
                else if (op[8] == 'R') pushBack(t);
                else pushMid(t);
            } else {
                if (op[8] == 'L') popFront();
                else if (op[8] == 'R') popBack();
                else popMid();
            }
        }
    }
}
