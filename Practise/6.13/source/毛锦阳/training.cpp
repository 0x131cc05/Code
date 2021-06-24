#include<bits/stdc++.h>
using namespace std; 
#define rep(i,j,k) for(int i=(j);i<=(k);i++) 
const int N=5145;
struct edge{int x,y,nt,w;}e[N<<1],g[N<<1];
int n,m,as=1e9,tt=1,po,ct,pd;
int v[N],hd[N],st[N],d[1145][1145];
void add(int x,int y,int z){e[++tt]={x,y,hd[x],z};hd[x]=tt;}
void getd(int x,int fa,int s){
	for(int i=hd[x],y;i;i=e[i].nt)if((y=e[i].y)!=fa&&e[i].w==0){
		d[s][y]=d[s][x]+1;getd(y,x,s);
	}
}

int main(){freopen("training.in","r",stdin);freopen("training.out","w",stdout);
	scanf("%d%d",&n,&m); int x,y,z; 
	rep(i,1,m){scanf("%d%d%d",&x,&y,&z),add(x,y,z),add(y,x,z);
	}rep(i,1,n)getd(i,0,i);
	rep(i,1,m)if((d[e[i*2].x][e[i*2].y]%2==0)&&e[i*2].w)st[++po]=i;else ct+=e[i*2].w,v[i]=1;
	printf("%d\n",ct);
} 
