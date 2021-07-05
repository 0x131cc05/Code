#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ui unsigned int
#define ull unsigned long long
#define db long double
#define pii pair<ll,int>
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define vi vector<int>
#define vii vector<vi>
#define lb lower_bound
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define per(i,b,a) for(register int i=(b);i>=(a);--i)
#define rep0(i,a,b) for(register int i=(a);i<(b);++i)
#define fore(i,a) for(register int i=0;i<a.size();++i)
#define gc() getchar()
inline int rd()
{
	int x=0;char c=gc();while(!isdigit(c))c=gc();
	while(isdigit(c))x=x*10+c-48,c=gc();return x;
}
const int N=300005,NN=1500005;
const db A=0.7,inf=10000000.0;
int n,q,a[NN],nxt[NN];char s[NN];
inline int kmp(int n,int m,int*a,int*b)
{
	int ans=0;nxt[0]=nxt[1]=0;
	for(int i=2,j=0;i<=m;i++)
	{
		while(j&&b[j+1]!=b[i])j=nxt[j];
		j+=(b[j+1]==b[i]);nxt[i]=j;
	}
	for(int i=1,j=0;i<=n;i++)
	{
		while(j&&b[j+1]!=a[i])j=nxt[j];
		j+=(b[j+1]==a[i]);ans+=(j==m);
	}
	return ans;
}
struct SgT
{
	int rt,tt,nn,a[N],q[N];
	struct st{int l,r,s;db w;}T[N];
	inline int sz(){return tt;}
	void del(int&x){if(!x)return;del(T[x].l);q[++nn]=x;del(T[x].r);x=0;}
	void rebuild(int&x,db dl,db dr,int l,int r)
	{
		if(l>r)return;db dm=(dl+dr)/2;int m=(l+r)/2;T[x=q[m]]=(st){0,0,r-l+1,dm};
		rebuild(T[x].l,dl,dm,l,m-1);rebuild(T[x].r,dm,dr,m+1,r);
	}
	void ins(int&x,db dl,db dr,int p,int o)
	{
		db dm=(dl+dr)/2;if(!x){T[x=p]=(st){0,0,1,dm};return;}T[x].s++;int ls=T[T[x].l].s,rs=T[T[x].r].s,ff=o;
		if(a[p]<a[x]||(a[p]==a[x]&&T[p-1].w<T[x-1].w))ff|=(A*T[x].s<=ls+1),ins(T[x].l,dl,dm,p,ff);
		else ff|=(A*T[x].s<=rs+1),ins(T[x].r,dm,dr,p,ff);
		if(ff&&!o){nn=0;del(x);rebuild(x,dl,dr,1,nn);}
	}
	void Ins(int c){a[++tt]=c;ins(rt,0,inf,tt,0);}
	inline void up(int x){T[x].s=T[T[x].l].s+T[T[x].r].s+1;}
	int merge(int x,int y)
	{
		if(!x||!y)return x|y;
		if(T[x].s>T[y].s){T[x].r=merge(T[x].r,y);up(x);return x;}
		T[y].l=merge(x,T[y].l);up(y);return y;
	}
	void del(int&x,db dl,db dr,int p)
	{
		if(x==p){x=merge(T[x].l,T[x].r);nn=0;del(x);rebuild(x,dl,dr,1,nn);return;}
		db dm=(dl+dr)/2;T[x].s--;T[p].w<T[x].w?del(T[x].l,dl,dm,p):del(T[x].r,dm,dr,p);
	}
/*	void del(int&x,int p)
	{
		if(x==p){x=merge(T[x].l,T[x].r);return;}
		T[x].s--;T[p].w<T[x].w?del(T[x].l,p):del(T[x].r,p);
	}*/
	void Del(){del(rt,0,inf,tt);tt--;}
	void build(int*b,int l,int r){del(rt);nn=0;tt=0;rep(i,l,r)Ins(b[i]);}
	int qry(int*b,int x,int n)
	{
		if(!x)return 0;int o=0;
		rep(i,1,n)if(a[x-i+1]!=b[i]){o=a[x-i+1]<b[i];break;}
		return o?T[T[x].l].s+1+qry(b,T[x].r,n):qry(b,T[x].l,n);
	}
	inline int qry(int n,int*b){return qry(b,rt,n+1)-qry(b,rt,n);}
}; 
struct DeQ
{
	int l,m,r,a[N],t[N];SgT T1,T2;
	inline void build(int*b,int L,int R)
	{
		m=N/2;int M=(L+R)/2;l=m-M+L;r=m-M+R;
		rep(i,L,R)t[m-M+i]=b[i];rep(i,l,r)a[i]=t[i];
		reverse(a+l,a+m+1);T1.build(a,l,m);
		reverse(a+l,a+m+1);T2.build(a,m+1,r);
	}
	inline int sz(){return r-l+1;}
	inline int lf(){return a[l];}
	inline int rg(){return a[r];}
	inline int gt(int p){return a[l+p-1];}
	inline void insl(int c){a[--l]=c;T1.Ins(c);}
	inline void insr(int c){a[++r]=c;T2.Ins(c);}
	inline void dell(){if(l==m+1)build(a,l,r);l++;T1.Del();}
	inline void delr(){if(r==m)build(a,l,r);r--;T2.Del();}
	inline int qry(int n,int*b)
	{
		int tt=0,sz1=min(T1.sz(),n-1),sz2=min(T2.sz(),n-1),ans=0;
		ans+=T1.qry(n,b);reverse(b+1,b+n+1);ans+=T2.qry(n,b);reverse(b+1,b+n+1);
		rep(i,1,sz1)t[++tt]=T1.a[i];reverse(t+1,t+tt+1);
		rep(i,1,sz2)t[++tt]=T2.a[i];return ans+kmp(tt,n,t,b); 
	} 
};
struct QuarQ
{
	int n,a[N];DeQ Q1,Q2;//Q1 with floor((n+1)/2) elements
	inline void build(int*b,int l,int r){int m=(l+r)/2;Q1.build(b,l,m);Q2.build(b,m+1,r);n=r-l+1;}
	inline void movl(){Q1.insr(Q2.lf());Q2.dell();}
	inline void movr(){Q2.insl(Q1.rg());Q1.delr();}
	inline void mov(){int m=(n+1)/2;while(Q1.sz()<m)movl();while(Q1.sz()>m)movr();}
	inline void insl(int c){Q1.insl(c);n++;mov();}
	inline void insr(int c){Q2.insr(c);n++;mov();}
	inline void insm(int c){if(n&1)movr();Q1.insr(c);n++;mov();}
	inline void dell(){Q1.dell();n--;mov();}
	inline void delr(){Q2.delr();n--;mov();}
	inline void delm(){if(n&1)Q1.delr();else Q2.dell();n--;mov();}
	inline int qry(int m,int*b)
	{
		if(n<m)return 0;int ans=Q1.qry(m,b)+Q2.qry(m,b);
		int tt=0,p=Q1.sz(),sz1=min(Q1.sz(),m-1),sz2=min(Q2.sz(),m-1);
		rep(i,1,sz1)a[++tt]=Q1.gt(p-i+1);reverse(a+1,a+tt+1);
		rep(i,1,sz2)a[++tt]=Q2.gt(i);return ans+kmp(tt,m,a,b); 
	}
}T;
int main()
{
	scanf("%s",s+1);n=strlen(s+1);
	rep(i,1,n)a[i]=s[i]-'a'+1;
	T.build(a,1,n);q=rd();
	rep(i,1,q)
	{
		char o[20],c[20];scanf("%s",o);
		if(o[0]=='I')
		{
			scanf("%s",c);
			if(o[7]=='L')T.insl(c[0]-'a'+1);
			if(o[7]=='R')T.insr(c[0]-'a'+1);
			if(o[7]=='M')T.insm(c[0]-'a'+1);
			continue;
		}
		if(o[0]=='D')
		{
			if(o[7]=='L')T.dell();
			if(o[7]=='R')T.delr();
			if(o[7]=='M')T.delm();
			continue;
		}
		scanf("%s",s+1);n=strlen(s+1);
		rep(i,1,n)a[i]=s[i]-'a'+1;a[n+1]=27;
		printf("%d\n",T.qry(n,a)); 
	}
	return 0;
}
/*
bbabaaaaab
12
INSERT_MIDDLE b
INSERT_LEFT b
INSERT_MIDDLE b
INSERT_MIDDLE b
INSERT_RIGHT a
INSERT_LEFT a
INSERT_MIDDLE b
INSERT_LEFT a
INSERT_MIDDLE a
QUERY bbaaa
DELETE_MIDDLE
DELETE_MIDDLE

1
*/

