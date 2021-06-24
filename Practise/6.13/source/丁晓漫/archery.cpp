#include<bits/stdc++.h>
using namespace std;

mt19937 rnd((unsigned long long)new char);

const int maxn=1005;
const int H1=20160224;
const int mod1=998244353;
const int H2=23333333;
const int mod2=1e9+7;
int n,k,ans,apos,len,pos;
int a[maxn],aa[maxn],b[maxn],c[maxn],d[maxn],z[maxn][maxn];
class Hashint{
public:
	int h1,h2;
	Hashint():h1(0),h2(0){}
	Hashint(int _h1,int _h2):h1(_h1),h2(_h2){}
	Hashint operator+(const Hashint &o)const{
		return Hashint(h1+o.h1>=mod1?h1+o.h1-mod1:h1+o.h1,h2+o.h2>=mod2?h2+o.h2-mod2:h2+o.h2);
	}
	Hashint operator*(const Hashint &o)const{
		return Hashint(1LL*h1*o.h1%mod1,1LL*h2*o.h2%mod2);
	}
	bool operator<(const Hashint &o)const{
		return h1<o.h1||(h1==o.h1&&h2<o.h2);
	}
}h,H(H1,H2),hh[2][maxn];
map<Hashint,int>mp;

void fix(int *x){
	for(int i=1;i<=n;i++)
		if(x[2*i-1]<x[2*i])swap(x[2*i-1],x[2*i]);
}
Hashint calc(int *x){
	Hashint h;
	for(int i=1;i<=2*n;i++)
		h=h*H+hh[x[i]][i];
	return h;
}

void solve(int *x,int *y){
	mp.clear();
	for(int i=1;i<=2*n;i++)
		z[0][i]=x[i];
	fix(z[0]);
	mp[calc(z[0])]=0;
	len=0;pos=-1;
	for(int i=1;i<=k;i++){
		for(int j=1;j<n;j++){
			z[i][2*j]=z[i-1][2*j+2];
			z[i][2*j+1]=z[i-1][2*j+1];
		} 
		z[i][1]=z[i-1][2];
		z[i][2*n]=z[i-1][1];
		fix(z[i]);
		Hashint cur=calc(z[i]);
		if(mp.count(cur)){
			len=i-mp[cur];
			pos=mp[cur];
			break;
		}
		mp[cur]=i;
	}
	for(int i=1;i<=2*n;i++)y[i]=z[(k-pos)%len+pos][i];
}

int main(){
	freopen("archery.in","r",stdin);
	freopen("archery.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(int i=1;i<=2*n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=2*n;i++)for(int f=0;f<2;f++)
		hh[f][i]=Hashint(rnd()%H1,rnd()%H2);
	ans=2*n+1;
	for(int i=1;i<=2*n;i++){
		for(int j=1;j<i;j++)aa[j]=a[j+1];
		aa[i]=a[1];
		for(int j=i+1;j<=2*n;j++)aa[j]=a[j];
		for(int j=1;j<=2*n;j++)b[j]=(aa[j]<a[1]?0:1);
		solve(b,c);
		for(int j=1;j<=2*n;j++)b[j]=(aa[j]<=a[1]?0:1);
		solve(b,d);
		int cans=0;
		for(int j=1;j<=2*n;j++)if(c[j]!=d[j])cans=(j+1)/2;
		if(cans<=ans)
			ans=cans,apos=(i+1)/2;
	}
	printf("%d\n",apos);
	return 0;
}
