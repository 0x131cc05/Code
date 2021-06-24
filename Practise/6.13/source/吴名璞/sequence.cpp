#include<bits/stdc++.h>

#define INL inline
#define ll long long
#define ull unsigned long long
#define ll long long
#define si size()

INL int read()
{
	int x=0,w=1;char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
	if(ch=='-')ch=getchar(),w=-1;
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();
	return x*w;
}

const int N = 10005 + 5;
const ll INF = 1ll<<30;

int n, Q;
ll a[N];
bool ok=1;
std::vector <ll> t[N<<2][2][2];

#define i0 i + i
#define i1 i + i + 1

INL void gx(std::vector <ll> &a, std::vector <ll> b, std::vector <ll> c)
{
	int n = b.si - 1, m = c.si - 1;
	a.resize(n + m + 1);
	ll s = b[0] + c[0]; a[0] = s;
	int l = 0, r = 0;
	while(l < n && r < m)
	{
		if(b[l + 1] - b[l] > c[r + 1] - c[r])
		{
			s += b[l + 1] - b[l];
			l ++;
		}
		else
		{
			s += c[r + 1] - c[r];
			r ++;
		}
		a[l + r] = s;
	}
	while(l < n) 
		s += b[l + 1] - b[l], l ++, a[l + r] = s;
	while(r < m)
		s += c[r + 1] - c[r], r ++, a[l + r] = s;
}

INL void fz(std::vector <ll> &a, std::vector <ll> b, int op)
{
	for(int i=0;i<b.si;i++)
	{
		a[i] = std::max(a[i], b[i]);
		if(op && i)
		{
			a[i - 1] = std::max(a[i - 1], b[i]);
		}
	}
}

void bt(int i, int x, int y)
{
	if(x == y)
	{
		for(int u=0;u<=1;u++)
		for(int v=0;v<=1;v++)
		{
			t[i][u][v].resize(2);
			t[i][u][v][0] = t[i][u][v][1] = -INF;
			if(u == 0 && v == 0) t[i][u][v][0] = 0;
			if(u == 1 && v == 1) t[i][u][v][1] = a[x];
		}
		return;
	}
	int m = (x + y) >> 1;
	bt(i0, x, m);
	bt(i1, m + 1, y);
	int len = y - x + 1;
	for(int u=0;u<=1;u++)
	for(int v=0;v<=1;v++)
	{
		t[i][u][v].resize(len + 1);
		for(int j=0;j<=len;j++)
			t[i][u][v][j] = -INF * n;
	}
	for(int u=0;u<=1;u++)
	for(int v=0;v<=1;v++)
	for(int p=0;p<=1;p++)
	for(int q=0;q<=1;q++)
	{
		std::vector <ll> b;
		gx(b, t[i0][u][v], t[i1][p][q]);
		fz(t[i][u][q], b, (v && p));
	}
}

void build()
{
	for(int i=1;i<=n;i++)
	{
		a[i]=1ll*read();
		if(a[i]<0)ok=0;
	}
	bt(1, 1, n);
}

struct nod{int x, y, k;} b[N];

int L[N],R[N],m[N],as[N];

int d[N];

int cmpd(int x, int y){return m[x] > m[y];}

int l[N<<2][2][2];

int pl,pr;

int mk;

struct P
{
	ll x; int y;
	P(ll _x = 0, int _y = 0)
	{
		x = _x, y = _y;
	}
};

P operator + (P a, P b) { return P(a.x + b.x, a.y + b.y);}
bool operator < (P a, P b) { return a.x == b.x ? a.y < b.y : a.x < b.x;}

P f[2], h[2];

INL int find(std::vector <ll> &g, int &l)
{
	while(l < g.si - 1 && g[l + 1] - g[l] >= mk) l ++;
	return l;
}

INL void gg(P *f, std::vector <ll> (*g)[2], int (*l)[2])
{
	for(int x=0;x<=1;x++)
	{
		h[x] = f[x];
		f[x] = P(-INF, -INF);
	}
	for(int u=0;u<=1;u++)
	for(int v=0;v<=1;v++)
	{
		int w = find(g[u][v], l[u][v]);
		P e = P(g[u][v][w], w);
		for(int x=0;x<=1;x++)
		{
			P nf = h[x] + e;
			nf.x -= e.y * mk;
			f[v] = std::max(f[v], nf);
			if(x == 1 && u == 1)
			{
				nf.y --, nf.x += mk;
				f[v] = std::max(f[v], nf);
			}
		}
	}
}

INL void ft(int i, int x, int y)
{
	if(y < pl || x > pr)
		return;
	if(x >= pl && y <= pr)
	{
		gg(f, t[i], l[i]);
		return;
	}
	int m = x + y >> 1;
	ft(i0, x, m); 
	ft(i1, m + 1, y);
}

ll ans[N];


int main()
{
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	scanf("%d %d", &n, &Q);
	if((n<=50&&Q<=50)||Q==1)
	{
		build();
	}
	if(!ok&&Q>50)return 0;
	int js = 0;
	for(int i=1;i<=n;i++)
		js += abs(a[i]);
	for(int i=1;i<=Q;i++)
	{
		b[i].x=read(),b[i].y=read(),b[i].k=read();
		L[i] = -35000, R[i] = js / b[i].k;
	}
	while(1)
	{
		for(int i=1;i<=Q;i++)
		{
			m[i] = ((ll) L[i] + R[i]) / 2;
			d[i] = i;
		}
		std::sort(d + 1, d + Q + 1, cmpd);
		memset(l, 0, sizeof l);
		int ok = 0;
		for(int i=1;i<=Q;i++)
		{
			int x = d[i];
			if(L[x] > R[x]) continue;
			ok = 1;
			mk = m[x];
			pl = b[x].x, pr = b[x].y;
			f[0] = P(0, 0); f[1] = P(-INF, INF);
			ft(1, 1, n);
			f[0] = std::max(f[0], f[1]);
			if(f[0].y >= b[x].k)
			{
				as[x] = m[x];
				L[x] = m[x] + 1;
			} 
			else
			{
				R[x] = m[x] - 1;
			}
		}
		if(!ok) break;
	}
	memset(l, 0, sizeof l);
	for(int i=1;i<=Q;i++)
		d[i] = i, m[i] = as[i];
	std::sort(d + 1, d + Q + 1, cmpd);
	for(int i=1;i<=Q;i++)
	{
		int x = d[i];
		mk = as[x];
		pl = b[x].x, pr = b[x].y;
		f[0] = P(0, 0); f[1] = P(-INF, INF);
		ft(1, 1, n);
		f[0] = std::max(f[0], f[1]);
		ans[x] = f[0].x + b[x].k * mk;
	}
	for(int i=1;i<=Q;i++)
		printf("%lld\n", ans[i]);
	return 0;
}

