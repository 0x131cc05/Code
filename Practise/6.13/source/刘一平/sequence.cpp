#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int MAXN = 5e4 + 5;
const int inf = 0x3f3f3f3f;

const int SIZ = 5e2;
struct Segment_Tree
{
	struct Node
	{
		int sum;
		pair<int,pii> mx;
		pii mxl, mxr;
		Node(void){}
		Node(int pos,int val): sum(val), mx(make_pair(val, make_pair(pos, pos))), mxl(make_pair(val, pos)), mxr(make_pair(val, pos)) {}
		Node(int _sum, pair<int,pii> _mx, pii _mxl, pii _mxr): sum(_sum), mx(_mx), mxl(_mxl), mxr(_mxr) {}
		inline friend Node operator + (const Node &p,const Node &q)
		{
			return Node(
				p.sum + q.sum,
				max(max(p.mx, q.mx), make_pair(p.mxr.first + q.mxl.first, make_pair(p.mxr.second, q.mxl.second))),
				max(p.mxl, make_pair(p.sum + q.mxl.first, q.mxl.second)),
				max(q.mxr, make_pair(q.sum + p.mxr.first, p.mxr.second))
			);
		}
	}p[MAXN<<2];
	int n;
	#define ls(u) ((u)<<1)
	#define rs(u) ((u)<<1|1)
	#define lson(u) ls(u),l,mid
	#define rson(u) rs(u),mid+1,r
	inline void push_up(int u){ p[u] = p[ls(u)] + p[rs(u)];}
	inline void build(int u,int l,int r,int a[])
	{
		if(l == r){ p[u] = Node(l, a[l]); return;}
		int mid = (l+r)>>1;
		build(lson(u),a); build(rson(u),a);
		push_up(u);
	}
	inline Node query(int u,int l,int r,int ql,int qr)
	{
		if(ql<=l && r<=qr) return p[u];
		int mid = (l+r)>>1;
		if(ql<=mid && mid<qr) return query(lson(u),ql,qr) + query(rson(u),ql,qr);
		return ql<=mid? query(lson(u),ql,qr): query(rson(u),ql,qr);
	}
	
	pair<int,pii> f[MAXN][SIZ];
	void build(int _n,int a[])
	{
		n = _n;
		build(1,1,n,a);
		for(int i=1; i<=n; ++i)
		{
			Node cur(i, a[i]);
			for(int j=0; j<SIZ && i+j<=n; ++j)
			{
				f[i][j] = cur.mx;
				if(i+j+1 <= n)
					cur = cur + Node(i+j+1, a[i+j+1]);
			}
		}
	}
	inline pair<int,pii> query(int l,int r)
	{
		if(r-l < SIZ) return f[l][r-l];
		return query(1,1,n,l,r).mx;
	}
};

int n,Q;
int a[MAXN];

namespace Subtask1
{
	const int MAXN = 50 + 5;
	
	int f[MAXN][MAXN], g[MAXN][MAXN];
	
	void solve(void)
	{
		while(Q--)
		{
			int l,r,k;
			scanf("%d%d%d",&l,&r,&k);
			
			memset(f[l-1], 0xc0, sizeof(f[l-1]));
			memset(g[l-1], 0xc0, sizeof(g[l-1]));
			f[l-1][0] = 0;
			for(int i=l; i<=r; ++i)
				for(int j=0; j<=k; ++j)
				{
					g[i][j] = g[i-1][j] + a[i];
					if(j)
						g[i][j] = max(g[i][j], f[i-1][j-1] + a[i]);
					
					f[i][j] = max(f[i-1][j], g[i][j]);
				}
			printf("%d\n",f[r][k]);
		}
		exit(0);
	}
}

namespace Subtask2
{
	inline bool is_this(void)
	{
		for(int i=1; i<=n; ++i)
			if(a[i] < 0) return 0;
		return 1;
	}
	
	int sum[MAXN];
	
	void solve(void)
	{
		while(Q--)
		{
			int l,r,k;
			scanf("%d%d%d",&l,&r,&k);
			printf("%d\n",sum[r] - sum[l-1]);
		}
		exit(0);
	}
}

namespace Subtask3
{
	Segment_Tree tree[2];
	int cnt_pos[MAXN];
	
	int b[2][MAXN];
	
	struct Data
	{
		int l,r,k;
		int mx, ml, mr;
		Data(void){}
		Data(int _l,int _r,int _k): l(_l), r(_r), k(_k)
		{
			pair<int,pii> res = tree[k].query(l,r);
//			printf("[%d, %d] k = %d: ",l,r,k);
			mx = res.first; ml = res.second.first; mr = res.second.second;
//			printf("mx = %d, in [%d, %d]\n",mx,ml,mr);
		}
		inline bool operator < (const Data &oth) const { return mx < oth.mx;}
	};
	
	void solve(void)
	{
		for(int i=1; i<=n; ++i)
			b[0][i] = a[i], b[1][i] = -a[i];
		tree[0].build(n, b[0]);
		tree[1].build(n, b[1]);
		
		for(int i=1; i<=n; ++i)
			cnt_pos[i] = cnt_pos[i-1] + (a[i] >= 0);
		
		while(Q--)
		{
			int ql,qr,qk;
			scanf("%d%d%d",&ql,&qr,&qk);
			if(qk >= cnt_pos[qr] - cnt_pos[ql-1])
			{
				static int t[MAXN];
				for(int i=ql; i<=qr; ++i) t[i] = a[i];
				sort(t+ql,t+qr+1);
				int res = 0;
				for(int i=0; i<qk; ++i) res += t[qr-i];
				printf("%d\n",res);
				continue;
			}
			
//			printf("this!\n");
			priority_queue<Data> t;
			t.push(Data(ql, qr, 0));
			int ans = 0;
			while(qk--)
			{
				Data cur = t.top(); t.pop();
				int l = cur.l, r = cur.r, k = cur.k;
				int mx = cur.mx, ml = cur.ml, mr = cur.mr;
				
				if(mx >= 0) ans += mx;
				
				if(l < ml) t.push(Data(l, ml-1, k));
				if(mr < r) t.push(Data(mr+1, r, k));
				if(mx >= 0 && ml <= mr) t.push(Data(ml, mr, !k));
			}
			printf("%d\n",ans);
		}
		exit(0);
	}
}

int main(void)
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	
	scanf("%d%d",&n,&Q);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
	
	if(n <= 50 && Q <= 50) Subtask1::solve();
	else if(Subtask2::is_this()) Subtask2::solve();
	else Subtask3::solve();
	return 0;
}
