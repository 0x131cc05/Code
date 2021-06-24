//Orz lsj
//lsj ak ioi
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define N 1050
int n,m,s[N*5][3],f[N][12],dep[N],head[N],cnt;
struct edge{int t,next;}ed[N*2];
void adde(int f,int t){ed[++cnt]=(edge){t,head[f]};head[f]=cnt;ed[++cnt]=(edge){f,head[t]};head[t]=cnt;}
void dfs0(int u,int fa)
{
	f[u][0]=fa;dep[u]=dep[fa]+1;
	for(int i=1;i<=11;i++)f[u][i]=f[f[u][i-1]][i-1];
	for(int i=head[u];i;i=ed[i].next)if(ed[i].t!=fa)dfs0(ed[i].t,u);
}
int LCA(int x,int y){if(dep[x]<dep[y])x^=y^=x^=y;for(int i=11;i>=0;i--)if(dep[x]-dep[y]>=1<<i)x=f[x][i];if(x==y)return x;for(int i=11;i>=0;i--)if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];return f[x][0];}
int su,dp[N],vl[N],fu[N],id[N];
vector<int> sn[N],tp[N];
void dfs1(int u,int fa)
{
	int ct=0;
	sn[u].push_back(u);
	for(int i=head[u];i;i=ed[i].next)if(ed[i].t!=fa)
	{
		dfs1(ed[i].t,u);id[ed[i].t]=++ct;
		for(int j=0;j<sn[ed[i].t].size();j++)sn[u].push_back(sn[ed[i].t][j]);
		dp[u]+=dp[ed[i].t];
	}
	for(int i=0;i<1<<ct;i++)fu[i]=0;
	for(int i=0;i<tp[u].size();i++)
	{
		int st=tp[u][i];
		int s1=s[st][0],s2=s[st][1],v1=s[st][2]+vl[s1]+vl[s2];
		for(int j=11;j>=0;j--)
		{
			if(dep[s1]-dep[u]>1<<j)s1=f[s1][j];
			if(dep[s2]-dep[u]>1<<j)s2=f[s2][j];
		}
		int f1=0;
		if(id[s1])f1|=1<<id[s1]-1;if(id[s2])f1|=1<<id[s2]-1;
		fu[f1]=max(fu[f1],v1);
	}
	for(int i=1;i<1<<ct;i++)
	{
		for(int j=1;j<=ct;j++)if(i&(1<<j-1))fu[i]=max(fu[i],fu[i^(1<<j-1)]+fu[1<<j-1]);
		for(int j=1;j<=ct;j++)if(i&(1<<j-1))
		for(int k=j+1;k<=ct;k++)if(i&(1<<k-1))fu[i]=max(fu[i],fu[i^(1<<j-1)^(1<<k-1)]+fu[(1<<j-1)^(1<<k-1)]);
	}
	dp[u]+=fu[(1<<ct)-1];
	for(int i=head[u];i;i=ed[i].next)if(ed[i].t!=fa)
	for(int j=0;j<sn[ed[i].t].size();j++)vl[sn[ed[i].t][j]]+=fu[((1<<ct)-1)^(1<<id[ed[i].t]-1)]-fu[(1<<ct)-1];
}
int main()
{
	freopen("training.in","r",stdin);
	freopen("training.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&s[i][0],&s[i][1],&s[i][2]);su+=s[i][2];
		if(!s[i][2])adde(s[i][0],s[i][1]);
	}
	dfs0(1,0);
	for(int i=1;i<=m;i++)if(s[i][2])
	{
		if((dep[s[i][0]]^dep[s[i][1]])&1)continue;
		tp[LCA(s[i][0],s[i][1])].push_back(i);
	}
	dfs1(1,0);printf("%d\n",su-dp[1]);
}
