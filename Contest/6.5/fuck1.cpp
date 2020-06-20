#include<bits/stdc++.h>
#define ll long long
#define lld long ll
using namespace std;
template<typename tn> void read(tn &a){
	tn x=0,f=1; char c=' ';
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	a=x*f;
}
const int N = 10010,mod = 998244353;
ll h[N];
int n,m;
ll fp(ll a,ll k){
	ll ans=1;
	for(;k;k>>=1,a=a*a%mod)
		if(k&1) ans=a*ans%mod;
	return ans;
}
void BM(ll *a,int n,vector<ll>&ans){
	ans.clear();
	vector<ll> lst;
	int w=0;ll delta=0;
	for(int i=1;i<=n;i++){
		ll tmp=0;
		for(int j=0;j<ans.size();j++)
			tmp=(tmp+a[i-1-j]*ans[j])%mod;
		if((a[i]-tmp)%mod==0) continue;
		if(!w){
			w=i;delta=a[i]-tmp;
			for(int j=i;j;j--) ans.push_back(0);
			continue;
		}
		vector<ll> now=ans;
		ll mul=(a[i]-tmp)*fp(delta,mod-2)%mod;
		if(ans.size()<lst.size()+i-w) ans.resize(lst.size()+i-w);
		ans[i-w-1]=(ans[i-w-1]+mul)%mod;
		for(int j=0;j<lst.size();j++) ans[i-w+j]=(ans[i-w+j]-mul*lst[j])%mod;
		if(now.size()-i<lst.size()-w){
			lst=now;w=i;delta=a[i]-tmp;
		}
	}
}
ll calc(int m,vector<ll>&coef,ll*h){
	if(m<=coef.size()) return h[m];
	int k=coef.size();
	static ll f[N],g[N],res[N],p[N];
	p[0]=-1;
	for(int i=1;i<=k;i++) p[i]=coef[i-1];
	for(int i=0;i<=2*k;i++) f[i]=g[i]=0;
	f[0]=1;
	if(k>1) g[1]=1;
	else g[0]=p[0];
	auto mul = [&](ll *a,ll *b,ll *c){
		for(int i=0;i<=2*k;i++) res[i]=0;
		for(int i=0;i<k;i++)
			for(int j=0;j<k;j++)
				res[i+j]=(res[i+j]+a[i]*b[j])%mod;
		for(int i=2*k;i>=k;i--)
			if(res[i]%mod)
				for(int j=k;~j;j--)
					res[i-j]=(res[i-j]+res[i]*p[j])%mod;
		for(int i=0;i<2*k;i++) c[i]=res[i];
		return 0;
	};
	for(;m;m>>=1,mul(g,g,g))
		if(m&1) mul(f,g,f);
	ll ans=0;
	for(int i=0;i<k;i++)
		ans=(ans+h[i+1]*f[i])%mod;
	return ans;
}
int main(){
	read(n);read(m);
	for(int i=1;i<=n;i++)
		read(h[i]);
	vector<ll> ans;
	BM(h,n,ans);
	cout << ans.size() << endl;
	for(auto x:ans) cout<<(x+mod)%mod<<' ';
	cout<<'\n';
	cout<<(calc(m,ans,h)+mod)%mod<<'\n';
	return 0;
}
