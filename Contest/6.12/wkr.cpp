#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;
const int G = 3;

int qpow(int base,int tms)
{
	int tmp = 1;
	while(tms)
	{
		if(tms & 1) tmp = tmp * 1ll * base % mod;
		base = base * 1ll * base % mod;
		tms >>= 1;
	}
	return tmp;
}

int rev[524288],limit,l;

void NTT(int *A,int typ)
{
	for(int i = 0;i < limit; ++ i)
		if(i < rev[i]) swap(A[i],A[rev[i]]);
	for(int len = 1;len < limit;len <<= 1)
	{
		int wn = qpow((typ == -1 ? qpow(G,mod - 2) : G),(mod - 1) / len / 2);
		for(int i = 0;i < limit;i += len << 1)
			for(int j = 0,w = 1;j < len;j ++,w = w * 1ll * wn % mod)
			{
				int x = A[i + j],y = A[i + j + len] * 1ll * w % mod;
				A[i + j] = (x + y) % mod;
				A[i + j + len] = (x - y + mod) % mod;
			}
	}
	if(typ == -1)
	{
		int inv = qpow(limit,mod - 2);
		for(int i = 0;i < limit; ++ i)
			A[i] = A[i] * 1ll * inv % mod;
	}
}

void init(int len)
{
	limit = 1,l = 0;
	while(limit <= len) limit <<= 1,l ++;
	for(int i = 0;i < limit; ++ i)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << l - 1);
}

int n,m,x;
int val[1000050];
int wpw[50050];
int a[524288],b[524288];
int dxs[50050];
pair<int,int> as[50050];
int cnt;

int main()
{
	scanf("%d%d%d",&n,&m,&x);
	int w = x;
	wpw[0] = 1;
	int lim = 1;
	wpw[lim] = w;
	int tp = x;
	while(tp != 1) tp = tp * 1ll * w % mod,lim ++,wpw[lim] = tp;
	int iw = wpw[lim - 1];
	for(int i = 1;i <= n; ++ i)
		scanf("%d",&val[i]);
	for(int i = 0;i < lim; ++ i) dxs[i] = 1;
	sort(val + 1,val + 1 + n);
	for(int i = 1;i <= n; ++ i)
	{
		int nxt = i;
		while(val[nxt + 1] == val[i]) nxt ++;
		int cur = 1,dw = wpw[val[i]];
		for(int j = 0;j < lim; ++ j)
			dxs[j] = dxs[j] * 1ll * qpow(cur + 1,nxt - i + 1) % mod,cur = cur * 1ll * dw % mod;
		i = nxt;
	}
	for (int i = 0; i < lim; i++) cout << dxs[i] << ' ';
	cout << endl;
	for(int i = 0;i < lim; ++ i)
		dxs[i] = qpow(dxs[i],m);
	for(int i = 0;i <= 2 * lim; ++ i)
		a[2 * lim - i] = qpow(iw,i * 1ll * (i - 1) / 2 % (mod - 1)) % mod, cout << a[2 * lim - i] << ' ';
	cout << endl;
	for(int i = 0;i < lim; ++ i)
		b[i] = dxs[i] * 1ll * qpow(w,i * 1ll * (i - 1) / 2 % (mod - 1)) % mod, cout << b[i] << ' ';
	cout << endl;
	init(lim * 3);
	NTT(a,1); NTT(b,1);
	for(int i = 0;i < limit; ++ i)
		a[i] = a[i] * 1ll * b[i] % mod;
	NTT(a,-1);
	int iv = qpow(lim,mod - 2);
	for(int i = 0;i < lim; ++ i)
	{
		dxs[i] = a[2 * lim - i] * 1ll * qpow(w,i * 1ll * (i - 1) / 2 % (mod - 1)) % mod * iv % mod;
		if(dxs[i])
			as[++ cnt] = make_pair(wpw[i],dxs[i]);
	}
	sort(as + 1,as + 1 + cnt);
	for(int i = 1;i <= cnt; ++ i)
		printf("%d %d\n",as[i].first,as[i].second);
}
