#include <bits/stdc++.h>
using namespace std;

#define LL long long

const int maxN = 5e4 + 10, INF = 1e9;

int n, q;
int a[maxN + 1], sum[maxN + 1];

namespace sub1
{
	int f[maxN + 1];

	inline void work()
	{
		while(q --)
		{
			int l, r, k;
			scanf("%d %d %d", &l, &r, &k);
			for(int i = l - 1; i <= r; i++) f[i] = 0;
			for(int i = 1; i <= k; i++)
			{
				int mx = f[l - 1] - sum[l - 1];
				f[l - 1] = -INF;
				for(int j = l; j <= r; j++)
				{
					int lst = mx;
					mx = max(mx, f[j] - sum[j]);
					f[j] = max(f[j - 1], lst + sum[j]);
				}
			}
			printf("%d\n", f[r]);
		}
	}
}

namespace sub2
{
	const LL INF = 1e18;

	struct Func
	{
		LL x;
		int v;
		Func(LL X = 0, int Y = 0) { x = X; v = Y; }
	}f[maxN + 1];

	inline void chkmx(Func &a, Func b)
	{
		if(a.x != b.x) a = a.x > b.x ? a : b;
		else a = a.v < b.v ? a : b;
	}

	inline void get(int L, int R, LL v)
	{
		for(int i = L - 1; i <= R; i++) f[i] = Func(0, 0);
		Func mx = Func(-sum[L - 1], 0);
		for(int i = L; i <= R; i++)
		{
			f[i] = f[i - 1];
			chkmx(f[i], Func(mx.x + sum[i] - v, mx.v + 1));
			chkmx(mx, Func(f[i].x - sum[i], f[i].v));
		}
	}

	inline LL work(int L, int R, int K)
	{
		int t = sum[R] - sum[L - 1];
		LL l = -t, r = t, ans;
		while(l <= r)
		{
			LL mid = (l + r) >> 1;
			get(L, R, mid);
			if(f[R].v <= K) ans = f[R].x + mid * K, r = mid - 1;
			else l = mid + 1;
		}
		return ans;
	}
}

int main()
{
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	scanf("%d %d", &n, &q);
	bool flag = true;
	for(int i = 1; i <= n; i++) 
	{
		scanf("%d", &a[i]);
		sum[i] = sum[i - 1] + a[i];
		if(a[i] < 0) flag = false;
	}

	if(n <= 50) { sub1::work(); return 0; }
	if(flag)
	{
		while(q --)
		{
			int l, r, k;
			scanf("%d %d %d", &l, &r, &k);
			printf("%d\n", sum[r] - sum[l - 1]);
		}
		return 0;
	}

	while(q --)
	{
		int l, r, k;
		scanf("%d %d %d", &l, &r, &k);
		printf("%lld\n", sub2::work(l, r, k));
	}
	return 0;
}
