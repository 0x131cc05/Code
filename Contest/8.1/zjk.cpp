#include<cstdio>
#include<algorithm>
#include<assert.h>
using namespace std;
#define N 1000500
#define ll long long
int in[N],tp[N],le[N],vl[N];
char s[N];
ll dp[N],as;
struct SAM{
	int ch[N][26],fail[N],len[N],las,ct;
	void ins(int t)
	{
		int s1=las,st=++ct;las=ct;len[st]=len[s1]+1;
		vl[st]=1;
		while(!ch[s1][t]&&s1)ch[s1][t]=st,s1=fail[s1];
		if(!ch[s1][t]){fail[st]=1;return;}
		int tp=ch[s1][t];
		if(len[tp]==len[s1]+1)fail[st]=tp;
		else
		{
			int cl=++ct;len[cl]=len[s1]+1;
			for(int i=0;i<26;i++)ch[cl][i]=ch[tp][i];
			fail[cl]=fail[tp];fail[tp]=fail[st]=cl;
			while(s1&&ch[s1][t]==tp)ch[s1][t]=cl,s1=fail[s1];
		}
	}
}sa;
bool cmp(int a,int b){return le[a]<le[b];}
int main()
{
	scanf("%s",s+1);sa.las=sa.ct=1;
	for(int i=1;s[i];i++)sa.ins(s[i]-'a');
	for(int i=1;i<=sa.ct;i++)tp[i]=i,le[i]=sa.len[i];
	sort(tp+1,tp+sa.ct+1,cmp);
	for(int i=sa.ct;i>0;i--)vl[sa.fail[tp[i]]]+=vl[tp[i]];
	for(int i=1;i<=sa.ct;i++)
	{
		int st=tp[i];
		dp[st]=max(dp[st],dp[sa.fail[st]]+1ll*vl[st]*(sa.len[st]-sa.len[sa.fail[st]]));as=max(as,dp[st]);
		for(int j=0;j<26;j++)if(sa.ch[st][j])dp[sa.ch[st][j]]=max(dp[sa.ch[st][j]],dp[st]+1ll*vl[sa.ch[st][j]]*(sa.len[sa.ch[st][j]]-sa.len[st]));
	}
	printf("%lld\n",as);
}
