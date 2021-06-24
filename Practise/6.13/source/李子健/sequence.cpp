#include<iostream>
#include<fstream>
#include<cstring>
#define mem(a,b) memset(a, b, sizeof(a))
#define rep(i,a,b) for(int i = (a); i <= (b); i++)
#define per(i,b,a) for(int i = (b); i >= (a); i--)
#define N 55
#define Inf 0x3f3f3f3f
using namespace std;

int dp[N][N], a[N], sum[N];
int n, q;

int solve(int l, int r, int k){
    if(l == r) return a[l];
    mem(dp, 0x80);
    int ans = -Inf;
    dp[l-1][0] = dp[l][0]= 0, dp[l][1] = a[l];
    rep(i,l+1,r) rep(p,1,k){
        dp[i][p] = max(dp[i][p], dp[i-1][p]);
        rep(j,l-1,i-1) dp[i][p] = max(dp[i][p], dp[j][p-1]);
        if(p) dp[i][p] += a[i];
        if(p == k) ans = max(ans, dp[i][p]);
    }
    return ans;
}

int main(){
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    cin>>n>>q;
    rep(i,1,n) cin>>a[i], sum[i] = sum[i-1]+a[i];
    int l, r, k;
    rep(i,1,q){
        cin>>l>>r>>k;
        if(n >= 100) cout<<sum[r]-sum[l-1]<<endl;
        else cout<<solve(l, r, k)<<endl;
    }
    return 0;
}
/*
6 5
-1 3 -1 2 3 -1
1 4 2
2 5 1
3 4 2
1 3 2
1 1 1

10 10
-3 4 2 -5 1 2 4 -3 2 1
2 6 2
3 9 2
1 5 1
5 9 3
1 10 7
1 4 4 
6 9 2
4 8 1
2 9 5
2 5 2

6 1
1 2 3 4 5 6
1 5 4
*/