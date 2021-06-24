#include<bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for(int i=(j);i<=(k);i++)
#define per(i,j,k) for(int i=(j);i>=(k);i--)
#define pii pair<int,int>
#define fi first
#define se second
const int N=414514;
pii as,fw[N];
int n,m,k,a[N],ct,mn=1e9,po=1;
int b[N],al[2][N>>1],nw[2],cn[2];
pii qsol(int l){memset(al,0,sizeof(al));
	if(fw[l].fi)return fw[l];
	rep(i,2,2*l-1)b[i]=a[i];b[2*l]=k;
	rep(i,2*l,2*n)b[i+1]=a[i]; 
	rep(i,2,2*n+1)if(i!=2*l&&b[i]<k)al[0][i/2]++;al[1][l]=1;nw[0]=nw[1]=0;
	int x=1,tt=0,ww=0,mx,nmd=0;
	while(1145){cn[0]=nw[0]+al[0][x];cn[1]=nw[1]+al[1][x];
		if(cn[0]+cn[1]>=2){
			mx=cn[1]?1:0;nw[1]=cn[1],nw[0]=cn[0];al[0][x]=al[1][x]=0;
			if(x>1)nw[0]--,al[0][x]++;
			else nw[mx]--,al[mx][x]++;
		}else{if(x>1)al[0][x]=cn[0],al[1][x]=cn[1],nw[0]=nw[1]=0;
			else nw[0]=cn[0],nw[1]=cn[1],al[0][x]=al[1][x]=0;
		}if(nw[1]&&x==1)nmd++;
		x--;if(!x)x=n;
		if(x==1){ww++;if(ww==3)break;}
	}
	rep(i,2,n)if(al[1][i]){return fw[l]={i,nmd};}
}
int sol(int l){
	rep(i,2,2*l-1)b[i]=a[i];b[2*l]=k;
	rep(i,2*l,2*n)b[i+1]=a[i]; 
	int sp=1,nw,x=m;
	while(x--){sp=0;
		per(i,n,2){if(b[2*i+1]<b[2*i])swap(b[2*i+1],b[2*i]);
			if(b[2*i+1]<n||b[2*i+1]==2*n)sp=1;swap(ct,b[2*i+1]);
		}if(b[2]<b[3])swap(b[2],b[3]);if(b[3]<n||b[3]==2*n)sp=1;
		swap(b[3],b[2*n+1]);b[3]=ct;
		if(!sp)break;
	}x=max(x,0);
	rep(i,2,2*n+1)if(b[i]==k)nw=i/2;
	if(k>=n&&k!=2*n)nw=((nw-x)%n+n)%n;if(!nw)nw=n;
	return nw;
}
pii aiae(int x){
	int l=x+1,r=n,nw=qsol(x).se,jw=x;
	while(l<=r){int mi=(l+r)>>1;
		if(qsol(mi).se==nw)jw=mi,l=mi+1;
		else r=mi-1;
	}return {nw,jw};
}
int get(int x){
	int l=x+1,r=n,nw=qsol(x).fi,jw=x;
	while(l<=r){int mi=(l+r)>>1;
		if(qsol(mi).fi==nw)jw=mi,l=mi+1;
		else r=mi-1;
	}return jw;
}
int main(){freopen("archery.in","r",stdin);freopen("archery.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);k=2*n-k+1;
	if(k==2*n)printf("%d",n),exit(0);
	rep(i,2,2*n)scanf("%d",&a[i]),a[i]=2*n-a[i]+1;as={1e9,0};
	if(k>=n){
		rep(i,1,n)if(sol(i)<=as.fi)as={sol(i),i};
		printf("%d\n",as.se);return 0;
	}
	while(po<=n){
		pii t=aiae(po);
		if(t.fi<=as.fi)as={t.fi,po};
		po=t.se+1;
	}printf("%d\n",get(as.se));
}
