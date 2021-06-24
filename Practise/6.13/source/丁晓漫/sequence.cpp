#include<bits/stdc++.h>
using namespace std;

const int maxn=50005;
const long long Inf=1e18;
int n,q;
int a[maxn],l[maxn],r[maxn],k[maxn],ord[maxn];
vector<int>ver[maxn];
long long x;
long long ans[maxn],low[maxn],high[maxn];

bool cmp(int u,int v){
	return low[u]+high[u]>low[v]+high[v];
}
 
class Convex{
public:
	int pt,sz;
	vector<long long>vec;
	Convex(){
		pt=sz=0;
		vec.clear();
	}
	Convex(int _sz){
		pt=0;sz=_sz;
		vec.clear();
		vec.resize(sz);
	}
	Convex shift(){
		Convex res=*this;
		res.vec.erase(res.vec.begin());
		res.sz--;
		return res;
	}
	Convex operator+(const Convex &o)const{
		Convex res(max(sz,o.sz));
		for(int i=0;i<res.sz;i++)
			res.vec[i]=max((i<sz?vec[i]:-Inf),(i<o.sz?o.vec[i]:-Inf));
		return res;
	}
	Convex operator*(const Convex &o)const{
		if(!sz||!o.sz)return Convex(0);
		Convex res(sz+o.sz-1);
		res.vec[0]=vec[0]+o.vec[0];
		int i=0,oi=0,ri=1;
		while(i+1<sz||oi+1<o.sz){
			if(oi+1==o.sz||(i+1<sz&&vec[i+1]-vec[i]>=o.vec[oi+1]-o.vec[oi]))
				res.vec[ri]=res.vec[ri-1]+vec[i+1]-vec[i],i++;
			else
				res.vec[ri]=res.vec[ri-1]+o.vec[oi+1]-o.vec[oi],oi++;
			ri++;
		}
		return res;
	}
	pair<long long,int>calc(){
		if(vec.empty())return make_pair(-Inf,-1);
		while(pt+1<sz&&vec[pt+1]-vec[pt]>=x)
			pt++;
		return make_pair(vec[pt]-pt*x,pt);
	}
	void print(){
		for(int i=0;i<sz;i++)cerr<<vec[i]<<" ";
		cerr<<endl;
	}
};
class Info{
public:
	long long val[2][2];
	int cnt[2][2];
	Info(){
		val[0][0]=val[0][1]=val[1][0]=val[1][1]=-Inf;
		cnt[0][0]=cnt[0][1]=cnt[1][0]=cnt[1][1]=-1;
	}
	Info operator*(const Info &o)const{
		Info res;
		for(int a=0;a<2;a++)for(int b=0;b<2;b++){
			res.val[a][b]=val[a][0]+o.val[0][b];
			res.cnt[a][b]=cnt[a][0]+o.cnt[0][b];
			if(val[a][1]+o.val[1][b]+x>res.val[a][b]||
				(val[a][1]+o.val[1][b]+x==res.val[a][b]&&cnt[a][1]+o.cnt[1][b]-1>res.cnt[a][b])){
					res.val[a][b]=val[a][1]+o.val[1][b]+x;
					res.cnt[a][b]=cnt[a][1]+o.cnt[1][b]-1;
				}
		}
		return res;
	}
};
namespace Segtree{
	Convex t[maxn*4][2][2];
	int pt[maxn*4][2][2];
	void build(int cur,int l,int r){
		if(l==r){
			t[cur][0][0].vec.push_back(0);
			t[cur][0][0].vec.push_back(a[l]);
			t[cur][0][0].sz=2;
			t[cur][1][1].vec.push_back(-Inf);
			t[cur][1][1].vec.push_back(a[l]);
			t[cur][1][1].sz=2;
			t[cur][0][1]=t[cur][1][0]=t[cur][1][1];
			return;
		}
		int mid=l+r>>1;
		build(cur<<1,l,mid);
		build(cur<<1|1,mid+1,r);
		for(int a=0;a<2;a++)for(int b=0;b<2;b++)for(int c=0;c<2;c++){
			Convex tmp=t[cur<<1][a][c]*t[cur<<1|1][c][b];
			if(c)tmp=tmp.shift();
			t[cur][a][b]=t[cur][a][b]+tmp;
		} 
	}
	void reset(int cur,int l,int r){
		for(int a=0;a<2;a++)for(int b=0;b<2;b++)
			t[cur][a][b].pt=0;
		if(l==r)return;
		int mid=l+r>>1;
		reset(cur<<1,l,mid);
		reset(cur<<1|1,mid+1,r);
	}
	Info query(int cur,int l,int r,int vl,int vr){
		if(l>=vl&&r<=vr){
			Info res;
			for(int a=0;a<2;a++)for(int b=0;b<2;b++){
				pair<long long,int>tmp=t[cur][a][b].calc();
				res.val[a][b]=tmp.first;
				res.cnt[a][b]=tmp.second;
			}
			return res;
		}
		int mid=l+r>>1;
		if(vr<=mid)return query(cur<<1,l,mid,vl,vr);
		else if(vl>mid)return query(cur<<1|1,mid+1,r,vl,vr);
		else return query(cur<<1,l,mid,vl,vr)*query(cur<<1|1,mid+1,r,vl,vr);
	}
}

int main(){
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	Segtree::build(1,1,n);
	for(int i=1;i<=q;i++){
		scanf("%d%d%d",&l[i],&r[i],&k[i]);
		low[i]=-1e9;
		high[i]=1e9;
		ord[i]=i;
	}
	for(int t=1;t<=31;t++){
		sort(ord+1,ord+1+q,cmp);
		Segtree::reset(1,1,n);
		for(int i=1;i<=q;i++){
			int j=ord[i];
			x=(low[j]+high[j]+1)/2;
			int ck=Segtree::query(1,1,n,l[j],r[j]).cnt[0][0];
			if(ck<k[j])high[j]=x-1;
			else low[j]=x;
		}
	}
	sort(ord+1,ord+1+q,cmp);
	Segtree::reset(1,1,n);
	for(int i=1;i<=q;i++){
		int j=ord[i];
		x=(low[j]+high[j])/2;
		ans[j]=Segtree::query(1,1,n,l[j],r[j]).val[0][0]+k[j]*x;
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
	return 0;
}
