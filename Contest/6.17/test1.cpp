#include<cstdio>
#include<ctime>
#include<algorithm>
#include<cstdlib>
using namespace std;
int main()
{
//	freopen("test1.in","w",stdout);
	srand(time(0)+(unsigned long long)new char);
	int n=500,q=1000,t=100,c=rand()%1000+1;
	printf("%d %d %d %d\n",n,q,t,c);
	for(int i=2;i<=n;i++)printf("%d %d %d\n",rand()%(i-1)+1,i,rand()%3?0:1);
	while(q--)
	{
		int l=rand()%(t+1),r=rand()%(t+1);
		if(l>r)l^=r^=l^=r;
		printf("%d %d %d %d\n",rand()%n+1,l,r-l,rand() % 10000000);
	}
}
