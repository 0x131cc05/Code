#include <cstdio>
const int N=2e5+5;
long long T;
int n;
bool a[N],b[N];

void solve() {
	// 0 a[1~n] 0 a[1~n]
	int len=2*n+2;
	for(long long S=1;S<=T;S<<=1) {
		if(T&S) {
			for(int i=1;i<=n;++i) {
				int l=i-S%len,r=i+S%len;
				if(l<0) l=-l;
				if(l>n+1) l=len-l;
				if(r>n+1) r=len-r;
				if(r<0) r=-r;
				b[i]=a[l]^a[r];
			}
			for(int i=1;i<=n;++i) a[i]=b[i];
		}
	}
}
int main() {
	scanf("%lld%d",&T,&n);
	while(getchar()!='\n');
	for(int i=1;i<=n;++i) a[i]=getchar()^48;
	solve();
	for(int i=1;i<=n;++i) putchar(a[i]+'0');
	puts("");
	return 0;
}

