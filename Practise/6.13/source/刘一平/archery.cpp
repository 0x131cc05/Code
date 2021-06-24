#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int MAXN = 4e5 + 5;
const int inf = 0x3f3f3f3f;

int n,r,nn;
int a[MAXN];

inline void init_f(int val,int f[])
{
	for(int i=1; i<=nn; ++i) f[i] = 0;
	for(int i=1; i<=n; ++i)
		if(a[i] >= val) ++f[(i+1)>>1];
}

inline void nxt_f(int f[])
{
	int tmp = f[1];
	if(tmp == 2) --f[1];
	for(int i=1; i<nn; ++i)
		if(f[i+1]) ++f[i], --f[i+1];
	if(tmp == 2) ++f[nn];
}

inline void change(int f[])
{
	int t = n + (r - n) % n;
	while(t--) nxt_f(f);
}

inline void get_f(int val,int f[])
{
	init_f(val, f);
	change(f);
}

namespace Subtask1
{
	const int MAXN = 1e3 + 5;
	
	void solve(void)
	{
		int ans = inf, ansi = -1;
		
		int val = a[1], pos = 1;
		for(int i=1; i<=nn; ++i)
		{
			static int f1[MAXN], f2[MAXN];
			get_f(val, f1); get_f(val+1, f2);
			
			int cur = inf;
			for(int j=1; j<=nn; ++j)
				if(f1[j] != f2[j])
				{
					cur = j;
					break;
				}
			if(cur <= ans)
				ans = cur, ansi = i;
			
			if(i == nn) break;
			swap(a[pos], a[pos+1]);
			swap(a[pos+1], a[pos+2]);
			pos += 2;
		}
		
		printf("%d",ansi);
		exit(0);
	}
}

int main(void)
{
	freopen("archery.in","r",stdin);
	freopen("archery.out","w",stdout);
	
	scanf("%d%d",&n,&r);
	nn = n; n <<= 1;
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]), a[i] = n - a[i] + 1;
	
	if(nn <= 500) Subtask1::solve();
	return 0;
}
