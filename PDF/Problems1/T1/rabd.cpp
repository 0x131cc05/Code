#include<bits/stdc++.h>
using namespace std;
int n,a,b,s;
int p[105050],v2[104050];
int main()
{
	srand((unsigned long long)new char+time(0));
	scanf("%d%d%d%d",&n,&a,&b,&s);
	char st[1050]="task0_0.in";
	sprintf(st,"task%d_%d.in",a,b);
	freopen(st,"w",stdout);
	printf("%d\n",n);
	for(int i=1;i<=n;i++)p[i]=i;
	for(int i=1;i<=30;i++)random_shuffle(p+1,p+n+1);
	for(int i=1;i<=30000;i++)v2[i]=rand()%s+1;
	for(int i=1;i<s;i++)printf("%d %d\n",p[rand()%i+1],p[i+1]);
	for(int i=s+1;i<=n;i++)printf("%d %d\n",p[v2[rand()%30000+1]],p[i]);
	fclose(stdout);
	freopen("1.bat","w",stdout);
	printf("t1.exe <task%d_%d.in>task%d_%d.out",a,b,a,b);
	fclose(stdout);
	system("1.bat");
}
