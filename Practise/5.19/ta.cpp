#include <bits/stdc++.h>
using namespace std;
#define MAXN 2006
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
#define P 998244353
int n , q;
ll A[MAXN] , S[MAXN];
map<int,int> M;

void solve() {
	n = 5 , q = 5;
	cout << n << ' ' << q << endl;
	rep( i , 1 , n ) {
		A[i] = rand() % 5 + 1;
		while( M[A[i]] ) A[i] = rand() % 5 + 1;
		M[A[i]] = 1;
	}
	rep( i , 1 , n ) printf("%d ",A[i]);
	puts("");
	rep( i , 1 , q ) {
		int op = rand() % 2 + 1 , l = rand()% n + 1 , r = rand() % n + 1;
		if( l > r ) swap( l , r );
		printf("%d %d %d\n",op,l,r);
	}
}

signed main() {
//    freopen("input","r",stdin);
	srand(time(0) + (long long)new char);
   //freopen("input","w",stdout);
//    int T;cin >> T;while( T-- ) solve();
	solve();
}
