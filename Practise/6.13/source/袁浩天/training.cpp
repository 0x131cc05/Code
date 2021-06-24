#include<bits/stdc++.h>
#define LL long long
#define mp make_pair
#define pb push_back
#define pii pair<int,int>
using namespace std;
inline int read(){
    int v=0,f=1;
    char c=getchar();
    while (c<'0' || c>'9'){
        if (c=='-') f=-1;
        c=getchar();
    }
    while (c>='0' && c<='9'){
        v=v*10+c-'0';
        c=getchar();
    }
    return v*f;
}
const int Maxn=1005;
int n,m,par[Maxn],st[Maxn],ed[Maxn],kc,dep[Maxn],O[Maxn];
int eu[Maxn],ev[Maxn],ew[Maxn],ke;
int dp[Maxn][Maxn];
vector<int> G[Maxn],P[Maxn],Son[Maxn],M[Maxn],WW[Maxn];
void dfs(int x,int p){
    par[x]=p;st[x]=++kc;O[kc]=x;
    for (int i=0;i<G[x].size();i++){
        int v=G[x][i];
        if (v!=p){
            Son[x].pb(v);
            dep[v]=dep[x]+1;
            dfs(v,x);
        }
    }
    ed[x]=kc;
}
bool ispar(int u,int v){
    return st[u]<=st[v] && ed[v]<=ed[u];
}
int lca(int u,int v){
    while (!ispar(u,v)) u=par[u];
    return u;
}
int ddp[1024];
void Ckmax(int &x,int y){
    if (y>x) x=y;
}
void dfs2(int x){
    for (int i=0;i<Son[x].size();i++) dfs2(Son[x][i]);
    
    if (Son[x].empty()){
        return;
    }
    //cerr<<x<<endl;
    int N=Son[x].size();
    for (int i=0;i<P[x].size();i++){
        int U=eu[P[x][i]],V=ev[P[x][i]];
        int mask=0,W=ew[P[x][i]];
        for (int j=0;j<N;j++){
            if (ispar(Son[x][j],U)){
                mask|=1<<j;W+=dp[Son[x][j]][U];
            }
            if (ispar(Son[x][j],V)){
                mask|=1<<j;W+=dp[Son[x][j]][V];
            }
        }
        //cerr<<"FK"<<W<<' '<<mask<<endl;
        M[x].pb(mask);WW[x].pb(W);
    }
    for (int i=-1;i<(int)Son[x].size();i++){
        //cerr<<"MX"<<i<<endl;
        for (int j=0;j<(1<<N);j++) ddp[j]=-1e9;
        
        if (i==-1) ddp[0]=0;
        else ddp[1<<i]=0;
        
        for (int j=0;j<P[x].size();j++){
            for (int msk=0;msk<(1<<N);msk++){
                if ((msk&M[x][j])==M[x][j]){
                    Ckmax(ddp[msk],ddp[msk^M[x][j]]+WW[x][j]);
                }
            }
        }
        
        int AMX=0;
        
        for (int j=0;j<(1<<N);j++){
            int tmp=ddp[j];
            for (int k=0;k<N;k++){
                if(j>>k&1) continue;
                tmp+=dp[Son[x][k]][Son[x][k]];
            }
            Ckmax(AMX,tmp);
        }
        //cerr<<"AMX"<<i<<' '<<AMX<<endl;
        if (i==-1){
            dp[x][x]=AMX;
            continue;
        }
        
        int lo=st[Son[x][i]],hi=ed[Son[x][i]];
        for (int j=lo;j<=hi;j++){
            dp[x][O[j]]=AMX+dp[Son[x][i]][O[j]];
        }
    }
}
int main(){
    freopen("training.in","r",stdin);
    freopen("training.out","w",stdout);
    n=read();m=read();
    int tot=0;
    for (int i=0;i<m;i++){
        int u,v,w;
        u=read();v=read();w=read();
        if (!w){
            G[u].pb(v);G[v].pb(u);
        }
        else{
            eu[ke]=u;ev[ke]=v;ew[ke]=w;
            tot+=w;
            ke++;
        }
    }
    dfs(1,-1);
    for (int i=0;i<ke;i++){
        int l=lca(eu[i],ev[i]);
        if ((dep[eu[i]]+dep[ev[i]]-dep[l]*2)&1){
            continue;
        }
        //cerr<<i<<' '<<l<<endl;
        P[l].pb(i);
    }
    
    dfs2(1);
    
    printf("%d\n",tot-dp[1][1]);
    return 0;
}
