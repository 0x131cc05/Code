/*
T2 35 pts 
*/
#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(v) (int)(v).size()
#define all(v) (v).begin(),(v).end()

const int maxn=50005;
int n,q;
int a[maxn];

#define debug(...) cout<<#__VA_ARGS__<<" : "<<__VA_ARGS__<<endl

namespace subtask1 {
	vector<int> s1;
	vector<int> s2;
	void getS(int l,int r) {
		for(int i=l;i<=r;) {
			if(a[i]<0) {
				i++;
			} else {
				int sum=0;
				while(i<=r&&a[i]>=0) {
					sum+=a[i];
					i++;
				}
				s1.pb(sum);
			}
		}
		for(int i=l;i<=r;) {
			if(a[i]>=0) {
				i++;
			} else {
				int sum=0;
				while(i<=r&&a[i]<0) {
					sum+=a[i];
					i++;
				}
				s2.pb(-sum);
			}
		}
	}
	void getit(int l,int r,int k) {
		int tot=0,len=0;
		for(int i=l;i<=r;) {
			if(a[i]<0) {
				i++; continue;
			} else {
				int _l=i,_r=i;
				while(_r<=r&&a[_r]>=0) {
					_r++;
				}
				i=_r;
				_r--;
				tot++;
				len+=_r-_l+1;
			}
		}
		int ans=0;
		if(tot<=k) {
			if(k>len) {
				vector<int> vec(a+l,a+r+1);
				sort(all(vec),greater<int>());
				for(int i=0;i<k;i++) ans+=vec[i];
			} else {
				for(int i=l;i<=r;i++)
					if(a[i]>=0) ans+=a[i];
			}
		} else {
			int maxx=0;
			//Case1 : choose some single elements
			vector<int> vec(a+l,a+r+1);
			sort(all(vec),greater<int>());
			for(int i=0;i<k;i++) maxx+=vec[i];
			///////////////////////////////
			getS(l,r); sort(all(s1)); sort(all(s2));
			//Case2 : delete some segements
			//in total: delete (tot-k) segements
			{
				int sum=0;
				for(int i=tot-k;i<sz(s1);i++)
					sum+=s1[i];
				maxx=max(maxx,sum);
			}
			//Case3 : merge some segements
			//in total: merge (tot-k) segements
			{
				int sum=0;
				for(int i=0;i<sz(s1);i++) sum+=s1[i];
				for(int i=0;i<tot-k;i++) sum-=s2[i];
				maxx=max(maxx,sum);
			}
			ans=maxx;
		}
		cout<<ans<<endl;
	}
	void solve() {
		while(q--) {
			s1.clear(); s2.clear();
			int l,r,k;
			scanf("%d%d%d",&l,&r,&k);
			getit(l,r,k);
		}
	}
}

namespace subtask2 {
	int sum[maxn];
	void solve() {
		memset(sum,0,sizeof(sum));
		for(int i=1;i<=n;i++)
			sum[i]=sum[i-1]+a[i];
		while(q--) {
			int l,r,k;
			scanf("%d%d%d",&l,&r,&k);
			printf("%d\n",sum[r]-sum[l-1]);
		}
		return;
	}
}

int main() {
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	scanf("%d%d",&n,&q);
	bool is_subtask2=true;
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		if(a[i]<0) is_subtask2=false; 
	}
	if(is_subtask2) {
		subtask2::solve();
	} else {
		subtask1::solve();
	}
	return 0;
}
