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
int v[400005];
int n,r;
int a[200005];
int b[200005];
int t[400005];
int val;

int solve(int pos)
{
	memcpy(t,v,sizeof(int)*2*n);
	rotate(t,t+1,t+pos*2+1);
	for(int i=0;i<2*n;i+=2)
	{
		a[i/2]=max(t[i],t[i+1]);
		b[i/2]=min(t[i],t[i+1]);
	}
	for(int _=0;_<n;_++)
	{
		int tmp=b[0];
		b[0]=min(a[0],a[1]);
		a[0]=max(a[0],a[1]);
		if(n>500)
		{
			int i;
			int *x=&a[1],*y=&a[2],*z=&b[1];
			for(i=2;i<n-4;i+=4)
			{
				*x=max(*z,*y);
				*z^=(*x)^(*y);
				x++;y++;z++;
				*x=max(*z,*y);
				*z^=(*x)^(*y);
				x++;y++;z++;
				*x=max(*z,*y);
				*z^=(*x)^(*y);
				x++;y++;z++;
				*x=max(*z,*y);
				*z^=(*x)^(*y);
				x++;y++;z++;
			}
			for(;i<n;i++)
			{
				a[i-1]=max(b[i-1],a[i]);
				b[i-1]^=a[i-1]^a[i];
			}
		}
		else
		{
			for(int i=2;i<n;i++)
			{
				a[i-1]=max(b[i-1],a[i]);
				b[i-1]^=a[i-1]^a[i];
			}
		}
		a[n-1]=max(b[n-1],tmp);
		b[n-1]=min(b[n-1],tmp);
	}
	swap(a[0],b[0]);
	rotate(a,a+r-n,a+n);
	swap(a[0],b[0]);
	for(int i=0;i<n;i++)
	{
		if(a[i]==val || b[i]==val) return i;
	}
	assert(0);
	return -1;
}

int main()
{
	freopen("archery.in","r",stdin);
	freopen("archery.out","w",stdout);
	double st=clock();
	cin>>n>>r;
	r=r%n+n;
	for(int i=0;i<n*2;i++)
	{
		scanf("%d",v+i);
		v[i]=2*n-v[i];
	}
	val=v[0];
	pii res=mp(inf,-1);
	for(int i=0;i<n;i++)
	{
		if((clock()-st)/CLOCKS_PER_SEC>=1.9) break;
		chmin(res,mp(solve(i),-i));
	}
	cout<<-res.second+1<<endl;
	return 0;
}