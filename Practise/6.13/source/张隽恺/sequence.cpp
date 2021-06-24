//Orz lsj
//lsj ak ioi
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define N 50050
#define M 35
int n,q,v[N],l,r,k,sr[M],ct,f1[M],f2[M],dp[M][M*3][2],sz[M],rs[M][2][2][M*3];
struct node{int l,r;vector<int> f[2][2];}e[N*4];
vector<int> doit(vector<int> v1,vector<int> v2)
{
	int s1=v1.size(),s2=v2.size();
	int l1=0,r1=0;
	vector<int> as;as.push_back(v1[0]+v2[0]);
	for(int i=1;i<s1+s2-1;i++)
	{
		int fg=0;
		if(l1==s1-1)fg=1;else if(r1==s2-1)fg=0;else fg=v1[l1+1]+v2[r1]<v1[l1]+v2[r1+1];
		if(fg)r1++;else l1++;
		as.push_back(v1[l1]+v2[r1]);
	}
	if(as[0]<-1.01e9)as[0]=-1.01e9;
	return as;
}
void pushup(int x)
{
	for(int i=0;i<2;i++)
	for(int j=0;j<2;j++)
	{
		vector<int> v1=doit(e[x<<1].f[i][0],e[x<<1|1].f[0][j]),v2=doit(e[x<<1].f[i][1],e[x<<1|1].f[1][j]);
		for(int l=1;l<v2.size();l++)v1[l-1]=max(v1[l-1],v2[l]);
		e[x].f[i][j]=v1;
	}
}
void build(int x,int l,int r)
{
	e[x].l=l;e[x].r=r;
	if(l==r)
	{
		vector<int> s1;s1.push_back(0);s1.push_back(v[l]);
		for(int i=0;i<2;i++)for(int j=0;j<2;j++)
		{
			if(i||j)s1[0]=-1.01e9;
			e[x].f[i][j]=s1;
		}
		return;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);build(x<<1|1,mid+1,r);
	pushup(x);
}
void query0(int x,int l,int r)
{
	if(e[x].l==l&&e[x].r==r){sr[++ct]=x;return;}
	int mid=(e[x].l+e[x].r)>>1;
	if(mid>=r)query0(x<<1,l,r);
	else if(mid<l)query0(x<<1|1,l,r);
	else query0(x<<1,l,mid),query0(x<<1|1,mid+1,r);
}
int justdoit(int x,int k)
{
	int lb=1,rb=sz[x],as=0;
	while(lb<=rb)
	{
		int mid=(lb+rb)>>1;
		if(e[sr[x]].f[0][0][mid]-e[sr[x]].f[0][0][mid-1]>=k)as=mid,lb=mid+1;
		else rb=mid-1;
	}
	return as;
}
int main()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)scanf("%d",&v[i]);
	build(1,1,n);
	while(q--)
	{
		scanf("%d%d%d",&l,&r,&k);
		ct=0;query0(1,l,r);
		int lb=-1e9,rb=1e9,as=0,s1=0,tp1=max(k-ct,0);
		for(int i=1;i<=ct;i++)sz[i]=e[sr[i]].f[0][0].size()-1;
		while(lb<=rb)
		{
			int mid=(lb+rb)>>1;
			int s1=0;
			for(int i=1;i<=ct;i++)s1+=justdoit(i,mid);
			if(s1>=tp1)as=mid,lb=mid+1;
			else rb=mid-1;
		}
		for(int i=1;i<=ct;i++)f1[i]=justdoit(i,as+1),f2[i]=justdoit(i,as),s1+=f1[i];
		for(int i=1;i<=ct;i++)
		{
			int tp=min(tp1-s1,f2[i]-f1[i]);
			f1[i]+=tp;s1+=tp;
		}
		for(int i=0;i<=ct;i++)for(int j=0;j<=ct*3;j++)for(int k=0;k<2;k++)dp[i][j][k]=-1e9;
		dp[0][ct][0]=0;
		for(int i=1;i<=ct;i++)
		{
			for(int p=0;p<2;p++)
			for(int q=0;q<2;q++)
			{
				int mx1=e[sr[i]].f[p][q].size()-1-f1[i];
				for(int j=0;j<=ct*3;j++)rs[i][p][q][j]=j>mx1?-1e9:e[sr[i]].f[p][q][f1[i]+j];
			}
			for(int q=0;q<2;q++)for(int j=0;j<=ct*3;j++)rs[i][0][q][j]=max(rs[i][0][q][j],rs[i][1][q][j]);
		}
		for(int i=1;i<=ct;i++)
		{
			for(int j=0;j<=ct*3-i+1;j++)if(dp[i-1][j][0]>-6e8)
			{
				for(int q=0;q<2;q++)
				for(int fu=0;j+fu<=ct*3-i;fu++)
				dp[i][j+fu][q]=max(dp[i][j+fu][q],dp[i-1][j][0]+rs[i][0][q][fu]);
				for(int q=0;q<2;q++)
				for(int fu=0;j+fu-1<=ct*3-i;fu++)
				dp[i][j+fu-1][q]=max(dp[i][j+fu-1][q],dp[i-1][j][1]+rs[i][1][q][fu]);
			}
			for(int j=0;j<=ct*3-i+1;j++)dp[i][j][0]=max(dp[i][j][0],dp[i][j][1]);
		}
		printf("%d\n",dp[ct][ct+(k-tp1)][0]);
	}
}
