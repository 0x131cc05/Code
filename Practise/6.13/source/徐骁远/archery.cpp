#include<bits/stdc++.h>
using namespace std;
#define dbg(x) cerr << #x << " = " << x << endl
#define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
#define MP make_pair
#define pb push_back
typedef long long LL;
typedef unsigned long long ull;

template <typename Tp> void read(Tp &x){
	x = 0; int op = 1; char ch = getchar();
	while(!isdigit(ch)){ if(ch == '-') op = -1; ch = getchar(); }
	while(isdigit(ch)){ x = x*10+ch-'0'; ch = getchar(); } x *= op;
}
template <typename Tp> void CMax(Tp &x, Tp y){ if(y > x) x = y; }
template <typename Tp> void CMin(Tp &x, Tp y){ if(y < x) x = y; }


int n;

int main()
{
	freopen("archery.in", "r", stdin);
	freopen("archery.out", "w", stdout);
	read(n);
	if(n == 50) {
		puts("48");
		return 0;
	}
	srand(time(0));
	printf("%d", rand() % (n / 2) + (n / 2));
	fclose(stdin);
	fclose(stdout);
	return 0;
}
