#include <iostream>
#include <algorithm>
using namespace std;
#define mid ((L[x] + R[x]) >> 1)
inline int read() {
    int x = 0, flag = 1;
    char ch = getchar();
    for( ; ch > '9' || ch < '0' ; ch = getchar()) if(ch == '-') flag = -1;
    for( ; ch >= '0' && ch <= '9' ; ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
    return x * flag;
}
typedef long long LL;
const int MAXN = 1e5 + 50;
int n, m;

struct SegmentTree {
    // Max 是区间最大值，se 是区间次大值，cnt 是最大值数量，laz 是懒标记，flag 维护当前区间时候每一个集合都有值
    int L[MAXN << 2], R[MAXN << 2], Max[MAXN << 2], se[MAXN << 2], cnt[MAXN << 2], laz[MAXN << 2], flag[MAXN << 2];
    LL sum[MAXN << 2]; // 区间和

    void update(int x) {
        sum[x] = sum[x << 1] + sum[x << 1 | 1]; // 维护区间和 
        flag[x] = (flag[x << 1] & flag[x << 1 | 1]); // 维护当前区间是否左右儿子都有取值
        if(Max[x << 1] == Max[x << 1 | 1]) { // 吉司机线段树要维护最大值和次大值
            Max[x] = Max[x << 1];
            cnt[x] = cnt[x << 1] + cnt[x << 1 | 1];
            se[x] = max(se[x << 1], se[x << 1 | 1]);
        }
        if(Max[x << 1] > Max[x << 1 | 1]) {
            Max[x] = Max[x << 1];
            cnt[x] = cnt[x << 1];
            se[x] = max(Max[x << 1 | 1], se[x << 1]);
        }
        if(Max[x << 1] < Max[x << 1 | 1]) {
            Max[x] = Max[x << 1 | 1];
            cnt[x] = cnt[x << 1 | 1];
            se[x] = max(Max[x << 1], se[x << 1 | 1]);
        }
        return ;
    }

    void build(int x, int l, int r) {
        L[x] = l, R[x] = r, se[x] = -1, laz[x] = -1; flag[x] = 0;
        if(l == r) {Max[x] = 1e9 + 7, cnt[x] = 1, sum[x] = 0; return ;}
        build(x << 1, l, mid);
        build(x << 1 | 1, mid + 1, r);
        update(x);
        return ;
    }

    void pushtag(int x, int k) { // 接到标记，更新节点
        if(Max[x] <= k) return ;
        sum[x] -= 1ll * Max[x] * cnt[x] * flag[x];
        sum[x] += 1ll * k * cnt[x] * (flag[x] = 1);
        Max[x] = laz[x] = k;
        return ;
    }

    void pushdown(int x) { // 下传标记
        if(laz[x] == -1) return ;
        pushtag(x << 1, laz[x]);
        pushtag(x << 1 | 1, laz[x]);
        laz[x] = -1; return ;
    }

    void change(int x, int l, int r, int k) {
        if(Max[x] <= k) return ; // 如果 k 大于等于当前区间最大值，没有必要往下找了
        if(se[x] < k && L[x] >= l && R[x] <= r) return pushtag(x, k); // 如果只需要更新最大值就直接更新
        pushdown(x); //否则就往下面暴力递归
        if(l <= mid) change(x << 1, l, r, k);
        if(r  > mid) change(x << 1 | 1, l, r, k);
        update(x);
        return ;
    }

} T,B;

LL GetSum(int x, int l, int r) { // 这里是获得答案的函数
    if(r < T.L[x] || l > T.R[x] || !T.sum[x] || !B.sum[x]) return 0ll; //其中一个是 0 就说明肯定这个节点下面的节点仍然是 0 ,返回
    if(T.L[x] >= l && T.R[x] <= r && T.flag[x] && B.flag[x]) // 两段都有值就返回两个区间和
    return T.sum[x] + B.sum[x];
    T.pushdown(x), B.pushdown(x);
    return GetSum(x << 1, l, r) + GetSum(x << 1 | 1, l, r); // 不然就访问子节点直到找到一个区间正负数线段树对应都有数
}

int main() {
    freopen("in.in", "r", stdin), freopen("out.out", "w", stdout);
    n = 1e5, m = read();
    T.build(1, 1, n); B.build(1, 1, n); // T 线段树处理正，B 处理负数
    while(m --) {
        int op = read(), l = read(), r = read() - 1;
        if(op == 1) {
            int k = read();
            if(k > 0) T.change(1, l, r, k);
            else B.change(1, l, r, - k); // 开了两棵线段树
        }
        else printf("%lld\n", GetSum(1, l, r));
    }
    return 0;
}