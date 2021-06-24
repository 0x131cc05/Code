#include<iostream>
#include<fstream>
#include<cstring>
#include<vector>
#include<cstdio>
#define mem(a,b) memset(a, b, sizeof(a))
#define rep(i,a,b) for(int i = (a); i <= (b); i++)
#define per(i,b,a) for(int i = (b); i >= (a); i--)
#define N 1010
#define M 5050
#define D 11
#define PII pair<int, int>
#define fr first
#define sc second
#define lowbit(x) (x&-x)
using namespace std;

int head[N], to[2*M], nxt[2*M];
int deg[N], w[2*M], dep[N], up[N][13], id[N];
int dp[N][1<<D];
int cnt, n, m;

struct edge{ int u, v, w; };
vector<int> son[N];
vector<edge> e[N], extra;
vector<PII> val[N];

void init(){ mem(head, -1), cnt = -1; }
void add_e(int a, int b, int _w, bool id){
    nxt[++cnt] = head[a], head[a] = cnt, to[cnt] = b;
    w[cnt] = _w, deg[a] += (_w == 0);
    if(id) add_e(b, a, _w, 0);
}

void dfs(int x, int fa){
    dep[x] = dep[fa]+1;
    up[x][0] = fa;
    rep(i,1,12) up[x][i] = up[up[x][i-1]][i-1];
    int num = 0;
    for(int i = head[x]; ~i; i = nxt[i]) if(w[i] == 0){
        if(to[i] == fa) continue;
        id[to[i]] = num++;
        son[x].push_back(to[i]);
        dfs(to[i], x);
    }
}
int lca(int a, int b){
    if(dep[a] < dep[b]) swap(a, b);
    per(i,12,0) if(dep[up[a][i]] >= dep[b]) a = up[a][i];
    if(a == b) return b;
    per(i,12,0) if(up[a][i] != up[b][i]) a = up[a][i], b = up[b][i];
    return up[a][0];
}
int dis(int a, int b){
    return dep[a]+dep[b]-2*dep[lca(a, b)];
}

PII get(int x, int goal){
    int ret = (x == goal ? 0 : dp[x][(1<<deg[x])-1]), dir = -1;
    while(x != goal){
        int k = id[x]; x = up[x][0];
        ret += dp[x][((1<<deg[x])-1)^(1<<k)];
        dir = k;
    }
    return {ret, dir};
}

bool Max(int &a, int b){ return a < b ? a = b, 1 : 0; }

void solve(int x, int fa){
    int empty = 0;
    for(int i = head[x], y; ~i; i = nxt[i]) if(w[i] == 0){
        if((y = to[i]) == fa) continue;
        solve(y, x);
        empty += dp[y][(1<<deg[y])-1];
    }
    for(edge k : e[x]){
        PII a = get(k.u, x), b = get(k.v, x);  
        int bit = 0;
        if(~a.sc) bit |= (1<<a.sc);
        if(~b.sc) bit |= (1<<b.sc);
        val[x].push_back({a.fr+b.fr+k.w, bit});
    }
    if(fa) deg[x]--;
    rep(i,0,(1<<deg[x])-1){
        rep(j,0,deg[x]-1) 
            if(i & (1<<j)) Max(dp[x][i], dp[x][i ^ (1<<j)]);
            else {
                int k = son[x][j];
                Max(dp[x][i | (1<<j)], dp[x][i]+dp[k][(1<<deg[k])-1]);
            }
        
        rep(j,0,(int)e[x].size()-1){
            if(i & val[x][j].sc) continue;
            Max(dp[x][i | val[x][j].sc], dp[x][i]+val[x][j].fr);
        }
    }
}

int main(){
    freopen("training.in", "r", stdin);
    freopen("training.out", "w", stdout);
    cin>>n>>m;
    int u, v, w;
    init();
    int tot = 0;
    rep(i,1,m){
        cin>>u>>v>>w, add_e(u, v, w, 1);
        if(w) extra.push_back({u, v, w});
        tot += w;
    }

    dfs(1, 0);
    for(edge k : extra) if(dis(k.u, k.v)%2 == 0)
        e[lca(k.u, k.v)].push_back(k);
    
    solve(1, 0);
    cout<< tot-dp[1][(1<<deg[1])-1] <<endl;
    return 0;
}
/*
5 8
2 1 0
3 2 0
4 3 0
5 4 0
1 3 2
3 5 2
2 4 5 
2 5 1
*/
