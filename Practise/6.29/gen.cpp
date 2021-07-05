#include <bits/stdc++.h>
using namespace std;
#define MAXN 114514
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
typedef long double db;
const db pi = acos( -1.0 );
const db eps = 1e-6;
int n;

char cc[MAXN];

const int C = 3;

void solve() {
	n = 100000;
	rep( i , 1 , 10 ) putchar(rand() % C + 'a');
	puts("");
	int len = 10;
	cout << n << endl;
	rep( i , 1 , n ) {
		int rnd = rand() % 7;
		while( rnd <= 2 && len == 10 ) rnd = rand() % 6;
		if( rnd == 0 ) printf("DELETE_LEFT\n") , -- len;
		if( rnd == 1 ) puts("DELETE_RIGHT") , -- len;
		if( rnd == 2 ) puts("DELETE_MIDDLE") , -- len;
		if( rnd == 3 ) printf("INSERT_LEFT %c\n",rand() % C + 'a') , ++ len;
		if( rnd == 4 ) printf("INSERT_RIGHT %c\n",rand() % C + 'a') , ++ len;
		if( rnd == 5 ) printf("INSERT_MIDDLE %c\n",rand() % C + 'a') , ++ len;
		if( rnd == 6 ) {
			int rq = rand() % 6 + 1;
			rep( i , 1 , rq ) cc[i] = rand() % C + 'a';
			printf("QUERY %s\n",cc + 1);
		}

	}
}

signed main() {
	srand(time(0) + (long long)new char);
//	freopen("astronomy.in","r",stdin);
//	freopen("astronomy.out","w",stdout);
//    int T;cin >> T;while( T-- ) solve();
	solve();
}



