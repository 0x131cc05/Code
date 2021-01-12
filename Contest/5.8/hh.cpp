#include <bits/stdc++.h>

using namespace std;

int gcd(int x,int y)
{
	return y ? gcd(y,x % y) : x;
}

int Phi(int base)
{
	int tmp = base,phi = base;
	for(int i = 2;i * 1ll * i <= base; ++ i)
	{
		if(tmp % i == 0)
		{
			phi = phi / i * (i - 1);
			while(tmp % i == 0) tmp /= i;
		}
	}
	if(tmp > 1) phi = phi / tmp * (tmp - 1);
	return phi;
}

long long qpow(long long base,long long tms,long long mod)
{
	long long tmp = 1;
	while(tms)
	{
		if(tms & 1) tmp = tmp * base % mod;
		base = base * base % mod;
		tms >>= 1;
	}
	return tmp;
}

typedef long long ll;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    ll g = exgcd(b, a % b, x, y);
    ll t = x;
    x = y;
    y = t - a / b * y;
    return g;
}

ll mul(ll x, ll y, ll mod) {
    ll tmp = (long double)x * y / mod;
    return x * y - tmp * mod;
}

long long f[3][2];

ll excrt() {
    for (int i = 2; i <= 2; i++) {
        ll a = f[1][0], b = f[1][1], c = f[i][0], d = f[i][1], x, y;
        ll g = exgcd(a, c, x, y);
        if ((d - b) % g)
            return -1;
        ll l = a / g * c;
        x = (x % l + l) % l;
        x = mul((d - b) / g, x, l);
        x = ((mul(x, a, l) + b) % l + l) % l;
        f[1][0] = l, f[1][1] = x;
    }
    return f[1][1];
}

long long Solve(int base,int mod)
{
	if(mod == 1) return 1;
	int pm = Phi(mod);
	long long nxt = Solve(base,gcd(mod,pm));
	long long right_side = qpow(base,nxt,mod);
	long long left_side = nxt;
	f[1][0] = mod; f[1][1] = right_side;
	f[2][0] = pm; f[2][1] = left_side;
	long long k = excrt();
	if(k < pm) k += pm * 1ll * mod / gcd(pm,mod);
	return k;
}

int main()
{
	int q; scanf("%d",&q);
	while(q --)
	{
		int a,m; scanf("%d%d",&a,&m);
		printf("%lld\n",Solve(a,m));
	}
	return 0;	
}

