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
#define MAXN 5006
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
typedef long long ll;
int n , r;
int A[MAXN];
vi pr , tf[MAXN] , tm[MAXN];
int que( ) {
	rep( i , 1 , n ) tf[i].clear();
	rep( i , 1 , 2 * n ) tf[i + 1 >> 1].pb( pr[i - 1] );
	rep( i , 1 , r ) {
		rep( j , 2 , n ) {
			int mn = A[tf[j][0]] < A[tf[j][1]] ? 0 : 1;
			tm[j - 1].pb( tf[j][mn] ) , tm[j].pb( tf[j][mn ^ 1] );
		}
		int mn = A[tf[1][0]] < A[tf[1][1]] ? 0 : 1;
		tm[n].pb( tf[1][mn ^ 1] ) , tm[1].pb( tf[1][mn] );
		rep( j , 1 , n ) tf[j] = tm[j] , tm[j].clear();
	}
	rep( i , 1 , n )
		if( tf[i][0] == 1 || tf[i][1] == 1 ) return i;
	return -1;
}

void solve() {
	cin >> n >> r;
	int val;
	rep( i , 1 , 2 * n ) {
		scanf("%d",A + i);
		if( i != 1 ) pr.pb( i );
	}
	int re = 0x3f3f3f3f , mx = 0;
	rep( i , 0 , 2 * n - 1 ) {
		pr.insert( pr.begin() + i , 1 );
		int t = que( );
		if( re >= t ) mx = i + 1 >> 1 , re = t;
		pr.erase( pr.begin() + i );
	}
	printf("%d\n",mx);
}

signed main() {
	freopen("archery.in","r",stdin);
	freopen("archery.out","w",stdout);
//    int T;cin >> T;while( T-- ) solve();
	solve();
}




