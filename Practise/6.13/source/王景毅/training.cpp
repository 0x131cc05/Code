#include<bits/stdc++.h>
using namespace std;
const int N=2005;
int n,m,t,dp[N][N],c[N][12],dep[N],lca[N][N],fa[N],jp[N],s[N],w[N],ru[N*3],rv[N*3],rw[N*3];
vector<int>e[N],q[N];
void dfs1(int u)
{
	int p=-1;
	for(int i=0;i<e[u].size();i++)
	{
		int v=e[u][i];
		if(!dep[v])
		{
			dep[v]=dep[u]+1;
			fa[v]=u;
			dfs1(v);
		}
	}
}
void dfs2(int r,int u,int f,int l)
{
	if(dep[u]<dep[l])
		l=u;
	lca[r][u]=l;
	for(auto v:e[u])
		if(v!=f)
			dfs2(r,v,u,l);
}
void dfs3(int u,int f,int s)
{
	jp[u]=f,w[u]=s+c[u][10];
	for(int i=0;i<e[u].size();i++)
		dfs3(e[u][i],f,s+c[u][i]);
}
void dfs4(int u)
{
	for(auto v:e[u])
		dfs4(v);
	int m=e[u].size();
	for(int i=1;i<=n;i++)
		jp[i]=-1,w[i]=0;
	for(int i=0;i<m;i++)
		dfs3(e[u][i],i,0);
	for(auto d:q[u])
	{
		for(int s=0;s<(1<<m);s++)
		{
			int x=ru[d],y=rv[d];
			if(x!=u&&(s>>jp[x]&1))
				continue;
			if(y!=u&&(s>>jp[y]&1))
				continue;
			int ns=s;
			if(x!=u)
				ns|=(1<<jp[x]);
			if(y!=u)
				ns|=(1<<jp[y]);
			dp[u][ns]=max(dp[u][ns],dp[u][s]+rw[d]+w[x]+w[y]);
		}
	}
	for(int s=0;s<(1<<m);s++)
	{
		for(int i=0;i<m;i++)
			if(!(s>>i&1))
				dp[u][s]+=c[e[u][i]][10];
		c[u][10]=max(c[u][10],dp[u][s]);
		for(int i=0;i<m;i++)
			if(!(s>>i&1))
				c[u][i]=max(c[u][i],dp[u][s]-c[e[u][i]][10]);
	}
}
int main()
{
	freopen("training.in","r",stdin);
	freopen("training.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		if(!w)
		{
			e[u].push_back(v);
			e[v].push_back(u);
		}
		t+=w;
		ru[i]=u,rv[i]=v,rw[i]=w;
	}
	dep[1]=1;
	dfs1(1);
	for(int i=1;i<=n;i++)
		dfs2(i,i,i,i);
	for(int u=1;u<=n;u++)
	{
		for(int i=0;i<e[u].size();i++)
		{
			if(e[u][i]==fa[u])
			{
				e[u].erase(e[u].begin()+i);
				break;
			}
		}
	}
	for(int i=1;i<=m;i++)
		if(rw[i]&&(dep[ru[i]]%2==dep[rv[i]]%2))
			q[lca[ru[i]][rv[i]]].push_back(i);
	dfs4(1);
	printf("%d\n",t-c[1][10]);
	return 0;
}