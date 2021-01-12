#include<bits/stdc++.h>
using namespace std;

#define IN inline
#define CO const
typedef long long int64;

template<typename type>
IN type read(){
	type x=0,w=1;char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-') w=-w;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	return x*w;
}
template<>
IN char read<char>(){
	char x=getchar();
	while(!isalpha(x)) x=getchar();
	return x;
}
template<typename type>
IN type&read(type&x){
	return x=read<type>();
}
template<typename type,typename...others>
IN void read(type&x,others&...y){
	x=read<type>(),read(y...);
}
template<typename type>
IN void write(type x){
	if(x<0) putchar('-'),x=-x;
	if(x>=10) write(x/10);
	putchar('0'+x%10);
}
template<>
IN void write<char>(char x){
	putchar(x);
}
template<typename type,typename...others>
IN void write(type x,others...y){
	write(x),write(y...);
}

CO int N=1e5+10,inf=2e9;
int n,m,a[N];
int lg[N],st[17][N];

IN int range_min(int l,int r){
	if(l>r) return inf;
	int k=lg[r-l+1];
	return min(st[k][l],st[k][r-(1<<k)+1]);
}
int seekl(int r,int lim){
	for(int i=lg[n];i>=0;--i)
		if(r>=1<<i and st[i][r-(1<<i)+1]>lim) r-=1<<i;
	return r;
}
int seekr(int l,int lim){
	for(int i=lg[n];i>=0;--i)
		if(l+(1<<i)-1<=n and st[i][l]>lim) l+=1<<i;
	return l;
}

int root1[N],root2[N],tot;
int tree[N*100],lc[N*100],rc[N*100];

void insert(int&x,int l,int r,int p,int v){
	++tot,lc[tot]=lc[x],rc[tot]=rc[x];
	tree[tot]=tree[x]+v,x=tot;
	if(l==r) return;
	int mid=l+((r-l)>>1);
	if(p<=mid) insert(lc[x],l,mid,p,v);
	else insert(rc[x],mid+1,r,p,v);
}
int query(int x,int y,int l,int r,int ql,int qr){
	if(ql<=l and r<=qr) return tree[y]-tree[x];
	int mid=l+((r-l)>>1);
	if(qr<=mid) return query(lc[x],lc[y],l,mid,ql,qr);
	if(ql>mid) return query(rc[x],rc[y],mid+1,r,ql,qr);
	return query(lc[x],lc[y],l,mid,ql,qr)+query(rc[x],rc[y],mid+1,r,ql,qr);
}

int main(){
	read(n,m);
	lg[0]=-1;
	for(int i=1;i<=n;++i) lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;++i) st[0][i]=read(a[i]);
	for(int k=1;k<=lg[n];++k)for(int i=1;i+(1<<k)-1<=n;++i)
		st[k][i]=min(st[k-1][i],st[k-1][i+(1<<(k-1))]);
	for(int i=1;i<=n;++i){
		root1[i]=root1[i-1];
		insert(root1[i],0,inf,a[i],1);
		root2[i]=root2[i-1];
		int pre=seekl(i,a[i]-1),nex=seekr(i+1,a[i]);
		if(1<=pre and pre<=n){
			insert(root2[i],0,inf,a[i]+max(a[pre],a[nex]),1);
			insert(root2[i],0,inf,2*a[i],-1);
		}
	}
	while(m--){
		int l=read<int>(),r=read<int>(),k=read<int>();
		int sl=0,sr=inf;
		while(sl<sr){
			int s=sl+((sr-sl)>>1);
			int ans=query(root1[l-1],root1[r],0,inf,0,s/2);
			if(ans){
				int dl=seekr(l,s/2),dr=seekl(r,s/2);
				ans+=query(root2[dl],root2[dr-1],0,inf,0,s);
				ans+=min(range_min(l,dl-1),range_min(dr+1,r))<=s-max(a[dl],a[dr]);
			}
			ans<k?sl=s+1:sr=s;
		}
		write(sl,'\n');
	}
	return 0;
}