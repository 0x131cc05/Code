#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "cmath"
#include "vector"
#include "map"
#include "set"
#include "queue"
#include "cassert"
#include "unordered_map"
#include "ctime"
using namespace std;
#define MAXN 200006
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
int a , b , x , y , z , P , c , Q;
const int R = 998244353 , base = 523;
int A[MAXN] , pw[MAXN];

struct mtrx {
	#define N 3
	int A[N][N];
	mtrx( ) { mem( A ); }
	mtrx( int a , int b , int c ) {
		mem( A );
		A[0][0] = a , A[0][1] = b , A[0][2] = c;
		A[1][0] = 1 , A[2][2] = 1;
	}
	int* operator [] ( int a ) {
		return A[a];
	}
	int PP = P * P;
	mtrx operator * ( mtrx B ) {
		mtrx re;
		rep( i , 0 , N - 1 ) rep( k , 0 , N - 1 ) if( A[i][k] ) rep( j , 0 , N - 1 ) 
			re[i][j] = ( re[i][j] + A[i][k] * B[k][j] ) , re[i][j] = re[i][j] > PP ? re[i][j] - PP : re[i][j];
		rep( i , 0 , N - 1 ) rep( j , 0 , N - 1 ) re[i][j] %= P;
		return re;
	}
	int hash( ) {
		int re = 0;
		rep( i , 0 , N - 1 ) rep( j , 0 , N - 1 ) re = ( re + A[i][j] * 1ll * pw[i * N + j] ) % R;
		return re;
	}
	bool operator == ( mtrx B ) {
		return hash( ) == B.hash( );
	}
	void in( ) {
		for( int i = 0 ; i < N ; ++ i ) A[i][i] = 1;
	}
	void ot( ) {
		rep( i , 0 , N - 1 ) { rep( j , 0 , N - 1 ) printf("%d ",A[i][j]); puts(""); }
	}
};

mtrx Pow( mtrx x , int a ) {
	mtrx ret;
	ret.in( );
	while( a ) {
		if( a & 1 ) ret = x * ret;
		x = x * x , a >>= 1;
	}
	return ret;
}

void solve() {
	pw[0] = 1;
	rep( i , 1 , 10 ) pw[i] = pw[i - 1] * 1ll * base % R;
	cin >> a >> b >> x >> y >> z >> P >> c >> Q;
	vector<int> fk;
	if( y == 0 ) {
		static int oc[MAXN];
		if( z == 0 && x == 0 ) {
			auto que = []( int x ) {
				if( x == 1 ) return A[1] == c;
				return A[1] == c + A[2] == c;
			};
			rep( i , 1 , Q ) {
				ll l , r;
				scanf("%lld%lld",&l,&r);
				printf("%lld\n",que( r ) - que( l - 1 ));
			}
		}
		mem( oc );
		mem( A );
		A[1] = a , A[2] = b , A[3] = ( A[2] * x + A[1] * y + z ) % P;
		int pas = 0;
		rep( i , 1 , 2 ) if( A[i] == c ) ++ pas;
		if( A[3] == c ) fk.pb( 0 );
		int fkp = 0;
		rep( i , 4 , P ) {
			A[i] = ( A[i - 1] * x + A[i - 2] * y + z ) % P;
			if( A[i] == A[3] ) {
				fkp = i - 2;
				break;
			}
			if( A[i] == c ) fk.pb( i - 3 ) , cout << i << endl;
		}
		auto que = [&]( ll t ) {
			t -= 3;
			ll as = pas + fk.size() * 1ll * ( t / fkp );
			t %= fkp;
			as += upper_bound( all( fk ) , t ) - fk.begin();
			return as;
		};
		rep( i , 1 , Q ) {
			ll l , r;
			scanf("%lld%lld",&l,&r);
			printf("%lld\n",que( r ) - que( l - 1 ));
		}
		return;
	}
	int blo = ceil( sqrt( P ) ) * P , bl = ceil( sqrt( P ) );
	mtrx B( x , y , z );
	mtrx S;
	S.in( );
	unordered_map<int,int> M;
	S = Pow( B , bl );
	mtrx F;
	F[0][0] = b , F[1][0] = a , F[2][0] = 1;
	rep( b , 1 , blo ) {
		F = S * F;
		if( !M.count( F.hash() ) ) M[F.hash()] = b;
	}
	auto fdb = [&]( mtrx st ) {
		int re = 0x3f3f3f3f;
		if( M.count( st.hash() ) ) re = M[st.hash()] * bl;
		rep( b , 1 , bl - 1 ) {
			st = B * st;
			int hs = st.hash();
			if( M.count( hs ) ) re = min( re , M[hs] * bl - b );
		}
		return re;
	};
	mtrx T;
	T[0][0] = b , T[1][0] = a , T[2][0] = 1;
	int fkp = fdb( T );
	assert( fkp < 1e9 );
	mem( T.A );
	rep( x , 0 , P - 1 ) {
		T[0][0] = c , T[1][0] = x , T[2][0] = 1;
		int re = fdb( T );
		if( re < 1e9 ) fk.pb( ( re + 1 ) % fkp );// , cout << re << endl;
	}
	sort( all( fk ) );
	int cur = -clock();
	auto que = [&]( ll x ) {
		x -= 1;
		ll as = ( a == c ) + x / fkp * fk.size();
		x %= fkp;
		return as + upper_bound( all( fk ) , x ) - fk.begin();
	};
	rep( i , 1 , Q ) {
		ll L , R;
		scanf("%lld%lld",&L,&R);
		printf("%lld\n",que( R ) - que( L - 1 ));
	}
	cur += clock();
	cerr << cur << endl;
}

signed main() {
//	freopen("input","r",stdin);
//	freopen("out","w",stdout);
    int T;cin >> T;while( T-- ) solve();
//    solve();
}

