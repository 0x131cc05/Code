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
#define MAXN 1006
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
const int P = 998244353;
ll n;
int m , k;

int Pow( int x , int a ) {
	int ret = 1;
	while( a ) {
		if( a & 1 ) ret = ret * 1ll * x % P;
		x = x * 1ll * x % P , a >>= 1;
	}
	return ret;
}

int J[MAXN] , iJ[MAXN];
int C( int a , int b ) {
	if( b > a || b < 0 || a < 0 ) return 0;
	return J[a] * 1ll * iJ[b] % P * iJ[a - b] % P;
}
int gc[506];
void CC( ll a , int b ) {
	int re = 1 , fk = 0;
	per( i , a % P + P , a % P + P - b ) {
		if( a < fk || a < 0 ) gc[fk] = 0;
		else {
			gc[fk] = re * 1ll * iJ[fk] % P;
			re = re * 1ll * i % P;
			++fk;
		}
	}
}

void Inc( int& x , int y ) {
	x = ( x + y < P ? x + y : x + y - P );
}

int S[506] , s[506] , i;
ll tot;
void solve( ll x ) {
//	cout << x << endl;
	if( x <= 50 ) {
		rep( k , 0 , m ) S[i] = 0;
		rep( c , 1 , x ) {
			CC( n - ( tot - c + 1 ) * i - 1 , m );
			rep( t , 0 , m ) Inc( S[t] , gc[t] );
		}
		return;
	}
	ll a = x >> 1;
	rep( c , 0 , m ) s[c] = S[c];
	if( x != 1 ) {
		solve( a );
		CC( a * i , m );
		rep( c , 0 , m ) {
			s[c] = S[c];
			rep( j , 0 , c )
				s[c] = ( s[c] + gc[c - j] * 1ll * S[j] ) % P;
		}
	}
	if( x & 1 ) {
		CC( n - ( tot - x + 1 ) * i - 1 , m );
		rep( c , 0 , m ) Inc( s[c] , gc[c] );
	}
	rep( c , 0 , m ) S[c] = s[c];
}

void solve() {
	cin >> n >> m;
	J[0] = iJ[0] = 1;
	rep( i , 1 , 506 ) J[i] = J[i - 1] * 1ll * i % P , iJ[i] = Pow( J[i] , P - 2 );
	int as = 0;
//	tot = n - 1;
//	solve( n - 1 );
//	rep( i , 0 , m ) cout << S[i] << ' '; puts("");
	for( i = 1 ; i < m ; ++ i ) {
		rep( c , 0 , m ) S[c] = 0;
		tot = n / i - ( n % i == 0 );
		solve( tot );
		int w = C( m , i ) * 1ll * S[m - i - 1] % P;
		if( i & 1 ) as = ( as + w ) % P;
		else as = ( as + P - w ) % P;
	}
	if( n % m == 0 ) {
		if( m & 1 ) Inc( as , 1 );
		else Inc( as , P - 1 );
	}
	cout << as << endl;
}

signed main() {
//	freopen("in.in","r",stdin);
//	freopen("ot","w",stdout);
//    int T;cin >> T;while( T-- ) solve();
	solve();
}

