#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)

typedef long long ll;
#define MOD 1000000009ll

ll dp[1000010];

class BunnySequence{
  public:

  int getNumber(int m, int n){
    int i;
    
    dp[0] = dp[1] = 1;
    for(i=2;i<m;i++) dp[i] = dp[i-1] * 2 % MOD;
    dp[m] = (dp[m-1] * 2 % MOD + MOD - 1) % MOD;
    dp[m+1] = dp[m] * 2 % MOD;
    for(i=m+2;i<1000010;i++) dp[i] = (dp[i-1] * 2 % MOD + MOD - dp[i-1-m]) % MOD;
    
    return (int)dp[n];
  }

};

int main() {
    BunnySequence solver;
    cout << solver.getNumber(2, 4);
}