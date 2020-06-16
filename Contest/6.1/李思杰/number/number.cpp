#include<bits/stdc++.h>
using namespace std;
#define I inline int
#define V inline void
#define ll long long int
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define ROF(i,a,b) for(int i=a;i>=b;i--)
const int N=1<<19|1,mod=998244353;
V check(int&x){x-=mod,x+=x>>31&mod;}
I Pow(ll t,int x){
	ll s=1;
	for(;x;x>>=1,t=t*t%mod)if(x&1)s=s*t%mod;
	return s;
}
namespace poly{
	int lmt,w[N],r[N];
	V init(int n){
		int l=-1,wn;
		for(lmt=1;lmt<=n;)lmt<<=1,l++;
		FOR(i,0,lmt-1)r[i]=(r[i>>1]>>1)|((i&1)<<l);
		wn=Pow(3,mod>>++l),w[lmt>>1]=1;
		FOR(i,(lmt>>1)+1,lmt-1)w[i]=1ll*w[i-1]*wn%mod;
		ROF(i,(lmt>>1)-1,1)w[i]=w[i<<1];
	}
	V cl(int*a,int n){memset(a,0,n<<2);}
	I getLen(int n){return 1<<32-__builtin_clz(n);}
	V mul(int*a,int x,int n,int*b){while(n--)*b++=1ll**a++*x%mod;}
	V dot(int*a,int*b,int n,int*c){while(n--)*c++=1ll**a++**b++%mod;}
	V DFT(int*a,int l){
		static unsigned ll tmp[N];
		int u=__builtin_ctz(lmt/l),t;
		FOR(i,0,l-1)tmp[i]=a[r[i]>>u];
		for(int i=1;i^l;i<<=1)for(int j=0,d=i<<1;j^l;j+=d)FOR(k,0,i-1)
			t=tmp[i|j|k]*w[i|k]%mod,tmp[i|j|k]=tmp[j|k]+mod-t,tmp[j|k]+=t;
		FOR(i,0,l-1)a[i]=tmp[i]%mod;
	}
	V IDFT(int*a,int l){reverse(a+1,a+l),DFT(a,l),mul(a,mod-mod/l,l,a);}
	V Inv(const int*a,int n,int*b){
		static int A[N],B[N],tmp[N],d,l;
		tmp[0]=Pow(a[0],mod-2),cl(A,d),cl(B,d);
		for(d=1,l=2;d<n;d<<=1,l<<=1){
			copy(a,a+min(l,n),A),copy(tmp,tmp+d,B);
			DFT(A,l),DFT(B,l),dot(A,B,l,A),IDFT(A,l);
			cl(A,d),DFT(A,l),dot(A,B,l,A),IDFT(A,l);
			copy(A+d,A+l,tmp+d),mul(tmp+d,mod-1,d,tmp+d);
		}
		copy(tmp,tmp+n,b);
	}
	int*f[N],*g[N],bin[N<<5],*np(bin);
	V Mul(int*a,int*b,int n,int m,int*c){
		static int A[N],B[N],l;
		l=getLen(n+m-1),copy(a,a+n,A),copy(b,b+m,B);
		DFT(A,l),DFT(B,l),dot(A,B,l,A),IDFT(A,l);
		copy(A,A+n+m-1,c),cl(A,l),cl(B,l);
	}
	V eva_init(int p,int l,int r,int*a){
		g[p]=np,np+=r-l+2,f[p]=np,np+=r-l+2;
		if(l==r)return g[p][0]=1,check(g[p][1]=mod-a[l]);
		int lc=p<<1,rc=lc|1,mid=l+r>>1,len1=mid-l+2,len2=r-mid+1;
		eva_init(lc,l,mid,a),eva_init(rc,mid+1,r,a);
		Mul(g[lc],g[rc],len1,len2,g[p]);
	}
	V Mult(int*a,int*b,int n,int m,int*c){
		static int A[N],B[N],l;
		l=getLen(n),copy(a,a+n,A),reverse_copy(b,b+m,B);
		DFT(A,l),DFT(B,l),dot(A,B,l,A),IDFT(A,l);
		copy(A+m-1,A+n,c);
		cl(A,l),cl(B,l);
	}
	V eva_work(int p,int l,int r,int*a){
		if(l==r)return void(a[l]=f[p][0]);
		int lc=p<<1,rc=lc|1,mid=l+r>>1,len1=mid-l+2,len2=r-mid+1;
		Mult(f[p],g[rc],r-l+1,len2,f[lc]);
		eva_work(lc,l,mid,a);
		Mult(f[p],g[lc],r-l+1,len1,f[rc]);
		eva_work(rc,mid+1,r,a);
	}
	V eva(int*a,int*b,int n,int m,int*c){
		static int X[N],Y[N],l;
		eva_init(1,1,m,b),Inv(g[1],m+1,X);
		reverse(X,X+m+1),Mul(a,X,n,m+1,Y);
		copy(Y+n,Y+n+m,f[1]),eva_work(1,1,m,c);
		FOR(i,1,m)check(c[i]=1ll*c[i]*b[i]%mod+a[0]);
	}
}

int n, m, a[N], b[N], c[N];

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int r[N];

inline void NTT(int a[], int len, int type) {
    for (int i = 1; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2; mid <= len; mid <<= 1) {
        int Wn = Pow(3, type ? (mod - 1) / mid : mod - 1 - (mod - 1) / mid);
        for (int i = 0; i < len; i += mid)
            for (int j = i, w = 1, t; j < i + (mid >> 1); j++, w = (LL)w * Wn % mod)
                t = (LL)w * a[j + (mid >> 1)] % mod, a[j + (mid >> 1)] = (a[j] - t + mod) % mod, a[j] = (a[j] + t) % mod;
    }
    if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++)
        a[i] = (LL)a[i] * inv % mod;
}

int fuck[N], frac[N], inv[N];

int main() {
    freopen("number.in", "r", stdin), freopen("number.out", "w", stdout);
    int n; scanf("%d%d", &n, &m), poly::init((m + 1) * 2);
    for (int i = 0; i <= m; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++) b[i] = i;
    poly::eva(a, b, m + 1, m, c), c[0] = a[0], frac[0] = inv[0] = 1;
    for (int i = 1; i <= m; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    for (int i = 0; i <= m; i++) {
        fuck[i] = inv[i];
        if (i & 1) fuck[i] = mod - fuck[i];
        c[i] = (LL)c[i] * inv[i] % mod;
    }
    int len = 1, l = 0;
    while (len <= m * 2) len <<= 1, l++;
    for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
    NTT(c, len, 1), NTT(fuck, len, 1);
    for (int i = 0; i < len; i++) c[i] = (LL)c[i] * fuck[i] % mod;
    NTT(c, len, 0);
    int res = 0;
    for (int k = 0, w = 1; k <= m; w = (LL)w * (n - k) % mod, k++) {
        int tmp = c[k];
        res = (res + (LL)tmp * w % mod * Pow(2, n - k)) % mod;
    }
    printf("%d\n", res);
	return 0;
}
