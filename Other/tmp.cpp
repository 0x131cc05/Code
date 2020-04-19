#include<bits/stdc++.h>
using namespace std;
const int maxn=1e7+20;
int p[maxn],n,m;
char s[maxn],t[maxn];
int len=0;
int ans[maxn],nxt[maxn];
void solve(int l,int r)
{
	//cout<<l<<' '<<r<<endl;
	if(l>r)return ;
	len=0;
	for(int i=l;i<=r;i++)t[++len]=s[i];
	for(int i=2;i<=len;i++)
	{
		int j=nxt[i-1];
		while(j&&t[j+1]!=t[i])j=nxt[j];
		if(t[j+1]==t[i])j++;
		nxt[i]=j;
	}
	int now=len,lst=1;
	//cout<<len<<endl;
	while(now)
	{
		//cout<<now<<endl;
		for(int i=lst;i<=len-nxt[now];i++)
		if(n>i)
		{
			cout << i << endl;
			ans[n-i]=true;
			//cout<<n<<endl;
			//if(n-i>10000)printf("fuck\n");
		}
		lst=len-nxt[now]+2,now=nxt[now];
	}
}
int main()
{
	//freopen("T2.in","r",stdin);
	//freopen("T2.out","w",stdout);
	while(~scanf("%s",s+1))
	{
		n=strlen(s+1),m=0;
		if(n==0){printf("0\n");continue;}
		for(int i=0;i<=n;i++)ans[i]=0;
		for(int i=n+1;i<=2*n;i++)s[i]=s[i-n];
		p[1]=0;
		for(int i=1;i<=n;i++)if(s[i]==s[i+1])p[++m]=i;
		if(!m)printf("1");
		else printf("0"),p[++m]=p[1]+n;
		for(int i=1;i<m;i++)solve(p[i]+1,p[i+1]);
		if(!m)solve(1,2*n);
		for(int i=1;i<n-1;i++)printf("%c",ans[i]?'1':'0');
		printf("0\n");
	}
}