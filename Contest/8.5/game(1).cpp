#include<cstdio>
#include<cmath>
#include<queue>
#include<cstdlib>
using namespace std;
#define N 5050
#define S 1050000
#define md 998244353
int n,p,s[N],s1[N],ct1,s2[N],ct2,fu[N],c1,phi,v1,v2,g,f1[S],tp[N],p1[N][21];
int gcd(int a,int b){return b?gcd(b,a%b):a;}
struct ht{
	int hd[S],vl[S],v1[S],nt[S],ct;
	queue<int> st;
	void ins(int x,int y){v1[++ct]=y;vl[ct]=x;nt[ct]=hd[x&1048575];hd[x&1048575]=ct;st.push(x&1048575);}
	int query(int x){for(int i=hd[x&1048575];i;i=nt[i])if(vl[i]==x)return v1[i];return -1;}
	void init(){while(!st.empty())hd[st.front()]=0,st.pop();ct=0;}
}t;
int pw(int a,int p,int mod){int as=1;while(p){if(p&1)as=1ll*as*a%mod;a=1ll*a*a%mod;p>>=1;}return as;}
int getg()
{
	for(int i=2;i<p;i++)
	{
		int fg=1;
		for(int j=1;j<=c1;j++)if(pw(i,phi/fu[j],p)==1)fg=0;
		if(fg)return i;
	}
}
void pre()
{
	int tp=100;
	int st=pw(g,tp,p),st2=1;
	for(int i=1;i<=1e6;i++)st2=1ll*st2*st%p,f1[i]=st2;
	for(int i=1e6;i>=1;i--)t.ins(f1[i],i*tp);
}
int bsgs(int a,int p,int k)
{
	int s1=k,as=1e9;
	for(int i=1;i<=120;i++)
	{
		s1=1ll*s1*a%p;int f1=t.query(s1);
		if(f1!=-1){int tp2=f1-i;if(as>tp2&&tp2>=0)as=tp2;}
	}
	return as;
}
int main()
{
	// freopen("game.in","r",stdin);
	// freopen("game.out","w",stdout);
	scanf("%d%d",&n,&p);v1=p,v2=1;
	for(int i=2;i*i<=p;i++)
	{
		long long st=i,q1=1;
		while(st*i<=p)st*=i,q1++;
		if(st==p){v1=i,v2=q1;break;}
	}
	phi=p/v1*(v1-1);
	int s21=phi;
	for(int i=2;i*i<=s21;i++)
	if(s21%i==0)
	{
		fu[++c1]=i;
		while(s21%i==0)s21/=i;
	}
	if(s21>1)fu[++c1]=s21;
	g=getg();pre();
	if(v2==1)
	{
		for(int i=1;i<=n;i++)scanf("%d",&s[i]),s1[i]=gcd(bsgs(g,p,s[i]),phi);
		int as=0;
		for(int i=1;i<=n;i++)
		{
			int ct=0,t1=1;
			for(int j=1;j<i;j++)if(s1[i]%s1[j]!=0)ct++;
			for(int j=i+1;j<=n;j++)if(s1[i]%s1[j]!=0||s1[i]==s1[j])ct++;
			for(int j=1;j<=ct;j++)t1=2*t1%md;
			as=(as+t1)%md;
		}
		printf("%d\n",as);
	}
	else
	{
		int as=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&s[i]);
			if(gcd(s[i],p)>1)s2[++ct2]=s[i];
			else s1[++ct1]=gcd(bsgs(g,p,s[i]),phi);
		}
		for(int i=1;i<=ct1;i++)
		{
			int ct=ct2,t1=1;
			for(int j=1;j<i;j++)if(s1[i]%s1[j]!=0)ct++;
			for(int j=i+1;j<=ct1;j++)if(s1[i]%s1[j]!=0||s1[i]==s1[j])ct++;
			for(int j=1;j<=ct;j++)t1=2*t1%md;
			as=(as+t1)%md;
		}
		for(int i=1;i<=ct2;i++)
		{
			int tp1=s2[i];
			while(tp1%v1==0)tp1/=v1,tp[i]++;
			int r1=s2[i],r2=1;
			for(int j=1;j<=20;j++)r2=1ll*r2*r1%p,p1[i][j]=r2;
		}
		for(int i=1;i<=ct2;i++)
		{
			int ct=ct1,t1=1;
			for(int j=1;j<=ct2;j++)if(j!=i)
			{
				int fg=1;
				if(tp[i]%tp[j]==0)
				{
					int st=tp[i]/tp[j];
					if(p1[j][st]==s2[i])fg=0;
				}
				ct+=fg;
			}
			for(int j=1;j<=ct;j++)t1=2*t1%md;
			as=(as+t1)%md;
		}
		printf("%d\n",as);
	}
}
