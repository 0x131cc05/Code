#include<bits/stdc++.h>

#define INL inline
#define ll long long
#define ull unsigned long long
#define max(a,b) (a>b?a:b)
#define pb push_back
#define maxn 1010
#define maxm 5010
#define fa(i) (p[i][0])

INL int read()
{
	int x=0,w=1;char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
	if(ch=='-')ch=getchar(),w=-1;
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();
	return x*w;
}
struct Edge
{
	int to,next;
	Edge(int a=0,int b=0)
	{
		to=a,next=b;
	}
}l[maxn<<1];
struct Brid
{
	int from,to,val;
	Brid(int a=0,int b=0,int c=0)
	{
		from=a,to=b,val=c;
	}
}H[maxm];
int head[maxn],p[maxn][12],cnt,n,m;
int dep[maxn],f[maxn][maxn<<2];
int id[maxn],rid[maxn],tot,sum;
std::vector<int>B[maxn];
void Add(int a=0,int b=0)
{
	l[++cnt]=Edge(b,head[a]);
	head[a]=cnt;
}
void Dfs(int u,int fa)
{
	dep[u]=dep[fa]+1;
	p[u][0]=fa;
	for(int i=1;i<12;i++)
	p[u][i]=p[p[u][i-1]][i-1];
	for(int i=head[u];i;i=l[i].next)
	{
		int v=l[i].to;if (v!=fa) Dfs(v,u);
	}
}
int Lca(int a,int b)
{
	if(dep[b]<dep[a]) std::swap(a,b);
	for(int i=11;~i;i--)
		if(dep[p[b][i]]>=dep[a]) b=p[b][i];
	if(a==b) return a;
	for(int i=11;~i;i--)
		if (p[a][i]!=p[b][i])
		a=p[a][i],b=p[b][i];
	return p[a][0];
}
void Solve(int u)
{
	int son=0;
	for(int i=head[u];i;i=l[i].next)
	{
		int v=l[i].to;
		if (v==fa(u)) continue;
		Solve(v);
	}
	for(int i=head[u];i;i=l[i].next)
	{
		int v=l[i].to;
		if (v==fa(u)) continue;
		id[son]=v,rid[v]=1<<son,son++;
	}
	for(int S=0,tem=0;S<1<<son;++S,tem=0)
	{
		for (register int i=0;i<son;i++)
			if (!(S>>i&1))
			tem+=f[id[i]][0];
		f[u][S]=tem;
	}
	for(int k=B[u].size()-1;~k;--k)
	{
		int i=B[u][k],tem=H[i].val;
		if (H[i].from!=u)
		tem+=f[H[i].from][0];
		if (H[i].to!=u)
		tem+=f[H[i].to][0];
		int a=0,b=0;
		if (H[i].from!=u)
			for (a=H[i].from;fa(a)!=u;a=fa(a))
			tem+=f[fa(a)][rid[a]];
		if (H[i].to!=u)
			for (b=H[i].to;fa(b)!=u;b=fa(b))
			tem+=f[fa(b)][rid[b]];
		for (int S=0;S<1<<son;++S)
			if ((S&rid[a])==0&&(S&rid[b])==0)
			f[u][S]=max(f[u][S],f[u][S|rid[a]|rid[b]]+tem);
	}
}
int main(){
	freopen("training.in","r",stdin);
	freopen("training.out","w",stdout);
	n=read(),m=read();
	for (int i=1,a,b,c;i<=m;++i)
	{
		a=read(),b=read(),c=read();
		if(!c) Add(a,b),Add(b,a);
		else H[++tot]=Brid(a,b,c),sum+=c;
	}
	Dfs(1,0);
	for (int i=1;i<=tot;++i)
	{
		int t=Lca(H[i].from,H[i].to);
		if (!((dep[H[i].from]+dep[H[i].to]-2*dep[t])&1))
		B[t].pb(i);
	}
	Solve(1);
	printf("%d",sum-f[1][0]);
	return 0;
}
