#include<bits/stdc++.h>
using namespace std;
int n,a,b,s;long long m,m1;
int p[105050],v2[104050];
int main()
{
	srand((unsigned long long)new char+time(0));
	scanf("%d%lld%d",&n,&m,&a);m1=m;
	for(b=1;b<=5;b++)
	{
		m=m1;
	char st[1050]="task0_0.in";
	sprintf(st,"task%d_%d.in",a,b);
	freopen(st,"w",stdout);
	m=m*(1.0*(rand()%5000+15000)/20001);
	printf("%d %lld\n",n,m);
	for(int i=1;i<=n;i++)p[i]=i;
	for(int i=1;i<=30;i++)random_shuffle(p+1,p+n+1);
	for(int i=1;i<n;i++)printf("%d %d\n",p[rand()%i+1],p[i+1]);
	fclose(stdout);
	freopen("1.bat","w",stdout);
	printf("t3.exe <task%d_%d.in>task%d_%d.out",a,b,a,b);
	fclose(stdout);
	system("1.bat");
	}
}
