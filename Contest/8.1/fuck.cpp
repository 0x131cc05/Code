#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<set>
#include <iostream>
#define ll long long
#define inf 20021225
#define mdn 998244353
#define N 200010
using namespace std;
ll read()
{
	ll s=0,t=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')	t=-1; ch=getchar();}
	while(ch>='0' && ch<='9')	s=s*10+ch-'0',ch=getchar();
	return s*t;
}
set<ll> f[N];
struct edge{int to,lt; ll v;}e[N];
int in[N],cnt,tag[N],n,id[N];
void add(int x,int y,ll v)
{
	e[++cnt].to=y; e[cnt].lt=in[x]; e[cnt].v=v; in[x]=cnt;
	e[++cnt].to=x; e[cnt].lt=in[y]; e[cnt].v=v; in[y]=cnt; 
}
int ksm(int bs,int mi)
{
	int ans=1;
	while(mi)
	{
		if(mi&1)	ans=1ll*ans*bs%mdn;
		bs=1ll*bs*bs%mdn; mi>>=1; 
	}
	return ans;
}
bool cmp(int x,int y)
{
	bool wei=0; int tx=tag[x],ty=tag[y];
	if(f[x].size()<f[y].size()) swap(x,y),swap(tx,ty),wei=1; set<ll>::iterator iy=f[y].end(),ix=f[x].end();
	do
	{
		--iy; --ix;
		if((*ix)+tx>(*iy)+ty)
		{
			if(wei)	swap(x,y);
			return 1^wei;
		}
		else if((*ix)+tx<(*iy)+ty)
		{
			if(wei)	swap(x,y);
			return 0^wei;
		}
	}while(iy!=f[y].begin()); bool gg=f[x].size()>f[y].size();
	return wei^gg;
}
void add(set<ll> &x,ll v)
{
	while(x.lower_bound(v)!=x.end()&&(*x.lower_bound(v))==v)	x.erase(v),v++;
	x.insert(v);
}
void add(int &x,int &y)
{
	if(f[x].size()<f[y].size())	swap(x,y);
	for(set<ll>::iterator iy=f[y].begin();iy!=f[y].end();iy++)
	{
		ll vy=*iy; vy=vy+tag[y]-tag[x]; add(f[x],vy);
	}
}
void dfs(int x,int fr)
{
	int mx=0;
	for(int i=in[x];i;i=e[i].lt)
	{
		int y=e[i].to; if(y==fr)	continue;
		dfs(y,x); add(f[id[y]],(ll)e[i].v-tag[id[y]]); if(!mx||cmp(id[y],id[mx])) mx=y;
	}
	if(mx) id[x]=id[mx], tag[id[x]]++;
	for(int i=in[x];i;i=e[i].lt)
	{
		int y=e[i].to; if(y==fr||y==mx) continue;
		add(id[x],id[y]);
	}
	cout << "mx: " << x << ' ' << mx << endl;
}
int main()
{
	n=read(); id[1]=1;
	for(int i=2;i<=n;i++)
	{
		id[i]=i;
		int x=read(); ll v=read();
		add(i,x,v);
	}
	dfs(1,0); int ans=0;
	for(set<ll>::iterator it=f[id[1]].begin();it!=f[id[1]].end();it++)
		(ans+=ksm(2,((*it)+tag[id[1]])%(mdn-1)))%=mdn;
	printf("%d\n",ans);
	return 0;
}
