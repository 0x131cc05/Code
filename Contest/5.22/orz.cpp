#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")

using namespace std;

int n;
int seq[50050];
vector<int> num[50050];
const int mod = 998244353,seed = 1000007;
long long pw[50050],inv[50050];

long long qpow(long long base,int tms)
{
	long long tmp = 1;
	while(tms)
	{
		if(tms & 1) tmp = tmp * 1ll * base % mod;
		base = base * 1ll * base % mod;
		tms >>= 1;
	}
	return tmp;
}

int ll;

struct zhuxishu
{
	int son[30000050][2];
	int val[30000050];
	int pcnt;
	void Push_Up(int rt)
	{
		val[rt] = (val[son[rt][0]] + val[son[rt][1]]) % mod;
	}
	void Update(int &rt,int rt0,int l,int r,int po,int vl)
	{
		rt = ++ pcnt;
		son[rt][0] = son[rt0][0]; son[rt][1] = son[rt0][1];
		val[rt] = val[rt0];
		if(l == r)
		{
			val[rt] += vl;
			return ;
		}
		int mid = (l + r) >> 1;
		if(mid >= po) Update(son[rt][0],son[rt0][0],l,mid,po,vl);
		else Update(son[rt][1],son[rt0][1],mid + 1,r,po,vl);
		Push_Up(rt);
	}
	int Query(int rt,int l,int r)
	{
		if(!rt) return 0;
		if(ll <= l) return val[rt];
		int mid = (l + r) >> 1;
		if(mid >= ll) return (Query(son[rt][0],l,mid) + val[son[rt][1]]) % mod;
		return Query(son[rt][1],mid + 1,r);
	}
}tree;

int root[50050];

unordered_map<int,int> mp[50050];

inline int Hash(int l,int r)
{
	ll = l; return tree.Query(root[r],1,n) * 1ll * inv[l] % mod;
}

int lst[50050];
int rnk[50050];

int get(int nu,int lw)
{
	return *lower_bound(num[nu].begin(),num[nu].end(),lw) - lw;
}

bool cmp(int a,int b)
{
	int l = 0,r = min(n - a,n - b),ans = -1;
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		if(Hash(a,a + mid) == Hash(b,b + mid))
			l = mid + 1;
		else
			r = mid - 1,ans = mid;
	}
	if(ans == -1)
		return a > b;
	return get(seq[a + ans],a) < get(seq[b + ans],b);
}

int main()
{
	scanf("%d",&n);
	for(int i = 1;i <= n; ++ i)
	{
		scanf("%d",&seq[i]);
		num[seq[i]].push_back(i);
	}
	pw[0] = 1;
	inv[0] = 1;
	for(int i = 1;i <= 50000; ++ i)
	{
		pw[i] = pw[i - 1] * 1ll * seed % mod;
		inv[i] = qpow(pw[i],mod - 2);
	}
	for(int i = 1;i <= n; ++ i)
	{
		if(lst[seq[i]])
			tree.Update(root[i],root[i - 1],1,n,lst[seq[i]],(i - lst[seq[i]]) * 1ll * pw[lst[seq[i]]] % mod);
		else
			root[i] = root[i - 1];
		lst[seq[i]] = i;
	}
//	for(int i = 1;i <= n; ++ i)
//		for(int j = i;j <= n; ++ j)
//			printf("%d %d %d\n",i,j,Hash(i,j));
	for(int i = 1;i <= n; ++ i)
		rnk[i] = i;
	stable_sort(rnk + 1,rnk + 1 + n,cmp);
	long long ans = n * 1ll * (n + 1) / 2;
	for(int i = 2;i <= n; ++ i)
	{
		int l = 0,r = min(n - rnk[i],n - rnk[i - 1]),as = 0;
		while(l <= r)
		{
			int mid = (l + r) >> 1;
			if(Hash(rnk[i - 1],rnk[i - 1] + mid) == Hash(rnk[i],rnk[i] + mid))
				l = mid + 1,as = mid;
			else
				r = mid - 1;
		}
		ans -= as + 1;
	}
	printf("%lld\n",ans);
}
