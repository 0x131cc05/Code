#include<cstdio>
#include<cmath>
using namespace std;
#define mod 998244353
#define N 105
#define M 40100
#define K 21
#define S 200500
#define ll long long
int id[K][M],tid[N][K][M],id2[K][M],tid2[K][M],ha1[600500],dp[N][K][M],f[K][M];
int n,k,a,b,head[N],cnt,s1[N][K],c1[K],as[K][N*K],mp1[2222222],mp2[5555],ct1;
ll m;
struct edge{int t,next;}ed[N*2];
void adde(int f,int t){ed[++cnt]=(edge){t,head[f]};head[f]=cnt;ed[++cnt]=(edge){f,head[t]};head[t]=cnt;}
struct state{int vl,v1;}tid1[M];
int fu1(state x){int st=x.vl*2800+x.v1;return st;}
state doit(state a,state b,int s)
{
	int r1=0,r2=0,c1=1,v2=0,s1=0,s2=0,tp=0;
	state c;c.v1=0;c.vl=a.vl+b.vl;
	a.v1=mp2[a.v1];b.v1=mp2[b.v1];
	if(!s)return c;
	while(a.v1)if(a.v1&1)r1+=1<<v2,v2++,a.v1>>=1;
	else if(c1<s)c1++,v2++,a.v1>>=1;
	else a.v1>>=1;
	c1=1;v2=0;
	while(b.v1)if(b.v1&1)r2+=1<<v2,v2++,b.v1>>=1;
	else if(c1<s)c1++,v2++,b.v1>>=1;
	else b.v1>>=1;
	tp=1;v2=0;
	while(r1+r2)
	if(r1&1)c.vl+=s2,s1+=tp,c.v1+=1<<v2,v2++,r1>>=1;
	else if(r2&1)c.vl+=s1,s2+=tp,c.v1+=1<<v2,v2++,r2>>=1;
	else r1>>=1,r2>>=1,v2++,tp++;
	c.v1=mp1[c.v1];
	return c;
}
void ins1(int d,state x,int vl)
{
	int vl1=fu1(x);
	if(!ha1[vl1])ha1[vl1]=++cnt,tid1[cnt]=x;
	int fu2=ha1[vl1];
	if(!id2[d][fu2])id2[d][fu2]=++c1[d],tid2[d][c1[d]]=fu2;
	fu2=id2[d][fu2];
	f[d][fu2]=(f[d][fu2]+vl)%mod;
}
void ins2(int u,int d,state x,int vl)
{
	int vl1=fu1(x);
	if(!ha1[vl1])ha1[vl1]=++cnt,tid1[cnt]=x;
	int fu2=ha1[vl1];
	if(!id[d][fu2])id[d][fu2]=++s1[u][d],tid[u][d][s1[u][d]]=fu2;
	fu2=id[d][fu2];
	dp[u][d][fu2]=(dp[u][d][fu2]+vl)%mod;
}
void dfs(int u,int fa)
{
	for(int i=head[u];i;i=ed[i].next)if(ed[i].t!=fa)dfs(ed[i].t,u);
	for(int i=0;i<=k;i++)
	{
		state fuc;
		fuc.vl=0;fuc.v1=mp1[!i?0:(1<<i-1)];
		for(int j=0;j<=k;j++)
		{
			for(int l=1;l<=c1[j];l++)id2[j][tid2[j][l]]=0,tid2[j][l]=0,f[j][l]=0;
			c1[j]=0;
		}
		ins1(i,fuc,1);
		for(int j=head[u];j;j=ed[j].next)if(ed[j].t!=fa)
		for(int l1=k;l1>=0;l1--)
		for(int v1=1;v1<=c1[l1];v1++)
		for(int l2=1;l1+l2<=k;l2++)
		for(int v2=1;v2<=s1[ed[j].t][l2];v2++)
		ins1(l1+l2,doit(tid1[tid[ed[j].t][l2][v2]],tid1[tid2[l1][v1]],i),1ll*dp[ed[j].t][l2][v2]*f[l1][v1]%mod);
		for(int j=1;j<=k;j++)
		for(int l=1;l<=c1[j];l++)
		ins2(u,j,tid1[tid2[j][l]],f[j][l]);
	}
	for(int j=0;j<=k;j++)
	for(int l=0;l<=s1[u][j];l++)id[j][tid[u][j][l]]=0;
}
bool check(int s)
{
	int tp1=1,as=0;
	while(s)if(s&1)as+=tp1,s>>=1;
	else tp1++,s>>=1;
	return as<=k;
}
int ch[S],pr[S],ct,p,f3[S],su[S];
void prime(int n)
{
	for(int i=2;i<=n;i++)
	{
		if(!ch[i])pr[++ct]=i;
		for(int j=1;j<=ct&&1ll*i*pr[j]<=n;j++)
		{
			ch[i*pr[j]]=1;
			if(i%pr[j]==0)break;
		}
	}
}
int getid(ll x){return x<=p?x:p*2-(1ll*p*p==m)-m/x+1;}
ll gettid(int x){if(x<=p)return x;x=2*p-(1ll*p*p==m)+1-x;return m/x;}
void init()
{
	int tp=p*2-(1ll*p*p==m);
	for(int i=1;i<=tp;i++)
	{
		ll s1=gettid(i),s2=s1+1;
		if(s1%2)s2/=2;
		else s1/=2;
		s1%=mod,s2%=mod;
		f3[i]=(1ll*s1*s2-1)%mod;
	}
	for(int i=1;i<=ct;i++)su[i]=su[i-1]+pr[i];
	for(int i=1;i<=ct;i++)
	for(int j=tp;j>=1;j--)
	{
		if(1ll*pr[i]*pr[i]>gettid(j))break;
		f3[j]=(f3[j]-1ll*f3[getid(gettid(j)/pr[i])]*pr[i]%mod+1ll*su[i-1]*pr[i]%mod+mod)%mod;
	}
}
int pw(int a,int p){int ans=1;while(p){if(p&1)ans=1ll*ans*a%mod;a=1ll*a*a%mod;p>>=1;}return ans;}
int solve2(ll m){return 1ll*n*(f3[getid(m)]-2*(m>1)+mod)%mod;}
int solve(int a,int p)
{
	if(a==2)return 0;
	int as1=0,st=pw(a,p);
	for(int i=0;i<=p*(p-1)/2;i++)as1=(as1+1ll*as[p][i]*st)%mod,st=1ll*st*a%mod;
	return as1;
}
int solveas(ll m,ll p)
{
	if(m<=1||pr[p]>m||(p>ct&&pr[ct]>=m))return 0;
	int ans=solve2(m);
	ans=(ans-1ll*n*(su[p-1]-(p>1)*2)%mod+mod)%mod;
	for(int j=p;j<=ct&&1ll*pr[j]*pr[j]<=m;j++)
	for(ll s=pr[j],tp=1;s<=m;s*=pr[j],tp++)
	ans=(ans+1ll*((s!=pr[j])+solveas(m/s,j+1))*solve(pr[j],tp))%mod;
	return ans;
}
int main()
{
	scanf("%d%lld",&n,&m);k=20;
	for(int i=0;i<=1050000;i++)if(check(i))mp1[i]=++ct1,mp2[ct1]=i;
	for(int i=1;i<n;i++)scanf("%d%d",&a,&b),adde(a,b);
	dfs(1,0);
	for(int i=1;i<=k;i++)
	for(int j=1;j<=s1[1][i];j++)
	as[i][tid1[tid[1][i][j]].vl]=(as[i][tid1[tid[1][i][j]].vl]+dp[1][i][j])%mod;
	prime(p=sqrt(m));
	init();
	printf("%d\n",(solveas(m,1)+1)%mod);
}
