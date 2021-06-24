#include <numeric>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <string.h>
#include <stack>
#include <assert.h>
#include <bitset>
#include <time.h>
#include <sstream>
#define Endl endl
#define mp make_pair
#define mt make_tuple
#define ll long long 
#define ull unsigned long long
#define pii pair<int,int>
#define over(A) {cout<<A<<endl;exit(0);}
#define all(A) A.begin(),A.end()
#define quickcin ios_base::sync_with_stdio(false);
const int mod=1000000007;
const int gmod=3;
const int inf=1039074182;
const double eps=1e-9;
const double pi=3.141592653589793238462643383279;
const ll llinf=2LL*inf*inf;
template <typename T1,typename T2> inline void chmin(T1 &x,T2 b) {if(b<x) x=b;}
template <typename T1,typename T2> inline void chmax(T1 &x,T2 b) {if(b>x) x=b;}
inline void chadd(int &x,int b) {x+=b-mod;x+=(x>>31 & mod);}
template <typename T1,typename T2> inline void chadd(T1 &x,T2 b) {x+=b;if(x>=mod) x-=mod;}
template <typename T1,typename T2> inline void chmul(T1 &x,T2 b) {x=1LL*x*b%mod;}
template <typename T1,typename T2> inline void chmod(T1 &x,T2 b) {x%=b,x+=b;if(x>=b) x-=b;}
template <typename T> inline T mabs(T x) {return (x<0?-x:x);}
using namespace std;
template <typename T>
ostream & operator<<(ostream &cout, const vector<T> &vec)
{
	cout << "{";
	for (int i = 0; i < (int)vec.size(); i++)
	{
		cout << vec[i];
		if (i != (int)vec.size() - 1)
			cout << ',';
	}
	cout << "}";
	return cout;
}

template <typename T1, typename T2>
ostream &operator<<(ostream &cout, pair<T1, T2> p)
{
	cout << "(" << p.first << ',' << p.second << ")";
	return cout;
}

template <typename T, typename T2>
ostream &operator<<(ostream &cout, set<T, T2> s)
{
	vector<T> t;
	for (auto x : s)
		t.push_back(x);
	cout << t;
	return cout;
}

template <typename T, typename T2>
ostream &operator<<(ostream &cout, multiset<T, T2> s)
{
	vector<T> t;
	for (auto x : s)
		t.push_back(x);
	cout << t;
	return cout;
}

template <typename T>
ostream &operator<<(ostream &cout, queue<T> q)
{
	vector<T> t;
	while (q.size())
	{
		t.push_back(q.front());
		q.pop();
	}
	cout << t;
	return cout;
}

template <typename T1, typename T2, typename T3>
ostream &operator<<(ostream &cout, map<T1, T2, T3> m)
{
	for (auto &x : m)
	{
		cout << "Key: " << x.first << ' ' << "Value: " << x.second << endl;
	}
	return cout;
}
void debug_out(
vector<string> __attribute__ ((unused)) args,
__attribute__ ((unused)) int idx, 
__attribute__ ((unused)) int LINE_NUM) { cerr << endl; } 
template <typename Head, typename... Tail>
void debug_out(vector<string> args, int idx, int LINE_NUM, Head H, Tail... T) {
	if(idx > 0) cerr << ", "; else cerr << "Line(" << LINE_NUM << ") ";
	stringstream ss; ss << H;
	cerr << args[idx] << " = " << ss.str();
	debug_out(args, idx + 1, LINE_NUM, T...);
}
#define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
using namespace std;
int n,m;
vector<int> trees[1005];
vector<pii> edges[1005];
int sons[1005][15];
int len[1005];
int dp[1005][1005];
int bel[1005][1005];
int f[1005][(1<<10)];
vector<tuple<int,int,int> > e[1005][15][15];
vector<tuple<int,int> > e2[1005][15];
int par[1005];
int depth[1005];
int l[1005],r[1005];

