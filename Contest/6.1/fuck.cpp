#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#define PB push_back
#define MP make_pair
#define PII pair<int,int>
#define FIR first
#define SEC second
#define ll long long
using namespace std;

inline char nc() {
	return getchar();
    static char buf[1000000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
template <class T>
inline void rd(T &x) {
	x=0; char c=nc(); int f=1;
	while(!isdigit(c)) { if(c=='-') f=-1; c=nc(); }
	while(isdigit(c)) x=x*10-'0'+c,c=nc(); x*=f;
}
static char pbuf[1000000],*p1=pbuf;
void flush() { fwrite(pbuf,1,p1-pbuf,stdout); p1=pbuf; }
inline void pc(char c) {
	putchar(c); return;
    if(p1-pbuf==1000000) flush();
    *p1++=c;
}
template <class T>
inline void wrt(T x) {
    static int s[35],top;
    s[top=1]=x%10; x/=10;
    while(x) s[++top]=x%10,x/=10;
    while(top) pc(s[top--]+'0');
}
#include <ctime> 

const int N=2e5+10;
const int M=11;
const int mod=998244353;
inline int Pow(int x,int y) { int res=1; for(;y;y>>=1,x=1ll*x*x%mod) if(y&1) res=1ll*res*x%mod; return res; }
inline void Add(int &x,int y) { x+=y; if(x>=mod) x-=mod; }
inline void Add(ll &x,ll y) { x+=y; if(x>=mod) x-=mod; }
inline void Dec(int &x,int y) { x-=y; if(x<0) x+=mod; }
inline void Dec(ll &x,ll y) { x-=y; if(x<0) x+=mod; }
inline int ADD(int x) { return x>=mod?x-mod:x; }
inline int SUB(int x) { return x<0?x+mod:x; } 
vector<int> son[N];
int dep[N],n;
int seq[N],val[N],ncnt,cur_mi;
void dfs(int u) {
	if(!son[u].size()) {
		seq[++ncnt]=u;
		val[ncnt]=cur_mi;
		cur_mi=1e9;
	}
	cur_mi=min(cur_mi,dep[u]);
	for(int i=0;i<son[u].size();++i) {
		int v=son[u][i];
		dep[v]=dep[u]+1;
		dfs(son[u][i]);
		cur_mi=min(cur_mi,dep[u]);
	}
}
int sum[M][N];
int C[M][M];
namespace TREE {
	int Lg[N],rmq[18][N];
	inline int rmq_getmin(int x,int y) { return val[x]<val[y] ? x : y; }
	void init_rmq() {
		for(int i=2;i<=n;++i) Lg[i]=Lg[i>>1]+1,rmq[0][i]=i;
		for(int j=1;j<=17;++j)
			for(int i=2;i+(1<<j)-1<=n;++i)
				rmq[j][i]=rmq_getmin(rmq[j-1][i],rmq[j-1][i+(1<<j-1)]);
	}
	int Qmin(int l,int r) {
		int L=Lg[r-l+1];
		return rmq_getmin(rmq[L][l],rmq[L][r-(1<<L)+1]);
	}	
	int ch[N][2],pre[N],suf[N];
	int s[N][M],a[N][M][M][2],b[N][M][M][2];
	int sub[N][M],subl[N][M],subr[N][M];
	int al[N][M][M][2],br[N][M][M][2];
	void build(int l,int r,int &i) {
		if(l>r) return (void)(i=0);
		i=Qmin(l,r);
		pre[i]=l-1,suf[i]=r+1;
		for(int t=0;t<M;++t)
			for(int j=0;j<=t;++j) {
				Add(s[i][t],1ll*val[i]*C[t][j]%mod*(sum[t-j][suf[i]-2]-sum[t-j][i-2]+mod)%mod*(sum[j][i-1]-sum[j][pre[i]-1]+mod)%mod*(j&1 ? mod-1 : 1)%mod);
				Add(a[i][t][j][0],1ll*val[i]*C[t][j]%mod*(sum[t-j][suf[i]-2]-sum[t-j][i-2]+mod)%mod*sum[j][i-1]%mod*(j&1 ? mod-1 : 1)%mod);
				Add(a[i][t][j][1],1ll*val[i]*C[t][j]%mod*(sum[t-j][suf[i]-2]-sum[t-j][i-2]+mod)%mod*(j&1 ? 1 : mod-1)%mod);
				Add(b[i][t][j][0],1ll*val[i]*C[t][j]%mod*(sum[t-j][i-1]-sum[t-j][pre[i]-1]+mod)%mod*(t-j&1 ? mod-1 : 1)%mod*(mod-sum[j][i-2])%mod);
				Add(b[i][t][j][1],1ll*val[i]*C[t][j]%mod*(sum[t-j][i-1]-sum[t-j][pre[i]-1]+mod)%mod*(t-j&1 ? mod-1 : 1)%mod);
			}
		build(l,i-1,ch[i][0]);
		build(i+1,r,ch[i][1]);
		for(int t=0;t<M;++t)
			sub[i][t]=((ll)s[i][t]+sub[ch[i][0]][t]+sub[ch[i][1]][t])%mod;
	}
//	void dfs0(int u) {
//		if(!u) return;
//		dfs0(ch[u][0]),dfs0(ch[u][1]);
//		for(int t=0;t<M;++t)
//			sub[u][t]=((ll)s[u][t]+sub[ch[u][0]][t]+sub[ch[u][1]][t])%mod;
//	}
	void dfs1(int u) {
		for(int t=0;t<=M-1;++t) {
			Add(subl[u][t],s[u][t]),
			Add(subr[u][t],s[u][t]);
		}
		if(ch[u][0]) {
			for(int t=0;t<M;++t) {
				subl[ch[u][0]][t]=subl[u][t],
				subr[ch[u][0]][t]=subr[u][t];
				for(int j=0;j<=t;++j)
					al[ch[u][0]][t][j][0]=ADD(al[u][t][j][0]+a[u][t][j][0]),
					al[ch[u][0]][t][j][1]=ADD(al[u][t][j][1]+a[u][t][j][1]),
					br[ch[u][0]][t][j][0]=br[u][t][j][0],
					br[ch[u][0]][t][j][1]=br[u][t][j][1];
			}
			for(int t=0;t<M;++t)
				Add(subr[ch[u][0]][t],sub[ch[u][1]][t]);
			dfs1(ch[u][0]);
		}
		if(ch[u][1]) {
			for(int t=0;t<M;++t) {
				subl[ch[u][1]][t]=subl[u][t],
				subr[ch[u][1]][t]=subr[u][t];
				for(int j=0;j<=t;++j)
					al[ch[u][1]][t][j][0]=al[u][t][j][0],
					al[ch[u][1]][t][j][1]=al[u][t][j][1],
					br[ch[u][1]][t][j][0]=ADD(br[u][t][j][0]+b[u][t][j][0]),
					br[ch[u][1]][t][j][1]=ADD(br[u][t][j][1]+b[u][t][j][1]);
			}
			for(int t=0;t<M;++t)
				Add(subl[ch[u][1]][t],sub[ch[u][0]][t]);
			dfs1(ch[u][1]);
		}
	}
	int rt;
	void init() {
		init_rmq();
		build(2,ncnt,rt);
//		dfs0(rt);
		dfs1(rt);
	}
	void Qry(int *f,int m,int L,int R) {
		if(L>=R) {
			for(int t=0;t<=m;++t) {
				f[t]=0;
				for(int j=0;j<=t;++j)
					for(int i=L;i<=R;++i) if(val[i])
						Add(f[t],1ll*val[i]*C[t][j]%mod*(sum[t-j][min(suf[i],R+1)-2]-sum[t-j][i-2]+mod)%mod*(sum[j][i-1]-sum[j][max(pre[i],L-1)-1]+mod)%mod*(j&1 ? mod-1 : 1)%mod);
			}
			return;
		}
		int lca=Qmin(L,R);
		for(int t=0;t<=m;++t) {
			f[t]=SUB(sub[lca][t]-s[lca][t]);
			Dec(f[t],SUB(subl[L][t]-subl[lca][t]));
			Dec(f[t],SUB(subr[R][t]-subr[lca][t]));
			if(ch[L][0]) Dec(f[t],sub[ch[L][0]][t]);
			if(ch[R][1]) Dec(f[t],sub[ch[R][1]][t]);
			for(int j=0;j<=t;++j) {
				int tmp_a[2]={SUB(al[L][t][j][0]-al[lca][t][j][0]),SUB(al[L][t][j][1]-al[lca][t][j][1])};
				int tmp_b[2]={SUB(br[R][t][j][0]-br[lca][t][j][0]),SUB(br[R][t][j][1]-br[lca][t][j][1])};
				Dec(tmp_a[0],a[lca][t][j][0]);
				Dec(tmp_a[1],a[lca][t][j][1]);
				Dec(tmp_b[0],b[lca][t][j][0]);
				Dec(tmp_b[1],b[lca][t][j][1]);
				Add(tmp_a[0],a[L][t][j][0]);
				Add(tmp_a[1],a[L][t][j][1]);
				Add(tmp_b[0],b[R][t][j][0]);
				Add(tmp_b[1],b[R][t][j][1]);
				Add(f[t],(tmp_a[0]+1ll*tmp_a[1]*sum[j][(L-1)-1])%mod);
				Add(f[t],(tmp_b[0]+1ll*tmp_b[1]*sum[j][(R+1)-2])%mod);
				Add(f[t],1ll*val[lca]*C[t][j]%mod*(sum[t-j][(R+1)-2]-sum[t-j][lca-2]+mod)%mod*(sum[j][lca-1]-sum[j][(L-1)-1]+mod)%mod*(j&1 ? mod-1 : 1)%mod);
			}
		}
	}
}

int sum_dep[N];
int coe[M],f[M],g[M],pw2[M];
int m;
int main() {
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int typ,q; rd(typ),rd(n),rd(q);
	for(int i=0;i<=M-1;++i) for(int j=0;j<=i;++j) C[i][j]=j ? (C[i-1][j-1]+C[i-1][j])%mod : 1;
	pw2[0]=1; for(int i=1;i<=M-1;++i) pw2[i]=pw2[i-1]*2ll%mod;
	for(int j=0;j<=M-1;++j) {
		sum[j][0]=j==0;
		for(int i=1;i<=n;++i) sum[j][i]=(sum[j][i-1]+Pow(i,j))%mod;
	}
	for(int i=2,x;i<=n;++i) rd(x),son[x].PB(i);
	dfs(1);
	TREE::init();
	for(int i=1;i<=ncnt;++i) sum_dep[i]=(sum_dep[i-1]+dep[seq[i]])%mod;
	int lastans=0,x,y;
	while(q--) {
		rd(x),rd(y),rd(m);
		if(typ) x^=lastans,y^=lastans;
		if(x>y) swap(x,y);
		
		int L=lower_bound(seq+1,seq+ncnt+1,x)-seq;
		int R=upper_bound(seq+1,seq+ncnt+1,y)-seq-1;
		
		if(R<L) {
			wrt(lastans=0),pc('\n');
//			printf("%d\n",lastans=0);
			continue;
		}
//		for(int t=0;t<=m-2;++t) {
//			g[t]=0;
//			for(int l=L;l<=R;++l)
//			for(int r=l+1;r<=R;++r)
//				g[t]=(g[t]+1ll*Qmin(seq[l],seq[r])*Pow(r-l-1,t))%mod;
//		}
		TREE::Qry(g,m-2,L+1,R);
//		for(int j=2;j<=m;++j)
//		for(int x=1;x<=j;++x)
//		for(int y=1;x+y<=j;++y)
//			f[j]=(f[j]+1ll*C[x+y][x]*C[j][x+y]%mod*g[j-x-y])%mod;
		for(int j=2;j<=m;++j)
			for(int t=2;t<=j;++t)
				f[j]=(f[j]+1ll*(pw2[t]-2ll+mod)*C[j][t]%mod*g[j-t])%mod;
		
		for(int j=1;j<=m;++j)
			f[j]=(f[j]+(sum_dep[R]-sum_dep[L-1]+mod)%mod)%mod;
		for(int j=1;j<=m-1;++j)
			for(int k=0;k<=j;++k)
				Add(coe[k+(m-j)],1ll*C[m][j]*C[j][k]%mod*Pow(R-L+1,j-k)%mod*(k&1 ? mod-1 : 1)%mod);
		int ans=0;
		for(int j=1;j<=m;++j) ans=(ans+1ll*f[j]*coe[j]%mod)%mod;
		ans=1ll*ans*Pow(R-L+1,1ll*m*(mod-2)%(mod-1))%mod; 
//		printf("%d\n",lastans=ans);
		wrt(lastans=ans),pc('\n');
		for(int j=1;j<=m;++j) f[j]=0,coe[j]=0;
	}
	flush();
	return 0;
}
	
