#include<bits/stdc++.h>
#define maxn 505
#define inf 1000000007
using namespace std;
typedef long long ll;
ll read()
{
    ll x=0,f=1;
    char ch=getchar();
    while(ch-'0'<0||ch-'0'>9){if(ch=='-') f=-1;ch=getchar();}
    while(ch-'0'>=0&&ch-'0'<=9){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,s,t;
struct P{
    int x,y;
    ll v;
}p[85];
struct X{
    char d;
    int a,b;
}co[325];
int Lx[85],Rx[85],Ly[85],Ry[85];
int head[325],nxt[140010],to[140010],c[140010],tot;
ll v[140010];
void add(int x,int y,int z,ll u)
{
    tot++;
    nxt[tot]=head[x];
    head[x]=tot;
    to[tot]=y;
    c[tot]=z;
    v[tot]=u;
}
void addx(int x,int y,int z,ll u)
{
    add(x,y,z,u);
    add(y,x,0,-u);
}
ll ans,res,dis[325];
int vis[325],pre[325],pre_num[325];
queue<int>q;
int spfa()
{
    for(int i=1;i<=t;i++)  dis[i]=-1e18;
    dis[s]=0;q.push(s);vis[s]=1;
    while(q.size())
    {
        int now=q.front();q.pop();vis[now]=0;
        for(int i=head[now];i;i=nxt[i])
        {
            if(dis[to[i]]<dis[now]+v[i]&&c[i])
            {
                dis[to[i]]=dis[now]+v[i];
                pre[to[i]]=now;
                pre_num[to[i]]=i;
                if(!vis[to[i]])  q.push(to[i]),vis[to[i]]=1;
            }
        }
    }
    if(dis[t]==-1e18)  return 0;
    int di=inf;
    for(int i=t;i!=s;i=pre[i])  di=min(di,c[pre_num[i]]);
    for(int i=t;i!=s;i=pre[i])  c[pre_num[i]]-=di,c[pre_num[i]^1]+=di;
    ans+=dis[t]*di;
    return di;
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++)  p[i].x=read(),p[i].y=read(),p[i].v=read();
    m=read();
    for(int i=1;i<=m;i++)  co[i].d=getchar(),co[i].a=read(),co[i].b=read();
    for(int k=1;k<=n;k++)
    {
        tot=1;memset(head,0,sizeof(head));
        s=2*k+2*n+1;t=s+1;
        for(int i=1;i<=k;i++)  addx(s,i,1,0);
        for(int i=k+2*n+1;i<=2*n+2*k;i++)  addx(i,t,1,0);
        for(int i=k+1;i<=k+n;i++)  addx(i,i+n,1,p[i-k].v);
        for(int i=1;i<=k;i++)  Lx[i]=Ly[i]=0,Rx[i]=Ry[i]=inf;
        for(int i=1;i<=m;i++)
        {
            if(co[i].d=='U')
            {
                for(int j=1;j<=k-co[i].b;j++)  Ry[j]=min(Ry[j],co[i].a-1);
            }
            if(co[i].d=='D')
            {
                for(int j=co[i].b+1;j<=k;j++)  Ly[j]=max(Ly[j],co[i].a+1);
            }
            if(co[i].d=='L')
            {
                for(int j=co[i].b+1;j<=k;j++)  Lx[j]=max(Lx[j],co[i].a+1);
            }
            if(co[i].d=='R')
            {
                for(int j=1;j<=k-co[i].b;j++)  Rx[j]=min(Rx[j],co[i].a-1);
            }
        }
        for(int i=1;i<=k;i++)
          for(int j=1;j<=n;j++)
            if(Lx[i]<=p[j].x&&p[j].x<=Rx[i])  addx(i,k+j,1,0);
        for(int i=1;i<=k;i++)
          for(int j=1;j<=n;j++)
            if(Ly[i]<=p[j].y&&p[j].y<=Ry[i])  addx(k+n+j,k+2*n+i,1,0);
        ans=0;
        while(spfa()){};
        res=max(res,ans);   
    }
    cout<<res<<endl;
    return 0;
}
