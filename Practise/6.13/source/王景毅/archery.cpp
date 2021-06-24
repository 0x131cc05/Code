#include<bits/stdc++.h>
using namespace std;
const int N=400005;
int n,r,b[N],a[N],p[N],v[N],m,mp,s;
int sol()
{
	for(int i=1;i<=n;i++)
		p[i]=(i+1)/2;
	for(int x=1;x<=n;x++)
	{
		for(int i=1;i<=n;i++)
			v[i]=0;
		for(int i=1;i<=n;i++)
			v[p[i]]^=a[i];
		for(int i=1;i<=n;i++)	
		{
			int y=v[p[i]]^a[i];
			if(a[i]<y)
			{
				if(p[i]>1)
					p[i]--;
			}
			else
			{
				if(p[i]==1)
					p[i]=n/2;
			}
		}
	}
	for(int i=1;i<=n;i++)
		if(a[i]==b[1])
			return (a[i]<=n/2+1?((p[i]-r-1)%n+n)%n+1:p[i]);
}
int main()
{
	freopen("archery.in","r",stdin);
	freopen("archery.out","w",stdout);
	scanf("%d%d",&n,&r);
	n<<=1;
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	m=n+1;
	for(int i=(n<=1000?1:n-100);i<=n;i++)
	{
		s=0;
		for(int j=2;j<=i;j++)
			a[++s]=b[j];
		a[++s]=b[1];
		for(int j=i+1;j<=n;j++)
			a[++s]=b[j];
		int x=sol();
		if(x<=m)
			m=x,mp=i;
	}
	printf("%d\n",(mp+1)/2);
	return 0;
}