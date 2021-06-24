#include<bits/stdc++.h>
using namespace std;

const int maxn=1005;
const int maxm=5005;
const int maxb=10;
int n,m,tot;
int par[maxn],pare[maxn],dep[maxn];
int u[maxm],v[maxm],w[maxm],dp[maxn][1<<maxb];
vector<int>edge[maxn],vec[maxn];

void ckmax(int &a,int b){
    if(b>a)a=b;
}

void predfs(int x,int p,int pe,int d){
    par[x]=p;
    pare[x]=pe;
    dep[x]=d;
    for(int i=0;i<int(edge[x].size());i++)
        if(edge[x][i]==p){
        	edge[x].erase(edge[x].begin()+i);
        	break; 
		}
    for(int i=0;i<int(edge[x].size());i++){
        int y=edge[x][i];
        predfs(y,x,i,d+1);
    }
}
int lca(int x,int y){
    while(dep[x]>dep[y])x=par[x];
    while(dep[y]>dep[x])y=par[y];
    while(x!=y)x=par[x],y=par[y];
    return x;
}
void dfs(int x){
    int sz=int(edge[x].size());
    for(int i=0;i<sz;i++)
        dfs(edge[x][i]);
    for(int mask=0;mask<(1<<sz);mask++){
    	for(int i=0;i<sz;i++)if(!((mask>>i)&1))
    		dp[x][mask]+=dp[edge[x][i]][0];
	}
    for(int i=0;i<int(vec[x].size());i++){
        int j=vec[x][i];
        int nmask=0,cur=w[j];
        if(u[j]!=x){
            cur+=dp[u[j]][0];
            int k=u[j];
            for(;par[k]!=x;k=par[k])
                cur+=dp[par[k]][1<<pare[k]];
            nmask|=1<<pare[k];
        }
        if(v[j]!=x){
            cur+=dp[v[j]][0];
            int k=v[j];
            for(;par[k]!=x;k=par[k])
                cur+=dp[par[k]][1<<pare[k]];
            nmask|=1<<pare[k];
        }
        for(int mask=0;mask<(1<<sz);mask++)if((mask&nmask)==nmask)
            ckmax(dp[x][mask^nmask],dp[x][mask]+cur);
    }
}

int main(){
    freopen("training.in","r",stdin);
    freopen("training.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u[i],&v[i],&w[i]);
        if(!w[i])
            edge[u[i]].push_back(v[i]),edge[v[i]].push_back(u[i]);
        tot+=w[i];
    }
    predfs(1,0,0,0);
    for(int i=1;i<=m;i++)if(w[i]){
        if((dep[u[i]]+dep[v[i]])&1)continue;
        vec[lca(u[i],v[i])].push_back(i);
    }
    dfs(1);
    printf("%d\n",tot-dp[1][0]);
    return 0;
}
