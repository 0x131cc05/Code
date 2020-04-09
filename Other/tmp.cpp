#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "cmath"
#include "vector"
#include "map"
#include "set"
#include "queue"
using namespace std;
#define MAXN 100006
//#define int long long
#define rep(i, a, b) for (int i = (a), i##end = (b); i <= i##end; ++i)
#define per(i, a, b) for (int i = (a), i##end = (b); i >= i##end; --i)
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define vi vector<int>
#define all(x) (x).begin() , (x).end()
#define mem( a ) memset( a , 0 , sizeof a )
#define P 998244353
typedef long long ll;
int n , m , k;
int A[MAXN] , ch[MAXN];
vector<pii> G[MAXN] , pr;
int p2[MAXN];

int siz[MAXN] , ea;
int g[MAXN][19] , dep[MAXN];
ll dis[MAXN];

int J[MAXN] , iJ[MAXN];
int C( int a , int b ) {
    if( a < b ) return 0;
    return J[a] * 1ll * iJ[b] % P * iJ[a - b] % P;
}

void dfs( int u , int fa ) {
    siz[u] = ch[u];
    for( auto& t : G[u] ) if( t.fi != fa ) {
            int v = t.fi;
            g[v][0] = u , dep[v] = dep[u] + 1 , dis[v] = dis[u] + t.se;
            for( int k = 1 ; k < 19 ; ++ k )
                if( g[g[v][k - 1]][k - 1] ) g[v][k] = g[g[v][k - 1]][k - 1];
                else break;
            dfs( v , u );
            siz[u] += siz[v];
            ( ea += 1ll * t.se * ( ( C( m , k ) - C( siz[v] , k ) + P ) % P - C( m - siz[v] , k ) + P ) % P ) %= P;
        }
}
int lca( int u , int v ) {
    if( dep[u] < dep[v] ) swap( u , v );
    for( int k = 18 ; k >= 0 ; -- k ) if( dep[g[u][k]] >= dep[v] ) u = g[u][k];
    if( u == v ) return u;
    for( int k = 18 ; k >= 0 ; -- k )
        if( g[u][k] != g[v][k] ) u = g[u][k] , v = g[v][k];
    return g[u][0];
}

ll d[506][506];

int Pow( int x , int a ) {
    int ret = 1;
    while( a ) {
        if( a & 1 ) ret = 1ll * ret * x % P;
        x = 1ll * x * x % P , a >>= 1;
    }
    return ret;
}

void solve() {
//    cout << 10ll * Pow( 3 , P - 2 ) % P << endl;
    cin >> n >> m >> k;
    p2[0] = J[0] = iJ[0] = 1;
    rep( i , 1 , n ) p2[i] = p2[i - 1] * 2 % P , J[i] = 1ll * J[i - 1] * i % P , iJ[i] = Pow( J[i] , P - 2 );
    int u , v , w;
    rep( i , 1 , m ) scanf("%d",A + i) , ch[A[i]] = 1;
    rep( i , 2 , n ) {
        scanf("%d%d%d",&u,&v,&w) , G[u].eb( mp( v , w ) ) , G[v].eb( mp( u , w ) );
    }
    dep[1] = 1 , dfs( 1 , 1 );
    ea = ea * 2 % P;
    rep( i , 1 , m ) rep( j , i , m ) d[i][j] = d[j][i] = dis[A[i]] + dis[A[j]] - 2 * dis[lca( A[i] , A[j] )];
    int ok , res = 0;
    ll rd , re;
//    cout << lca( A[3] , A[4] ) << endl;
    rep( i , 1 , m ) {
        rep( j , 1 , i - 1 ) {
            rd = d[i][j] , ok = 2;
            rep(t, 1, m) if (t != i && t != j) {
                if (max(d[t][i], d[t][j]) > rd) continue;
                if (d[t][i] == rd && t < j) continue;
                if (d[t][j] == rd && t < i) continue;
                ok++;
            }
            ( res += 1ll * C( ok - 2 , k - 2 ) * ( rd % P ) % P ) %= P;
        }
    }
//    cout << res << ' ' << ea << endl;
    cout << 1ll * ( ea - res + P ) % P * ( Pow( C( m , k ) , P - 2 ) ) % P << endl;
}

signed main() {
//    freopen("in1.in","r",stdin);
//    freopen("fuckout","w",stdout);
//    int T;cin >> T;while( T-- ) solve();
    solve();
}