void go(int x,int p,int d=0)
{
	static int T=0;
	l[x]=T++;
	par[x]=p;
	depth[x]=d;
	for(auto u:trees[x])
	{
		if(u==p) continue;
		sons[x][len[x]++]=u;
		go(u,x,d+1);
	}
	r[x]=T;
}

void dfs(int x,int p)
{
	int n=len[x];
	auto &sons=::sons[x];
	for(auto u:trees[x])
	{
		if(u==p) continue;
		dfs(u,x);
	}
	memset(f[x],-0x3f,sizeof(f[x]));
	auto &f=::f[x];
	f[0]=0;
	for(int mask=0;mask<(1<<n);mask++)
	{
		for(int i=0;i<n;i++)
		{
			if((1<<i) & mask) continue;
			for(int j=i+1;j<n;j++)
			{
				if((1<<j) & mask) continue;
				for(auto &o:e[x][i][j])
				{
					int u,v,w;
					tie(u,v,w)=o;
					chmax(f[mask|(1<<i)|(1<<j)],f[mask]+dp[sons[i]][u]+dp[sons[j]][v]+w);
				}
			}
		}
		for(int i=0;i<n;i++)
		{
			if((1<<i) & mask) continue;
			for(auto &o:e2[x][i])
			{
				int u,w;
				tie(u,w)=o;
				chmax(f[mask|(1<<i)],f[mask]+dp[sons[i]][u]+w);
			}
			chmax(f[mask|(1<<i)],f[mask]+dp[sons[i]][sons[i]]);
		}
	}
	for(int i=0;i<::n;i++)
	{
		if(i==x)
		{
			dp[x][i]=f[(1<<n)-1];
		}
		else if(bel[x][i]==-1) continue;
		else
		{
			int mask=((1<<n)-1)^(1<<bel[x][i]);
			dp[x][i]=f[mask]+dp[sons[bel[x][i]]][i];
		}
	}
}

tuple<int,int,int> dedges[5005];
int main()
{
	// freopen("input.txt","r",stdin);
	freopen("training.in","r",stdin);
	freopen("training.out","w",stdout);
	cin>>n>>m;
	int tot=0;
	for(int i=0;i<m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		x--;
		y--;
		tot+=z;
		if(z==0)
		{
			trees[x].emplace_back(y);
			trees[y].emplace_back(x);
		}
		else
		{
			edges[x].emplace_back(y,z);
			edges[y].emplace_back(x,z);
		}
		dedges[i]=mt(x,y,z);
	}
	go(0,-1);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if((l[j]>=l[i] && r[j]<=r[i]) && (i!=j))
			{
				bel[i][j]=-1;
				for(int k=0;k<len[i];k++)
				{
					if(l[j]>=l[sons[i][k]] && r[j]<=r[sons[i][k]])
					{
						bel[i][j]=k;
						break;
					}
				}
				assert(bel[i][j]!=-1);
			}
			else
			{
				bel[i][j]=-1;
			}
		}
	}
	for(int i=0;i<m;i++)
	{
		int x,y,z;
		tie(x,y,z)=dedges[i];
		int tx=x,ty=y;
		if(depth[tx]<depth[ty]) swap(tx,ty);
		while(depth[tx]>depth[ty]) tx=par[tx];
		while(tx!=ty) tx=par[tx],ty=par[ty];
		// cout<<depth[x]<<' '<<depth[y]<<endl;
		if(((depth[x]^depth[y])&1)==1) continue;
		if(tx==x)
		{
			e2[x][bel[x][y]].emplace_back(y,z);
		}
		else if(tx==y)
		{
			e2[y][bel[y][x]].emplace_back(x,z);
		}
		else
		{
			if(bel[tx][x]>bel[tx][y]) swap(x,y);
			assert(bel[tx][x]!=bel[tx][y]);
			e[tx][bel[tx][x]][bel[tx][y]].emplace_back(x,y,z);
		}
	}
	dfs(0,-1);
	cout<<tot-dp[0][0]<<endl;
	return 0;
}