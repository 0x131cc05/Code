#include <bits/stdc++.h>
#define PB push_back
#define MP make_pair
#define PII pair<int,int>
#define FIR first
#define SEC second
#define ll long long
using namespace std;

inline char nc() {
    return getchar();
	static char buf[1000000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}

template <class T>
inline void rd(T &x) {
	x=0; char c=nc(); int f=1;
	while(!isdigit(c)) { if(c=='-') f=-1; c=nc(); }
	while(isdigit(c)) x=x*10-'0'+c,c=nc(); x*=f;
}
const int N=1e6+10;
int n,m;
struct node {
	int a,b,id,v;
	void calc_v() { v= a<b ? 2*(n+m+1)-a : b; }
	friend bool operator <(node A,node B) {
	    int t1 = max(A.a, B.a - A.b + A.a), t2 = max(B.a, A.a - B.b + B.a);
		return t1 > t2;
	}
}val[N<<1];
//priority_queue<node> Q;
vector<int> buc[N<<2];
node mer(node A,node B) {
	node t=(node){max(A.a,A.a-A.b+B.a),A.b+B.b-A.a-B.a+max(A.a,A.a-A.b+B.a),A.id,0}; t.calc_v();
	return t;
}

int fa[N<<1];
int tmp[1000500],t;
int find(int x) { return fa[x]==x ? x : fa[x]=find(fa[x]); }

int anc[N<<1];
char A[N],B[N];
int main() {
	int T; rd(T);
	while(T--) {
		rd(n),rd(m);
//		scanf("%s%s",A+1,B+1);
		char c=nc(); while(c!='('&&c!=')') c=nc();
		for(int i=1;i<=n;++i) A[i]=c,c=nc();
		
		while(c!='('&&c!=')') c=nc();
		for(int i=1;i<=m;++i) B[i]=c,c=nc();

		
		for(int i=1;i<=n;++i) {
			anc[i]=i==1 ? n+m+1 : i-1;
			val[i].a=A[i]==')';
			val[i].b=A[i]=='(';
			val[i].id=i;
			val[i].calc_v();
			buc[val[i].v].PB(i);
//			Q.push(val[i]);
		}
		for(int i=1;i<=m;++i) {
			anc[i+n]=i==1 ? n+m+1 : i-1+n;
			val[i+n].a=B[i]==')';
			val[i+n].b=B[i]=='(';
			val[i+n].id=i+n;
			val[i+n].calc_v();
			buc[val[i+n].v].PB(i+n);
//			Q.push(val[i+n]);
		}
		val[n+m+1]=(node){0,0,n+m+1,0};
		for(int i=1;i<=n+m+1;++i) fa[i]=i;
		
		for(int i=2*(n+m+1);i>=0;--i) if(buc[i].size()) {
			t = 0;
			for(auto u : buc[i]) {
				if(fa[u]!=u) continue;
				int f=find(anc[u]);
				val[f]=mer(val[f],val[u]);
				fa[u]=f;
//				cout<<u<<' '<<val[u].v<<' '<<f<<':'<<val[f].a<<' '<<val[f].b<<' '<<val[f].v<<endl;
				assert(val[f].v <= i || f == n + m + 1);
				if(f!=n+m+1)
				{
					if(val[f].v < i)
						buc[val[f].v].PB(f);
					else
						tmp[++ t] = f;
				}
			}
			for(int j = 1;j <= t; ++ j)
			{
				int u = tmp[j];
				if(fa[u]!=u) continue;
				int f=find(anc[u]);
				val[f]=mer(val[f],val[u]);
				fa[u]=f;
//				cout<<u<<' '<<val[u].v<<' '<<f<<':'<<val[f].a<<' '<<val[f].b<<' '<<val[f].v<<endl;
				assert(val[f].v <= i || f == n + m + 1);
				if(f!=n+m+1)
				{
					if(val[f].v < i)
						buc[val[f].v].PB(f);
					else
						tmp[++ t] = f;
				}
			}
			vector<int>().swap(buc[i]);
		}
		
//		while(!Q.empty()) {
//			int u=Q.top().id; Q.pop();
//			if(fa[u]!=u) continue;
//			int f=find(anc[u]);
//			val[f]=mer(val[f],val[u]);
//			fa[u]=f;
////			cout<<u<<' '<<val[f].a<<' '<<val[f].b<<endl;
//			if(f!=n+m+1) Q.push(val[f]);
//		}
		int res=val[n+m+1].a;
		int t1=0,t2=0;
		for(int i=1;i<=n;++i)
			A[i]=='(' ? ++t1 : ++t2;
		for(int i=1;i<=m;++i)
			B[i]=='(' ? ++t1 : ++t2;
//		cout<<t1<<' '<<t2<<' '<<res<<endl;
		printf("%d\n",res+(t1-(t2-res)));
	}
	return 0;
}
