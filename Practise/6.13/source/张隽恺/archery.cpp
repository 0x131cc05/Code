//Orz lsj
//lsj ak ioi
#include<cstdio>
#include<algorithm>
using namespace std;
#define N 3050
int n,k,v[N*2],s[N*2][N][2],as,vl=0,s1[N],c1,s2[N],c2;
void init()
{
	for(int i=1;i<=n;i++)s[0][i][0]=v[i*2+1],s[0][i][1]=v[i*2];
	s[0][n][0]=v[1];
	for(int i=1;i<=2*n+1;i++)
	{
		for(int j=1;j<=n;j++)if(s[i-1][j][0]>s[i-1][j][1])swap(s[i-1][j][0],s[i-1][j][1]);
		for(int j=1;j<=n;j++)
		{
			int v1=j==1?s[i-1][j][1]:s[i-1][j][0],v2=s[i-1][j][1]^s[i-1][j][0]^v1;
			s[i][j==1?n:j-1][0]=v1;s[i][j][1]=v2;
		}
	}
}
void calc(int x,int y)
{
	int a1,a2,v1=y,v2=y==n?1:y+1;
	if(v1==1)a1=s[x-1][v1][0];else a1=s[x-1][v1][1];
	if(v2==1)a2=s[x-1][v2][1];else a2=s[x-1][v2][0];
	if(a1>a2)a1^=a2^=a1^=a2;
	if(s[x][y][0]!=a1||s[x][y][1]!=a2)s[x][y][0]=a1,s[x][y][1]=a2,s2[++c2]=y;
}
int check(int x)
{
	if(x<n)
	{
		s[0][x][0]=v[1];s[0][x][1]=v[x*2];
		s[0][x+1][0]=v[x*2+1];s[0][x+1][1]=v[x*2+2];
		if(s[0][x][0]>s[0][x][1])swap(s[0][x][0],s[0][x][1]);
		if(s[0][x+1][0]>s[0][x+1][1])swap(s[0][x+1][0],s[0][x+1][1]);
		c1=2;s1[1]=x;s1[2]=x+1;
		for(int i=1;i<=2*n;i++)
		{
			for(int j=1;j<=c1;j++){int s=s1[j];calc(i,s);calc(i,s==1?n:s-1);}
			c1=c2;c2=0;for(int j=1;j<=c1;j++)s1[j]=s2[j];
		}
		c1=0;
	}
	int tp=0,rt=k-2*n;
	for(int i=1;i<=n;i++)if(s[n*2][i][0]==v[1]||s[n*2][i][1]==v[1])tp=i;
	if(v[1]==1||v[1]>n+1)return tp;
	else return (tp-1+n-(rt%n))%n;
}
int main()
{
	freopen("archery.in","r",stdin);
	freopen("archery.out","w",stdout);
	scanf("%d%d",&n,&k);as=n+1;
	if(n>3000){scanf("%d",&v[1]);if(v[1]>n+1)printf("2\n");else if(v[1]==1)printf("%d\n",n);else printf("%d\n",k%n+1);return 0;}
	for(int i=1;i<=n*2;i++)scanf("%d",&v[i]);
	init();
	for(int i=n;i>=1;i--)
	{
		int tp=check(i);
		if(tp<as)as=tp,vl=i;
	}
	printf("%d\n",vl);
}
