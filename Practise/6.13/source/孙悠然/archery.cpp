#include <bits/stdc++.h>

using namespace std;

#define FOR(i, x, y) for(int i = (int)(x); i < (int)(y); ++i)
#define REP(i, x, y) for(int i = (int)(x); i <= (int)(y); ++i)

const int maxn = 1005;

int n, r;
int a[maxn], b[maxn], c[maxn], los[maxn];

inline int check(){
	FOR(it, 0, r){
		FOR(i, 0, n)
			los[i] = (b[i << 1] < b[i << 1 | 1]);
		FOR(i, 0, n << 1)
			c[i] = b[i];
		c[(n - 1) << 1 | (los[n - 1] ^ 1)] = b[0 << 1 | los[0]];
		FOR(i, 1, n){
			if(i - 1)
				c[(i - 1) << 1 | (los[i - 1] ^ 1)] = b[i << 1 | (los[i] ^ 1)];
			else
				c[(i - 1) << 1 | los[i - 1]] = b[i << 1 | (los[i] ^ 1)];
		}
		FOR(i, 0, n << 1)
			b[i] = c[i];
	}
	
	FOR(i, 0, n << 1) if(b[i] == a[0])
		return i >> 1;
	assert(false);
}

int main(){
	freopen("archery.in", "r", stdin);
	freopen("archery.out", "w", stdout); 
	
	scanf("%d%d", &n, &r);
	FOR(i, 0, n << 1)
		scanf("%d", a + i);
		
	int ans = 0x3f3f3f3f, pos = -0x3f3f3f3f;
	FOR(i, 0, n << 1){
		int ptr = 1;
		FOR(j, 0, i)
			b[j] = a[ptr++];
		b[i] = a[0];
		FOR(j, i + 1, n << 1)
			b[j] = a[ptr++];
		int res = check();
		if(res <= ans)
			ans = res, pos = i >> 1;
	}
	
	printf("%d\n", pos + 1);
	return 0;
}
