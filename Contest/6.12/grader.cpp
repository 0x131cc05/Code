#include<cstdio>
#include<algorithm>
#include"module.h"
#define ll long long
int T,x,y,ct;
ll mul(ll x,ll y,ll mod){ll tmp=(long double)x*y/mod;return (x*y-tmp*mod+mod)%mod;}
ll pw(ll a,ll p,ll k){ll as=1;while(p){if(p&1)as=mul(as,a,k);a=mul(a,a,k);p>>=1;}return as;}
static ll f[11]={2,3,7,61,24251},tp[70];
bool mrtest(ll a,ll p){ll ct=0,st2=p-1;while(~st2&1)st2>>=1,ct++;tp[0]=pw(a,st2,p);for(int i=1;i<=ct;i++)tp[i]=mul(tp[i-1],tp[i-1],p);if(tp[ct]!=1)return 0;for(int i=ct;i>0;i--)if(tp[i]==1&&(tp[i-1]>1&&tp[i-1]<p-1))return 0;else if(tp[i]!=1)return 1;return 1;}
bool mr(ll p){if(p==1)return 0;for(int i=0;i<5;i++)if(f[i]==p)return 1;for(int i=0;i<5;i++)if(!mrtest(f[i],p))return 0;return 1;}
ll Query(ll q)
{
	ct++;
	if(ct>5)
	{
		std::printf("Wrong Answer more than 5 Query");
		std::exit(0);
	}
	if(q<1e9)
	{
		std::printf("Wrong Answer q<10^9");
		std::exit(0);
	}
	if(q>1e10)
	{
		std::printf("Wrong Answer q>10^10");
		exit(0);
	}
	if(!mr(q))
	{
		std::printf("Wrong Answer q is not a prime");
		std::exit(0);
	}
	return mul(x,pw(y,q-2,q),q);
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		x=y=0;
		scanf("%d%d",&x,&y);
		ct=0;
		std::pair<int,int> st=Solve();
		if(st.first<=0||st.first>1e9)
		{
			std::printf("Wrong Answer x not in [1,10^9]");
			std::exit(0);
		}
		if(st.second<=0||st.second>1e9)
		{
			std::printf("Wrong Answer y not in [1,10^9]");
			std::exit(0);
		}
		if(1ll*x*st.second!=1ll*y*st.first)
		{
			std::printf("Wrong Answer incorrect x/y");
			std::exit(0);
		}
	}
	printf("Accepted");
	exit(0);
}
