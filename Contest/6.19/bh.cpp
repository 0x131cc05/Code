#include<bits/stdc++.h>
using namespace std;
const int maxn=55;
int C[maxn][maxn];
int n,m,mod;
int dp[9][maxn];
int f[maxn][maxn][9][(1<<8)+5];
int g[maxn][maxn][9];
int Pow(int a,long long k)
{
	int ret=1;
	while(k)
	{
		if(k&1)ret=ret*1LL*a%mod;
		k>>=1,a=a*1LL*a%mod;
	}
	return ret;
}
int F(int a,int b,int d,int mi)
{
	if(a>b)swap(a,b);
	if(d==-1)return 1;
	if(f[a][b][d][mi]!=-1)return f[a][b][d][mi];
	if(!a||!b)return f[a][b][d][mi]=Pow((1<<d),a+b);
	int cur=0;
	if(mi&(1<<d))cur=F(a,b,d-1,mi^(1<<d))*2LL%mod;
	else 
	{
		for(int i=0;i<=a;i++)
		for(int j=0;j<=b;j++)cur=(cur+C[a][i]*1LL*C[b][j]%mod*F(i,j,d-1,mi)%mod*F(a-i,b-j,d-1,mi)%mod)%mod;
	}
	return f[a][b][d][mi]=cur;
}
int solve(int d,int k)
{
	if(d==-1)return 0;
	if(dp[d][k]!=-1)return dp[d][k];
	int cur=2 * solve(d - 1, k) % mod;
	for(int i=1;i<k;i++) {
	    cout << k << ' ' << d << ' ' << i << ' ' << g[i][k - i][d] << endl;
	    cur=(cur+C[k][i]*1LL*(solve(d-1,i)*1LL*Pow(2,d*1LL*(k-i))%mod+
			solve(d-1,k-i)*1LL*Pow(2,d*1LL*i)%mod)%mod+
			C[k][i]*1LL*(1<<d)%mod*1LL*Pow(2,d*1LL*i)%mod*Pow(2,d*1LL*(k-i))%mod+
			g[i][k-i][d]*1LL*C[k][i]%mod)%mod;
    }
        	
	return dp[d][k]=cur;
}
int main()
{
	memset(f,-1,sizeof(f));
	memset(dp,-1,sizeof(dp));
	scanf("%d%d%d",&n,&m,&mod);
	C[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		C[i][0]=1;
		for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	for(int i=0;i<=n;i++)
	for(int j=0;j+i<=n;j++)
	for(int d=0;d<=m;d++)
	for(int k=0;k<(1<<d+1);k++)
	{
		if(k==(1<<d+1)-1)g[i][j][d + 1]+=F(i,j,d,k)*1LL*k%mod;
		else g[i][j][d + 1]+=(F(i,j,d,k)-F(i,j,d,k+1)+mod)*1LL*k%mod;
//		printf("%d %d %d %d %d\n",i,j,d,k,F(i,j,d,k) - F(i,j,d,k + 1));
		g[i][j][d + 1]%=mod;
	}
	cout << g[1][1][1] << endl;
	printf("%d\n",solve(m-1,n));
}

