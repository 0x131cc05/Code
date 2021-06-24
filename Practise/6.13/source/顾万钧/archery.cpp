/*
{
######################
#       Author       #
#        Gary        #
#        2021        #
######################
*/
#include<bits/stdc++.h>
#define rb(a,b,c) for(int a=b;a<=c;++a)
#define rl(a,b,c) for(int a=b;a>=c;--a)
#define LL long long
#define IT iterator
#define PB push_back
#define II(a,b) make_pair(a,b)
#define FIR first
#define SEC second
#define FREO freopen("check.out","w",stdout)
#define rep(a,b) for(int a=0;a<b;++a)
#define SRAND mt19937 rng(chrono::steady_clock::now().time_since_epoch().count())
#define random(a) rng()%a
#define ALL(a) a.begin(),a.end()
#define POB pop_back
#define ff fflush(stdout)
#define fastio ios::sync_with_stdio(false)
#define check_min(a,b) a=min(a,b)
#define check_max(a,b) a=max(a,b)
using namespace std;
//inline int read(){
//    int x=0;
//    char ch=getchar();
//    while(ch<'0'||ch>'9'){
//        ch=getchar();
//    }
//    while(ch>='0'&&ch<='9'){
//        x=(x<<1)+(x<<3)+(ch^48);
//        ch=getchar();
//    }
//    return x;
//}
const int INF=0x3f3f3f3f;
typedef pair<int,int> mp;
/*}
*/
const int MAXN=2e5+23;
int n,a[MAXN],r;
vector<int> nex(vector<int> v){
	vector<int> d(n/2+1),u(n/2+1);
	rb(i,1,n){
		d[(i+1)/2]=max(v[i],v[i+1]);
		u[(i+1)/2]=min(v[i],v[i+1]);
		i++;
	}
	swap(d[1],u[1]);
	int tmp=u[1];
	rb(i,1,n/2-1){
		u[i]=u[i+1];
	}
	u[n/2]=tmp;
	vector<int> vv(1,0);
	rb(i,1,n/2){
		vv.PB(d[i]);
		vv.PB(u[i]);
	}
	return vv;
}
int solve(vector<int> v,int z){
	rb(i,1,n) v=nex(v);
	if(z<=n/2+1){
		int d=0;
		rb(i,1,n){
			if(v[i]==z){
				d=(i+1)/2;
			}
		}
		(d--);
		d-=r;
		d+=n;
		d%=n/2;
		d++;
		return d;
	}
	else{
		rb(i,1,n){
			if(v[i]==z) return (i+1)/2;
		}
	}
	return 0;
}
int main(){
	freopen("archery.in","r",stdin);
	freopen("archery.out","w",stdout);
	scanf("%d%d",&n,&r);
	r-=2*n;
	r%=n;
	n<<=1;
	rb(i,1,n) scanf("%d",&a[i]);
	int is,ans;
	if(a[1]==1){
		cout<<n/2<<endl;
		return 0;
	}
	is=INF,ans=-1;
	rb(i,0,n-1){
		vector<int> v(1);
		rb(j,1,i){
			v.PB(a[1+j]);
		}
		v.PB(a[1]);
		rb(j,i+1,n-1){
			v.PB(a[1+j]);
		}
		int tmp=solve(v,a[1]);
		if(tmp<=is){
			is=tmp;
			ans=(i+2)/2;
		}
	}
	printf("%d\n",ans);
	return 0;
}