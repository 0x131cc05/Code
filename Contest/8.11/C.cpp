#include<bits/stdc++.h>
using namespace std;
#define I inline int
#define V inline void
#define P pair<int,int>
#define ll long long int
#define FOR(i,a,b) for(int i=a;i<=b;i++)
const int N=8e5+10,INF=0x3f3f3f3f;
V cmin(int&x,int y){if(y-x>>31)x=y;}
namespace SAM{
    int ch[N][27],fa[N],len[N],tot=1,last=1;
    V cpy(int x,int y){FOR(i,0,26)ch[x][i]=ch[y][i];}
    I ins(int x){
        int p(last),np,q,nq;
        len[np=last=++tot]=len[p]+1;
        while(p&&!ch[p][x])ch[p][x]=np,p=fa[p];
        if(!p)return fa[np]=1,last;
        if(len[q=ch[p][x]]==len[p]+1)return fa[np]=q,last;
        cpy(nq=++tot,q),len[nq]=len[p]+1,fa[nq]=fa[q],fa[q]=fa[np]=nq;
        while(p&&ch[p][x]==q)ch[p][x]=nq,p=fa[p];
        return last;
    }
}
namespace seg{
    ll c[N],d[N];
    I lowbit(int x){return x&-x;}
    V add(int x,int y){for(ll w=x*y;x<N;x+=lowbit(x))c[x]+=y,d[x]+=w;}
    ll ask(int x){
        ll out=0,tmp=0;
        for(int p=x;p;p^=lowbit(p))out+=c[p],tmp+=d[p];
        return out*(x+1)-tmp;
    }
    ll ask(int l,int r){return ask(r)-ask(l-1);}
    V add(int l,int r,int x){add(l,x),add(r+1,-x);}
}
namespace LCT{
    int fa[N],ch[N][2],last[N],tag[N],len[N],val[N];
    I id(int x){return x==ch[fa[x]][1];}
    I nrt(int x){return x==ch[fa[x]][id(x)];}
    V upd(int x){val[x]=len[x];FOR(i,0,1)cmin(val[x],val[ch[x][i]]);}
    V rot(int x){
        int y=fa[x],z=fa[y],p=id(x),w=ch[x][p^1];
        if(nrt(y))ch[z][id(y)]=x;if(w)fa[w]=y;
        fa[y]=x,fa[x]=z,ch[x][p^1]=y,ch[y][p]=w,upd(y),upd(x);
    }
    V add(int x,int w){last[x]=tag[x]=w;}
    V psd(int x){if(tag[x])FOR(i,0,1)add(ch[x][i],tag[x]);tag[x]=0;}
    V psa(int x){if(nrt(x))psa(fa[x]);psd(x);}
    V spl(int x){
        for(psa(x);nrt(x);rot(x))if(nrt(fa[x]))
            rot(id(x)==id(fa[x])?fa[x]:x);
    }
    V acc(int x,int now){
        for(int p=x,y=0;p;p=fa[y=p]){
            spl(p),ch[p][1]=y,upd(p);
            if(last[p])seg::add(last[p]-SAM::len[p]+1,last[p]-val[p]+1,-1);
        }
        spl(x),add(x,now),seg::add(now-SAM::len[x]+1,now,1);
    }
    V init(){
        val[0]=INF;
        FOR(i,1,SAM::tot){
            val[i]=len[i]=SAM::len[fa[i]=SAM::fa[i]]+1;
            tag[i]=ch[i][0]=ch[i][1]=last[i]=0;
        }
    }
}
char a[N];
ll ans[N];
vector<P>q[N];
int T,n,m,l,r,pos[N];
// 感谢模板

int type;

int main() {
    scanf("%d%d%s", &n, &type, a + 1), a[n + 1] = 'a' + 26;
    for (int i = n + 2; i <= n * 2 + 1; i++) a[i] = a[i - n - 1];
    for (int i = 1; i <= n * 2 + 1; i++) pos[i] = SAM::ins(a[i] - 'a');
    LCT::init();
    int m; scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int l, r; scanf("%d%d", &l, &r);
        q[l + n].push_back(P(i, r + 1));
        if (type == 2) q[r].push_back(P(i, l));
        else ans[i] += r - l + 1;
        ans[i] += (ll)(r - l + 1) * (l - 1 + n - r);
        ans[i] -= (ll)(n - r + 1) * l; 
        ans[i] += (ll)(n - r) * (l - 1);
    }
    n = n * 2 + 1;
    for (int i = 1; i <= n; i++) {
        LCT::acc(pos[i], i);
        for (auto x : q[i]) 
            ans[x.first] += seg::ask(x.second, i);
    }
    for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
}

// int main(){
//     scanf("%s%d",a+1,&m),n=strlen(a+1);
//     FOR(i,1,m)scanf("%d%d",&l,&r),q[r].push_back(P(i,l));
//     FOR(i,1,n)pos[i]=SAM::ins(a[i]-'a');
//     LCT::init();
//     FOR(i,1,n){
//         LCT::acc(pos[i],i);
//         for(P x:q[i])ans[x.first]=seg::ask(x.second,i);
//     }
//     FOR(i,1,m)cout<<ans[i]<<'\n';
//     return 0;
// }