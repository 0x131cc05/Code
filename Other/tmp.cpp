#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N=2e5+5;
const int inf=1e9;
int n,m,l,r,ans;
int a[N],p[N],dp[N];
inline void init(){
    for (int i=1;i<=n;++i)
        r=max(r,a[i+1]-a[i]-1);
    for (int i=1;i<=n;++i)
        if (a[i+1]-a[i]-1==r){
            for (int j=1;j<=n;++j) p[j]=a[i+j];
            for (int j=n;j;--j) p[j]-=p[1];
            return;
        }
}
inline bool chk(int x){
	for (int i = 1; i <= n; i++) cout << p[i] << ' ';
	puts("");
    for (int st=1;st<=2;++st){
        dp[st]=(st==1)?0:max(p[st],x);
        for (int i=st+1;i<=n;++i){
            dp[i]=dp[i-1];
            if (dp[i-1]>=p[i]-1) dp[i]=p[i]+x;
            if (dp[i-1]>=p[i]-x-1) dp[i]=max(dp[i],p[i]);
            if (i!=st+1 && dp[i-2]>=p[i]-x-1) dp[i]=max(dp[i],p[i-1]+x);
			cout << st << ' ' << i << ' ' << p[i] << ' ' << dp[i] << endl;
        }
        if (dp[n]>=min(m-1,m+p[st]-x-1)) return 1;
    }
    return 0;
}

inline int read() {
	int x; scanf("%d", &x);
	return x;
}

int main(){
    m=read(),n=read();
    if (n==1) return printf("%d\n",m-1),0;
    for (int i=1;i<=n;++i) 
        a[i+n]=(a[i]=read())+m;
    sort(a+1,a+(n<<1)+1),init();
	cout << chk(1) << endl;
    while (l<=r){
        int mid=(l+r)>>1;
        if (chk(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
    printf("%d\n",ans);
    return 0;
}