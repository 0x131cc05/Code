#include <bits/stdc++.h>
using namespace std;
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define loop(i, a) for (int i = 0; i < (a); ++i)
#define cont(i, a) for (int i = 1; i <= (a); ++i)
#define circ(i, a, b) for (int i = (a); i <= (b); ++i)
#define range(i, a, b, c) for (int i = (a); (c) > 0 ? i <= (b) : i >= (b); i += (c))
#define parse(it, x) for (auto &it : (x))
#define pub push_back
#define pob pop_back
#define emb emplace_back
#define mak make_pair
#define mkt make_tuple
typedef long long ll;
typedef long double lf;
const int Inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3fll;

int n, r, t;
int a[5005], b[5005];
vector<int> cur[5005], nxt[5005];

int main() {
    #ifndef Acetyl
    freopen("archery.in", "r", stdin);
    freopen("archery.out", "w", stdout);
    #endif
    cin >> n >> r >> t; n <<= 1;
    cont(i, n - 1) cin >> a[i];
    int res = Inf, ius = 0;
    cont(i, n) {
        cont(j, n - 1) b[j + (j >= i)] = a[j];
        b[i] = t;
        cont(i, n >> 1) cur[i].clear();
        cont(i, n >> 1) cur[i].pub(b[i * 2]), cur[i].pub(b[i * 2 - 1]);
        loop(R, r) {
            cont(i, n >> 1) nxt[i].clear();
            nxt[1].pub(min(cur[1][0], cur[1][1]));
            nxt[n >> 1].pub(max(cur[1][0], cur[1][1]));
            circ(i, 2, n >> 1) {
                nxt[i - 1].pub(min(cur[i][0], cur[i][1]));
                nxt[i].pub(max(cur[i][0], cur[i][1]));
            }
            cont(i, n >> 1) cur[i] = nxt[i];
        }
        int pos = n;
        cont(i, n >> 1) if (cur[i][0] == t || cur[i][1] == t) {
            pos = i;
            break;
        }
        if (pos <= res) {
            res = pos;
            ius = i;
        }
    }
    printf("%d\n", (ius + 1) / 2);
    return 0;
}
/*

4 8
7 4 2 6 5 8 1 3

*/