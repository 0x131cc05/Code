#include <bits/stdc++.h>
using namespace std;

inline char nc() {
//    return getchar();
    static char buf[1000000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2) ? EOF : *p1++;
}

template <class T>
inline void rd(T &x) {
    x=0; char c=nc(); int f=1; 
    while(!isdigit(c)) { if(c=='-') f=-1; c=nc(); }
    while(isdigit(c)) x=x*10-'0'+c,c=nc(); x*=f;
}

//#pragma GCC optimize("Ofast")
const int N = 200010;
const int SZ = 1200;

vector<int> G1[N], wkr[N];

int mark[N], ans[N], val[N], AiAe[N], belong[N];

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
} 

bool check(int u) {
	if (mark[u]) return true;
	for (int i = head[u]; i; i = e[i].next) 
        if (check(e[i].to)) return true; 
	return false;
}

void pushdown(int u, int val) {
	ans[u] = val;
	for (int i = head[u]; i; i = e[i].next) pushdown(e[i].to, val);
}

vector<int> zzh;

void dfs(int u, int top) {
	if (mark[u]) G1[top].push_back(u), top = u, zzh.push_back(u);
	belong[u] = top;
	for (int i = head[u]; i; i = e[i].next) dfs(e[i].to, top);
}

struct tcurts {
	int op, a, b;
} q[N];

int F[N]; 

inline int count(int i, int l, int r) {
	return upper_bound(wkr[i].begin(), wkr[i].end(), r) - lower_bound(wkr[i].begin(), wkr[i].end(), l);
}

inline void erase(int u) {
	int f = belong[F[u]];
//	cout << "erase: " << u << ' ' << f << endl;
//	assert(G1[f].size());
	for (auto &v : G1[f]) 
    	if (v == u) { swap(v, G1[f].back()); break; }
	G1[f].pop_back();
}

inline void ins(int u) {
//	cout << "link: " << u << ' ' << F[u] << endl;
	G1[F[u]].push_back(u);
}

void pd(int u, int v1) {
	AiAe[u] = v1;
	for (auto v : G1[u]) pd(v, v1);
}

int tim1 , tim2 , tim3 , tim4;

int main() {
	freopen("ex_data2.in", "r", stdin), freopen("fuck.out", "w", stdout);
	int n, fuck; rd(n),rd(fuck);
	cerr<<n<<' '<<fuck<<endl;
    for (int i = 1; i <= n; i++) rd(val[i]);
	for (int i = 1; i <= fuck; i++) rd(q[i].op),rd(q[i].a),rd(q[i].b);
	int hh = (fuck + SZ - 1) / SZ;
	for (int i = 1; i <= hh; i++) {
    	int l = (i - 1) * SZ + 1, r = min(fuck, i * SZ); zzh.clear(), G1[0].clear(), ecnt = 0;
    	for (int i = 0; i <= n; i++) head[i] = 0;
    	for (int j = 1; j <= n; j++) mark[j] = 0, wkr[j].clear(), ans[j] = 0, G1[j].clear();
    	for (int i = 1; i <= n; i++) adde(F[i], i);
    	for (int j = l; j <= r; j++) {
        	if (q[j].op == 0) mark[q[j].a] = 1;
        	else if (q[j].op == 1) mark[q[j].a] = mark[q[j].b] = 1;
        }
    	for (int i = head[0]; i; i = e[i].next) 
        	if (!check(e[i].to)) pushdown(e[i].to, val[e[i].to]);
        	else mark[e[i].to] = 1, dfs(e[i].to, 0);
        for (int i = 1; i <= n; i++) if (belong[i]) wkr[belong[i]].push_back(i);
    	for (int i = 1; i <= n; i++) ans[i] += ans[i - 1];
    	for (int i = l; i <= r; i++) {
        	if (q[i].op == 0) {
            	erase(q[i].a), F[q[i].a] = 0, val[q[i].a] = q[i].b, ins(q[i].a);
            } else if (q[i].op == 1) {
            	erase(q[i].a), F[q[i].a] = q[i].b, ins(q[i].a);
            } else {
            	int L = q[i].a, R = q[i].b, res = ans[R] - ans[L - 1];
            	for (auto v : G1[0]) pd(v, val[v]);
            	for (auto v : zzh) res += count(v, L, R) * AiAe[v];
            	printf("%d\n", res);
            }
        }
    }
    return 0;
}

