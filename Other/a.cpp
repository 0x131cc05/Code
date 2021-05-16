#include<bits/stdc++.h>
using namespace std;
#define maxn 110
#define maxm 10010
#define maxs 1000010
template <typename T>inline T read()
{
    register T sum=0;
    register char cc=getchar();
    int sym=1;
    while(cc!='-'&&(cc>'9'||cc<'0'))cc=getchar();
    if(cc=='-')sym=-1,cc=getchar();
    sum=sum*10+cc-'0';
    cc=getchar();
    while(cc>='0'&&cc<='9')sum=sum*10+cc-'0',cc=getchar();
    return sym*sum;
}
template <typename T>inline T read(T &a)
{
    a=read<T>();
    return a;
}
template <typename T,typename... Others> inline void read(T& a, Others&... b)
{
    a=read(a);
	read(b...);
}
struct Edge
{
	int u,v,w;
	bool operator < (const Edge &o)
	const{
		return w<o.w;
	}
};
int n,m,Q,r[maxn][maxm],d[maxn][maxm],fa[maxs],book[maxs];
long long pres[maxm],sufs[maxm];
vector<Edge>pre[maxm],suf[maxm];
unsigned int SA, SB, SC;
int lim;
int getweight()
{
	SA ^= SA << 16;
	SA ^= SA >> 5;
	SA ^= SA << 1;
	unsigned int t = SA;
	SA = SB;
	SB = SC;
	SC ^= t ^ SA;
	return SC % lim + 1;
}
void gen()
{
	read(n,m,SA,SB,SC,lim);
	int i, j;
	for(i = 1; i <= n; i++)
		for(j = 1; j <= m; j++)
			r[i][j]=getweight();
	for(i = 1; i < n; i++)
		for(j = 1; j <= m; j++)
			d[i][j]=getweight();
}
int find(int x)
{
	return fa[x]==x? x:fa[x]=find(fa[x]);
}
void solve(vector<Edge> &a,vector<Edge> &b,long long &del)
{
	sort(a.begin(),a.end());
	b.clear();
	del=0;
	for(auto i:a)
	{
		int fx=find(i.u),fy=find(i.v);
		if(fx==fy)
			del+=i.w;
		else
		{
			if(book[fx]&&book[fy])
			{
				fa[fy]=fx;
				b.push_back({fx,fy,i.w});
			}
			else if(book[fx])
				fa[fy]=fx;
			else
				fa[fx]=fy;
		}
	}
}
int id(int x,int y)
{
	return (x-1)*m+y;
}
void reset(int x,int y)
{
	fa[x]=x;
	book[x]=y;
}
void init_pre()
{
	vector<Edge>a,b;
	long long del;
	for(int i=1;i<=n*m;i++)	
		fa[i]=i,book[i]=0;
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			reset(id(j,1),1);
			reset(id(j,i),1);
			if(i>2)
				reset(id(j,i-1),0);
		}
		a=pre[i-1];
		pres[i]=pres[i-1];
		for(int j=1;j<=n;j++)
		{
			if(i!=1)
			{
				a.push_back({id(j,i-1),id(j,i),r[j][i-1]});
				pres[i]+=r[j][i-1];
			}
			if(j!=n)
			{
				a.push_back({id(j,i),id(j+1,i),d[j][i]});
				pres[i]+=d[j][i];
			}
		}
		solve(a,b,del);
		pre[i]=b;
		pres[i]-=del;
	}
}
void init_suf()
{
	vector<Edge>a,b;
	long long del;
	for(int i=1;i<=n*m;i++)	
		fa[i]=i,book[i]=0;
	for(int i=m;i>=1;i--)
	{
		for(int j=1;j<=n;j++)
		{
			reset(id(j,m),1);
			reset(id(j,i),1);
			if(i<m-1)
				reset(id(j,i+1),0);
		}
		a=suf[i+1];
		sufs[i]=sufs[i+1];
		for(int j=1;j<=n;j++)
		{
			if(i!=m)
			{
				a.push_back({id(j,i+1),id(j,i),r[j][i]});
				sufs[i]+=r[j][i];
			}
			if(j!=n)
			{
				a.push_back({id(j,i),id(j+1,i),d[j][i]});
				sufs[i]+=d[j][i];
			}
		}
		solve(a,b,del);
		suf[i]=b;
		sufs[i]-=del;
	}
}
int main()
{
	gen();
	init_pre();
	init_suf();
	read(Q);
	for(int i=1;i<=n*m;i++)
		fa[i]=i,book[i]=0;
	for(int cas=1;cas<=Q;cas++)
	{
		static vector<Edge>a,b;
		int l,r;
		read(l,r);
		long long ans=pres[l-1]+sufs[r+1];
		a=pre[l-1];
		a.insert(a.end(),suf[r+1].begin(),suf[r+1].end());
		for(int i=1;i<=n;i++)
		{
			ans+=::r[i][m];
			a.push_back({id(i,m),id(i,1),::r[i][m]});
			reset(id(i,1),0);
			reset(id(i,m),0);
			reset(id(i,l-1),0);
			reset(id(i,r+1),0);
		}
		long long del;
		solve(a,b,del);
		ans-=del;
		printf("%lld\n",ans);
	}
    return 0;
}
