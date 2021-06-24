#include<bits/stdc++.h>
using namespace std;
const int N=100005,M=55,inf=1e9;
int n,q,a[N],p[N],dp[M][M];
inline void chmax(int &a,int b){if(a<b)a=b;}
int sol(int l,int r,int k)
{
	if(n>50)
		return p[r]-p[l-1];
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)
			dp[i][j]=-inf;
	dp[l-1][0]=0;
	for(int i=l-1;i<=r;i++)
	{
		for(int j=0;j<=k;j++)
		{
			if(dp[i][j]<=-inf)
				continue;
			chmax(dp[i+1][j],dp[i][j]);
			for(int x=i+1;x<=r;x++)
				chmax(dp[x][j+1],dp[i][j]+p[x]-p[i]);
		}
	}
	return dp[r][k];
}
int main()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),p[i]=p[i-1]+a[i];
	while(q--)
	{
		int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",sol(l,r,k));
	}
	return 0;
}