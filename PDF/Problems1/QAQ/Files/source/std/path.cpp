#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define N 530000
#define mod 998244353
int n,m,v1,v2,v[N],a[N],b[N],st[20][2][N],le[20][2],ntt[N],rev[N],fr[N],ifr[N],sr[20][2][N],as[N],s1;
int pw(int a,int p){int as=1;while(p){if(p&1)as=1ll*as*a%mod;a=1ll*a*a%mod;p>>=1;}return as;}
vector<int> sb;
void dft(int s,int *a,int t)
{
	for(int i=0;i<s;i++)rev[i]=(rev[i>>1]>>1)|(i&1?s/2:0),ntt[rev[i]]=a[i];
	for(int i=2,ct=1;i<=s;i<<=1,ct++)
	{
		for(int j=0;j<s;j+=i)
		for(int k=j,vl=0;k<j+(i>>1);k++,vl++)
		{
			int a1=ntt[k],a2=1ll*ntt[k+(i>>1)]*sr[ct][(t+1)>>1][vl]%mod;
			ntt[k]=(a1+a2)%mod;
			ntt[k+(i>>1)]=(a1-a2+mod)%mod;
		}
	}
	int inv=pw(s,t==-1?mod-2:0);
	for(int i=0;i<s;i++)a[i]=1ll*ntt[i]*inv%mod;
}
void doit(int s)
{
	int vl=1;
	for(int i=0;i<=s/2;i++)a[i]=1ll*fr[s]*ifr[i*2]%mod*ifr[s-i*2]%mod*vl%mod,vl=1ll*vl*(i*2+1)%mod;
}
void cdq(int l,int r,int d,int v)
{
	if(l==r)
	{
		doit(sb[l]);le[d][v]=sb[l]/2+1;
		for(int i=0;i<=sb[l];i++)st[d][v][i]=a[i];
		return;
	}
	int mid=(l+r)>>1;
	cdq(l,mid,d+1,0);
	cdq(mid+1,r,d+1,1);
	int l1=1;while(l1<=le[d+1][0]+le[d+1][1])l1<<=1;
	for(int i=0;i<l1;i++)a[i]=b[i]=0;
	for(int i=0;i<le[d+1][0];i++)a[i]=st[d+1][0][i];
	for(int i=0;i<le[d+1][1];i++)b[i]=st[d+1][1][i];
	dft(l1,a,1);dft(l1,b,1);for(int i=0;i<l1;i++)a[i]=1ll*a[i]*b[i]%mod;
	dft(l1,a,-1);le[d][v]=le[d+1][0]+le[d+1][1]-1;
	for(int i=0;i<le[d][v];i++)st[d][v][i]=a[i];
}
int main()
{
	freopen("path.in","r",stdin),freopen("path.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<n;i++)scanf("%d%d",&v1,&v2),v[v1]++,v[v2]++;
	fr[0]=ifr[0]=1;for(int i=1;i<=250000;i++)fr[i]=1ll*fr[i-1]*i%mod,ifr[i]=pw(fr[i],mod-2);
	for(int i=1;i<=19;i++)
	for(int j=0;j<=1;j++)
	{
		int st1=pw(3,(mod-1)>>i);
		if(!j)st1=pw(st1,mod-2);
		sr[i][j][0]=1;
		for(int k=1;k<1<<i-1;k++)sr[i][j][k]=1ll*sr[i][j][k-1]*st1%mod;
	}
	s1=1;as[0]=1;
	for(int i=0;i<=19;i++)
	{
		int ct=0,l=(1<<i)-1,r=(1<<i+1)-2;sb.clear();
		for(int j=1;j<=n;j++)if(v[j]>=l&&v[j]<=r)sb.push_back(v[j]),ct++;
		if(!ct)continue;
		sort(sb.begin(),sb.end());
		cdq(0,ct-1,1,0);
		int l1=1;while(l1<=s1+le[1][0])l1<<=1;
		for(int i=0;i<l1;i++)a[i]=b[i]=0;
		for(int i=0;i<le[1][0];i++)a[i]=st[1][0][i];
		for(int i=0;i<s1;i++)b[i]=as[i];
		dft(l1,a,1);dft(l1,b,1);for(int i=0;i<l1;i++)a[i]=1ll*a[i]*b[i]%mod;
		dft(l1,a,-1);s1=s1+le[1][0]-1;
		for(int i=0;i<s1;i++)as[i]=a[i];
	}
	for(int i=1;i<n;i++)printf("%d ",as[n-1-i]);
}
