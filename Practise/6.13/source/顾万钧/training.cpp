#include<bits/stdc++.h>
#define rb(a,b,c) for(int a=b;a<=c;++a)
#define rl(a,b,c) for(int a=b;a>=c;--a)
#define LL long long
#define IT iterator
#define PB push_back
#define II(a,b) make_pair(a,b)
#define FIR first
#define SEC second
#define FREO freopen("check.out","w",stdout)
#define rep(a,b) for(int a=0;a<b;++a)
#define SRAND mt19937 rng(chrono::steady_clock::now().time_since_epoch().count())
#define random(a) rng()%a
#define ALL(a) a.begin(),a.end()
#define POB pop_back
#define ff fflush(stdout)
#define fastio ios::sync_with_stdio(false)
#define check_min(a,b) a=min(a,b)
#define check_max(a,b) a=max(a,b)
using namespace std;
const int INF=0x3f3f3f3f;
typedef pair<int,int> mp;
const int MAXN=1005;
const int MAXM=10005;
const int MAXD=10;
int n,m,dp[MAXN][MAXM],col[MAXN],fa[MAXN][10],deep[MAXN];
bool precalc[MAXN][MAXN];
vector<int> tree[MAXN];
vector<int> g[MAXN];
map<mp,int> E;
vector<int> dep[MAXN];
int V[MAXM],W[MAXM],L[MAXM],A[MAXM];
void dfs(int now,int pre,int depth=0){
	deep[now]=depth;
	dep[depth].PB(now);
	fa[now][0]=pre;
	rb(i,1,9) fa[now][i]=fa[fa[now][i-1]][i-1];
	for(auto it:tree[now]) if(it!=pre) col[it]=col[now]^1,dfs(it,now,depth+1);
}
int jump(int now,int dd){
	rep(i,10) if((dd>>i)&1) now=fa[now][i];
	return now;
}
int lca(int u,int v){
	if(deep[u]<deep[v]) swap(u,v);
	u=jump(u,deep[u]-deep[v]);
	if(u==v) return u;
	rl(i,9,0) if(fa[u][i]!=fa[v][i]) {u=fa[u][i],v=fa[v][i];}
	return fa[u][0];
}
bool isanc(int u,int v){
	return deep[u]<=deep[v]&&jump(v,deep[v]-deep[u])==u;
}
int cp[1<<MAXD];
int bst[1<<MAXD];
int id[MAXN];
int cnt=0;
void trans(int now){
	vector<int> ch;
	for(auto it:tree[now]) if(it!=fa[now][0]) ch.PB(it);
	if(ch.empty()){
		dp[now][cnt]=0;
		for(auto it:g[now]) dp[now][it]=W[it];
		return ;
	}
	rep(i,ch.size()) id[ch[i]]=i;
	memset(cp,-63,sizeof(cp));
	memset(bst,-63,sizeof(bst));
	bst[0]=0;
	cp[0]=0;
	for(auto it:ch){
		rb(i,0,cnt-1){
			if(dp[it][i]>=0&&L[i]==now&&V[i]!=now){
				int anoc=A[i];
				if(dp[anoc][i^1]>=0){
					assert(W[i]==W[i^1]);
					assert(anoc!=it);
					check_max(cp[(1<<id[it])|(1<<id[anoc])],dp[it][i]+dp[anoc][i^1]-W[i]);
				}
			}
		}
	}
	for(auto it:ch){
		bst[1<<id[it]]=dp[it][cnt];
		rb(i,0,cnt-1){
			if(dp[it][i]>=0&&V[i]==now) check_max(bst[1<<id[it]],dp[it][i]);
		}
	}
	rep(mask,1<<ch.size()) rep(j,ch.size()) if((mask>>j)&1) check_max(bst[mask],bst[mask^(1<<j)]+bst[1<<j]);
	rep(mask,1<<ch.size()) rep(j,ch.size()) if((mask>>j)&1) rep(k,ch.size()) if((mask>>k)&1&&k!=j) check_max(cp[mask],cp[mask^(1<<j)^(1<<k)]+cp[(1<<j)|(1<<k)]);
	rep(mask,1<<ch.size()) for(int smask=mask;;smask=(smask-1)&mask){
		check_max(bst[mask],bst[mask^smask]+cp[smask]);
		if(!smask) break;
	}
	dp[now][cnt]=bst[(1<<ch.size())-1];
	for(auto it:g[now]) if(L[it]!=now) check_max(dp[now][it],dp[now][cnt]+W[it]);
	for(auto it:ch){
		rb(i,0,cnt-1){
			if(dp[it][i]>=0&&bst[((1<<ch.size())-1)^(1<<id[it])]>=0&&precalc[L[i]][now]&&L[i]!=now){
				check_max(dp[now][i],dp[it][i]+bst[((1<<ch.size())-1)^(1<<id[it])]);
			}
		}
	}
}
int main(){
	freopen("training.in","r",stdin);
	freopen("training.out","w",stdout);
	memset(dp,-63,sizeof(dp));
	scanf("%d%d",&n,&m);
	int sum=0;
	rb(i,1,m){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		sum+=w;
		if(w==0) tree[u].PB(v),tree[v].PB(u);
		else if(E.find(II(u,v))==E.end()||E[II(u,v)]<w) E[II(u,v)]=E[II(v,u)]=w;
	}
	dfs(1,0);
	rb(i,1,n) rb(j,1,n) precalc[i][j]=isanc(i,j);
	for(auto ite=E.begin();ite!=E.end();ite++) if(col[ite->FIR.FIR]==col[ite->FIR.SEC]) {
		if(ite->FIR.FIR<ite->FIR.SEC) continue;
		V[cnt]=ite->FIR.SEC;
		W[cnt]=ite->SEC;
		g[ite->FIR.FIR].PB(cnt);
		L[cnt]=L[cnt+1]=lca(ite->FIR.SEC,ite->FIR.FIR);
		if(V[cnt]!=L[cnt]) A[cnt]=jump(V[cnt],deep[V[cnt]]-deep[L[cnt]]-1);
		cnt++;
		g[ite->FIR.SEC].PB(cnt);
		V[cnt]=ite->FIR.FIR;
		W[cnt]=ite->SEC;
		if(V[cnt]!=L[cnt]) A[cnt]=jump(V[cnt],deep[V[cnt]]-deep[L[cnt]]-1);
		cnt++;
	}
	rl(i,n,0) for(auto it:dep[i]) trans(it);
	int ans=0;
	rb(i,0,cnt) check_max(ans,dp[1][i]);
	printf("%d\n",sum-ans);
	return 0;
}