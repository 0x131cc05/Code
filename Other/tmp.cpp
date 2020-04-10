#include<bits/stdc++.h>
using namespace std;
const int M=1000000007,P=998244353;
const int N=500005,E=262144;
#define inf 2147483647
int n,m,i,q,l1,l2,len,x[N],y,k,p,u,v,j;
int st[N],tp,dep[N],fa[20][N],head[N],Next[N*2],adj[N*2],leng[N*2];
int a[N],b[N],c[N],dp[N],num[N],dis[N],tot,d[N],dfn[N];
void dfs(int i,int f)
{
	int j;
	fa[0][i]=f;
	dfn[i]=++k;
	for(j=head[i];j!=0;j=Next[j])
		if(adj[j]!=f)
		{
			dep[adj[j]]=dep[i]+1;
			dfs(adj[j],i);
		}
}
int lca(int x,int y)
{
	int i;
	if(dep[x]<dep[y])
		swap(x,y);
	for(i=19;i>=0;--i)
		if(dep[fa[i][x]]>=dep[y])
			x=fa[i][x];
	for(i=19;i>=0;--i)
		if(fa[i][x]!=fa[i][y])
			x=fa[i][x],y=fa[i][y];
	return (x==y?x:fa[0][x]);
}
void Push(int u,int v)
{
	Next[++k]=head[u];
	head[u]=k;
	adj[k]=v;
}
void add(int u,int v,int w)
{
	Next[++k]=head[u];
	head[u]=k;
	adj[k]=v;
	leng[k]=w;
}
inline void ins(int x)
{
	if(st[tp]==x)
		return;
    if (tp==0)
    {
        st[tp=1]=x;
        num[++tot]=x;
        return;
    }
    int ance=lca(st[tp],x);
    while ((tp>1)&&(dep[ance]<dep[st[tp-1]]))
    {
        add(st[tp-1],st[tp],dep[st[tp]]-dep[st[tp-1]]);
        --tp;
    }
    if (dep[ance]<dep[st[tp]]) add(ance,st[tp],dep[st[tp]]-dep[ance]),--tp;
    if ((!tp)||(st[tp]!=ance)) st[++tp]=ance,num[++tot]=ance;
    st[++tp]=x,num[++tot]=x;
}
bool cmp(int a,int b)
{
	return dfn[a]<dfn[b];
}
void dfs2(int i)
{
	int j;
	for(j=head[i];j!=0;j=Next[j])
	{
		dfs2(adj[j]);
		int di=dis[adj[j]]+leng[j];
		if((di+d[dp[adj[j]]]-1)/d[dp[adj[j]]]<(dis[i]+d[dp[i]]-1)/d[dp[i]]
			||(((di+d[dp[adj[j]]]-1)/d[dp[adj[j]]]==(dis[i]+d[dp[i]]-1)/d[dp[i]])&&dp[adj[j]]<dp[i]))
		{
			dp[i]=dp[adj[j]];
			dis[i]=di;
		}
	}
}
void dfs3(int i,int f)
{
	int j;
	for(j=head[i];j!=0;j=Next[j])
	{
		int di=dis[i]+leng[j];
		if((dis[adj[j]]+d[dp[adj[j]]]-1)/d[dp[adj[j]]]>(di+d[dp[i]]-1)/d[dp[i]]
			||((dis[adj[j]]+d[dp[adj[j]]]-1)/d[dp[adj[j]]]==(di+d[dp[i]]-1)/d[dp[i]]&&dp[adj[j]]>dp[i]))
		{
			dp[adj[j]]=dp[i];
			dis[adj[j]]=di;
		}
		dfs3(adj[j],i);
	}
}
int main()
{
	scanf("%d",&n);
	for(i=1;i<n;++i)
	{
		scanf("%d %d",&u,&v);
		Push(u,v);
		Push(v,u);
	}
	dep[1]=1;
	k=0;
	dfs(1,0);
	for(i=1;i<20;++i)
		for(j=1;j<=n;++j)
			fa[i][j]=fa[i-1][fa[i-1][j]];
	scanf("%d",&q);
	memset(head,0,sizeof(head));
	d[0]=1;
	for(i=1;i<=n;++i)
		dis[i]=1<<30;
	while(q--)
	{
		y=k=0;
		scanf("%d %d",&m,&p);
		for(i=1;i<=m;++i)
		{
			scanf("%d %d",&a[i],&d[i]);
			c[++y]=a[i];
			dp[a[i]]=i;
			dis[a[i]]=0;
		}
		for(i=1;i<=p;++i)
		{
			scanf("%d",&b[i]);
			c[++y]=b[i];
		}
		c[++y]=1;
		sort(c+1,c+1+y,cmp);
		for(i=1;i<=y;++i)
			ins(c[i]);
		if(tp)while(--tp)add(st[tp],st[tp+1],dep[st[tp+1]]-dep[st[tp]]);
		dfs2(1);
		dfs3(1,0);
		for(i=1;i<=p;++i)
			printf("%d ",dp[b[i]]);
		printf("\n");
		for(i=1;i<=tot;++i)
		{
			head[num[i]]=dp[num[i]]=0;
			dis[num[i]]=1<<30;
		}
		tot=0;
	}
}
