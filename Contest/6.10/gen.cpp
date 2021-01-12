#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#define PB push_back
#define MP make_pair
#define PII pair<int,int>
#define FIR first
#define SEC second
#define ll long long
using namespace std;
template <class T>
inline void rd(T &x) {
	x=0; char c=getchar(); int f=1;
	while(!isdigit(c)) { if(c=='-') f=-1; c=getchar(); }
	while(isdigit(c)) x=x*10-'0'+c,c=getchar(); x*=f;
}
#include <cstdlib>
#include <ctime>

int main() {
	srand((unsigned long long)new char + time(0));
	int T=3; cout<<T<<endl;
	while(T--) {
		int n=rand()%10+1,m=rand()%10+1;
		cout<<n<<' '<<m<<endl;
		for(int i=1;i<=n;++i) cout<<(rand()&1 ? '(' : ')'); cout<<endl;
		for(int i=1;i<=m;++i) cout<<(rand()&1 ? '(' : ')'); cout<<endl;
	}
	return 0;
}
	
