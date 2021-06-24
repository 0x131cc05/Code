#include<bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for(int i=(j);i<=(k);i++)
const int N=10004;
int n,q,sp,mx,nw,a[N],s[N],f[2][N],w[10005][10005];
int main(){freopen("sequence.in","r",stdin);freopen("sequence.out","w",stdout);;
	scanf("%d%d",&n,&q);
	rep(i,1,n)scanf("%d",&a[i]),w[i][i]=a[i],s[i]=s[i-1]+a[i],sp|=a[i]<0;
	if(n<=10000)rep(i,1,n){nw=mx=0;rep(j,i,n){
		nw+=a[j];nw=max(0,nw);mx=max(nw,0);
		if(i!=j)w[i][j]=mx;
	}}int l,r,k,as;
	rep(i,1,q){scanf("%d%d%d",&l,&r,&k);as=-1e9;
		if(!sp){printf("%d\n",s[r]-s[l-1]);continue;}nw=0;
		rep(j,l,r)f[0][j]=w[l][j];
		rep(i,2,k){nw^=1;memset(f[nw],0xac,sizeof(f[nw]));
			rep(j,l+i-1,r){
				rep(p,l+i-2,j-1)f[nw][j]=max(f[nw][j],f[nw^1][p]+w[p+1][j]);
			}
		}rep(i,l,r)as=max(f[nw][i],as);printf("%d\n",as);
	}
}
