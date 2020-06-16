#include<cstdio>
#include<algorithm>
using namespace std;
#define N 5050
int n,v[N],dp[N][N],is[N];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&v[i]);
	for(int i=1;i<=n;i++)
	{
		int las=0;
		for(int j=i-1;j>=1;j--)
		if(!las)is[j]=1,las=j;
		else if(1ll*(las-i)*(v[j]-v[i])-1ll*(j-i)*(v[las]-v[i])<0)las=j,is[j]=1;
		else is[j]=0;
		las=i;dp[i][i]=1;
		int su=0;
		for(int j=i;j>=1;j--)
		if(is[j])
		{
			if(las!=j+1)su+=min(dp[j+1][las],dp[j+1][las-1]);
			las=j;
			dp[j][i]=su+1;
		}
		else dp[j][i]=su+1+min(dp[j][las],dp[j][las-1]);
	}
	int su=0;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=i;j++)su^=dp[j][i], printf("%d %d %d\n", j, i, dp[j][i]);
	printf("%d\n",su);
}
