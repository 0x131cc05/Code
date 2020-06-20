#include<cstdio>
using namespace std;
#define N 10050
int n,k,tp;
char s[N],t[N],as[N],as1[N];
void solve()
{
	int le=0,st=n;
	while(t[st]==t[n])le++,st--;
	le<<=(k-1);
	if(le>n)le=n;
	for(int i=1;i<=le;i++)as1[i]=t[n];
	for(int i=le+1,k=st;i<=n;i++,k--)as1[i]=t[k];
	for(int i=1;i<=n;i++)if(as[i]>as1[i]){for(int j=1;j<=n;j++)as[j]=as1[j];return;}
	else if(as[i]<as1[i])return;
}
int main()
{
	scanf("%d%d%s",&n,&k,s+1);
	if(k>=14){char as='z';for(int i=1;i<=n;i++)if(s[i]<as)as=s[i];for(int i=1;i<=n;i++)printf("%c",as);return 0;}
	tp=1<<k-1;
	for(int i=1;i<=n;i++)s[n*2-i+1]=s[i];
	as[1]='z'+1;
	for(int i=n+1;i<=n*2;i++)
	{
		for(int j=i-n+1;j<=i;j++)t[j-i+n]=s[j];
		solve();
	}
	printf("%s",as+1);
}
