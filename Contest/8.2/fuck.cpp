#include<bits/stdc++.h>
#define re register
struct eg{int to,c;eg*nx;}e[100010],*la[50010],*cnt=e;
inline void addE(re int a,re int b,re int c)
{
	*++cnt=(eg){b,c,la[a]};la[a]=cnt;
	*++cnt=(eg){a,c,la[b]};la[b]=cnt;
}
int ans[50010],n,m;
std::vector<int>to[50010];
int sz[50010],hv[50010],szt[50010],fa[50010],dfn[50010],top[50010],tt[50010],tot;
const int N=65536;
int mi[2*N],tg[2*N];
void pu(re int i){mi[i]=std::min(mi[2*i],mi[2*i+1])+tg[i];}
void ad(re int i,re int c){mi[i]+=c;tg[i]+=c;}
void mdf(re int l,re int r,re int c)
{
	//printf("***%d %d %d\n",l,r,c);
	for(l+=N-1,r+=N+1;;)
	{
		if(!(l&1))ad(l^1,c);
		if(r&1)ad(r^1,c);
		l/=2;r/=2;pu(l);pu(r);
		if(l==(r^1))
		{
			for(l/=2;l;l/=2)pu(l);
			return;
		}
	}
}
void mdd(re int a,re int c)
{
	for(;a>1;a=fa[top[a]])
	{
		//printf("******%d %d %d\n",a,top[a],dfn[a]);
		mdf(dfn[top[a]],dfn[a],c);
	}
}
void dfs(re int a)
{
	sz[a]=1;szt[a]=to[a].size();
	for(re eg*i=la[a];i;i=i->nx)if(i->to!=fa[a])
	{
		tt[i->to]=i->c;fa[i->to]=a;dfs(i->to);sz[a]+=sz[i->to];szt[a]+=szt[i->to];
		if(sz[hv[a]]<sz[i->to])hv[a]=i->to;
	}
}
void dfs1(re int a)
{
	dfn[a]=tot++;
	if(hv[a]){top[hv[a]]=top[a];dfs1(hv[a]);}
	for(re eg*i=la[a];i;i=i->nx)if(i->to!=fa[a]&&i->to!=hv[a])
	{
		top[i->to]=i->to;dfs1(i->to);
	}
}
void dec(re int a)
{
	for(auto x:to[a])
	{
		mdd(x,2);
	}
	if(!to[a].empty())mdd(a,2*to[a].size());
	for(re eg*i=la[a];i;i=i->nx)if(i->to!=fa[a]&&i->to!=1)
	{
		dec(i->to);
	}
}
void adc(re int a)
{
	for(auto x:to[a])
	{
		mdd(x,-2);
	}
	if(!to[a].empty())mdd(a,-2*to[a].size());
	for(re eg*i=la[a];i;i=i->nx)if(i->to!=fa[a]&&i->to!=1)
	{
		adc(i->to);
	}
}
void dfss(re int a)
{
	if(a!=1)
	{
		mdf(dfn[a],dfn[a],1<<30);
		//printf("***%d %d %d %d\n",a,tt[a],szt[a],mi[1]);
		ans[tt[a]]=szt[a]+mi[1]+2;
		mdf(dfn[a],dfn[a],-1<<30);
	}
	for(re eg*i=la[a];i;i=i->nx)if(i->to!=fa[a]&&i->to!=hv[a]&&i->to!=1)
	{
		dec(i->to);
	}
	for(auto x:to[a])
	{
		mdd(x,2);
	}
	if(!to[a].empty())mdd(a,2*to[a].size());
	if(hv[a])dfss(hv[a]);
	for(re eg*i=la[a];i;i=i->nx)if(i->to!=fa[a]&&i->to!=hv[a]&&i->to!=1)
	{
		adc(i->to);
		dfss(i->to);
	}
}
int main()
{
	re int n,m,x,y;
	scanf("%d%d",&n,&m);
	for(re int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);addE(x,y,i);
	}
	for(re int i=1;i<=m-n+1;i++)
	{
		scanf("%d%d",&x,&y);to[x].push_back(y);to[y].push_back(x);
	}
	dfs(1);top[1]=hv[1];dfs1(1);
	for(re int i=2;i<=n;i++)if(fa[i]==1)
	{
		fa[i]=0;
	}
	for(re int i=2;i<=n;i++)mi[N+dfn[i]]=szt[i];
	mi[N]=1<<30;for(re int i=n;i<N;i++)mi[N+i]=1<<30;
	for(re int i=N-1;i;i--)pu(i);
	for(re eg*i=la[1];i;i=i->nx)
	{
		adc(i->to);dfss(i->to);
	}
	for(re int i=1;i<n;i++)printf("%d ",ans[i]);
}
