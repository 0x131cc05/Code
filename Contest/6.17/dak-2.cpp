#include<cstdio>
#include<algorithm>
#include<map>
#include<queue>
#define ll long long
using namespace std;
#define N 200500
map<int,int> id[N];
struct edge{int t,next,v;}ed[N*2];
int n,q,t,s,head[N],cnt,a,b,c,d,dis[N],qu[N],ct1,sb[N],ct2,ds[N][22],mn[N][22],v3[N][22],f1[N],dep[N],sz[N],vis[N],vl1,as1,as2,ls[N];
long long as[N],fu[N][4];
void adde(int f,int t,int v){ed[++cnt]=(edge){t,head[f],v};head[f]=cnt;ed[++cnt]=(edge){f,head[t],v};head[t]=cnt;}
bool cmp(int a,int b){return fu[a][1]==fu[b][1]?fu[a][2]==fu[b][2]?a>b:fu[a][2]<fu[b][2]:fu[a][1]<fu[b][1];}
void dfs1(int u,int fa)
{
	sz[u]=1;int mx=0;
	for(int i=head[u];i;i=ed[i].next)if(ed[i].t!=fa&&!vis[ed[i].t])dfs1(ed[i].t,u),sz[u]+=sz[ed[i].t],mx=mx<sz[ed[i].t]?sz[ed[i].t]:mx;
	if(mx<vl1-sz[u])mx=vl1-sz[u];
	if(as1>mx)as1=mx,as2=u;
}
void dfs2(int u,int fa,int d,int di,int mi,int v)
{
	di++,mi=min(mi,dis[u]);
	ds[u][d]=di;mn[u][d]=mi;v3[u][d]=v;
	for(int i=head[u];i;i=ed[i].next)if(ed[i].t!=fa&&!vis[ed[i].t])dfs2(ed[i].t,u,d,di,mi,v+ed[i].v);
}
void dfs3(int u,int d)
{
	vis[u]=1;dep[u]=d;
	dfs2(u,0,d,-1,1e9,0);
	for(int i=head[u];i;i=ed[i].next)if(!vis[ed[i].t]){dfs1(ed[i].t,u);vl1=sz[ed[i].t];as1=1e9;dfs1(ed[i].t,u);f1[as2]=u;dfs3(as2,d+1);}
}
#define M 12330000
int ch[M][2],fa[M],ct;
ll vl[M],v[M],mx[M];
struct Splay{
	int rt;
	void init(){rt=++ct;ch[ct][1]=ct+1;fa[ct+1]=ct;ct++;vl[ct]=1e18;v[ct]=v[ct-1]=mx[ct]=mx[ct-1]=-1e18;vl[ct-1]=-1e18;}
	void pushup(int x){mx[x]=max(v[x],max(mx[ch[x][0]],mx[ch[x][1]]));}
	void rotate(int x){int f=fa[x],g=fa[f],tp=ch[f][1]==x;ch[g][ch[g][1]==f]=x;fa[x]=g;ch[f][tp]=ch[x][!tp];fa[ch[x][!tp]]=f;ch[x][!tp]=f;fa[f]=x;pushup(f);pushup(x);}
	void splay(int x,int y=0){while(fa[x]!=y){int f=fa[x],g=fa[f];if(g!=y)rotate((ch[g][1]==f)^(ch[f][1]==x)?x:f);rotate(x);}if(!y)rt=x;}
	int getpre(int x,ll v){if(!x)return 0;if(vl[x]>v)return getpre(ch[x][0],v);int st=getpre(ch[x][1],v);return st?st:x;}
	void insert(ll v1,ll v2)
	{
		if(v1<0)return;
		int tp=getpre(rt,v1);
		splay(tp);
		if(vl[tp]==v1){v[tp]=max(v[tp],v2);pushup(tp);return;}
		int st=ch[tp][1];
		while(ch[st][0])st=ch[st][0];
		splay(st,tp);
		ch[st][0]=++ct;v[ct]=mx[ct]=v2;fa[ct]=st;vl[ct]=v1;
		pushup(st);pushup(tp);
	}
	ll query(ll st){ll tp=getpre(rt,st-1);splay(tp);return mx[ch[tp][1]];}
}tr[N][5];
int main()
{
	mx[0]=-1e18;
	scanf("%d%d%d%d",&n,&q,&t,&s);
	for(int i=1;i<=n;i++)dis[i]=1e9;
	queue<int> st;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%d",&a,&b,&c),adde(a,b,c);
		if(c)dis[a]=dis[b]=1,st.push(a),st.push(b);
	}
	while(!st.empty())
	{
		int f=st.front();st.pop();
		for(int i=head[f];i;i=ed[i].next)if(dis[ed[i].t]>1e8)dis[ed[i].t]=dis[f]+1,st.push(ed[i].t);
	}
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		if(c||!id[a][b]){fu[++ct2][0]=a;fu[ct2][1]=b;fu[ct2][2]=c+b;fu[ct2][3]=d;if(!c)id[a][b]=ct2;}
		else fu[id[a][b]][3]+=d;
	}
	dfs3(1,1);
	for(int i=1;i<=n;i++)fu[i+ct2][0]=i,ls[i]=i+ct2;
	ct2+=n;
	for(int i=1;i<=ct2;i++)sb[i]=i;
	sort(sb+1,sb+ct2+1,cmp);
	for(int i=ct2;i>=1;i--)
	{
		ll res=fu[sb[i]][3],v1=dis[fu[sb[i]][0]],v2=t-fu[sb[i]][2];
		v2-=v1-1;if(v2<0)v2=0;
		res+=v2*s;
		as[sb[i]]=res;
	}
	for(int i=1;i<=n;i++)for(int j=0;j<5;j++)tr[i][j].init();
	for(int i=ct2;i>=1;i--)
	{
		int tp=sb[i];
		for(int j=fu[tp][0];j;j=f1[j])
		{
			int de=dep[j];
			ll t1=fu[tp][2]+ds[fu[tp][0]][de],v1=mn[fu[tp][0]][de]-1,f1=v3[fu[tp][0]][de];
			ll as1=tr[j][4].query(t1);
			as[tp]=max(as[tp],as1+fu[tp][3]+f1*s);
			ll as2=tr[j][1].query(t1),as3=tr[j][3].query(t1);
			if(t1&1)
			{
				as[tp]=max(as[tp],as2-(t1+1)/2*s*2+f1*s+fu[tp][3]);
				as[tp]=max(as[tp],as3-t1/2*s*2+f1*s+fu[tp][3]);
			}
			else
			{
				as[tp]=max(as[tp],as2-t1/2*s*2+f1*s+fu[tp][3]);
				as[tp]=max(as[tp],as3-t1/2*s*2+f1*s+fu[tp][3]);
			}
			ll as4=tr[j][0].query(t1+v1*2),as5=tr[j][2].query(t1+v1*2);
			if((t1+2*v1)&1)
			{
				as[tp]=max(as[tp],as4-(t1+2*v1+1)/2*s*2+f1*s+fu[tp][3]);
				as[tp]=max(as[tp],as5-(t1+2*v1)/2*s*2+f1*s+fu[tp][3]);
			}
			else
			{
				as[tp]=max(as[tp],as4-(t1+2*v1)/2*s*2+f1*s+fu[tp][3]);
				as[tp]=max(as[tp],as5-(t1+2*v1)/2*s*2+f1*s+fu[tp][3]);
			}
		}
		if(tp<=ct2-n)
		for(int j=fu[tp][0];j;j=f1[j])
		{
			int de=dep[j];
			ll t1=fu[tp][1]-ds[fu[tp][0]][de],v1=mn[fu[tp][0]][de]-1,f1=v3[fu[tp][0]][de];
			tr[j][4].insert(t1,as[tp]+f1*s);
			tr[j][(t1&1)<<1].insert(t1,as[tp]+t1/2*s*2+f1*s);
			tr[j][((t1-2*v1)&1)<<1|1].insert(t1-2*v1,as[tp]+(t1-2*v1)/2*s*2+f1*s);
		}
	}
	for(int i=1;i<=n;i++)printf("%lld ",as[ls[i]]);
}
