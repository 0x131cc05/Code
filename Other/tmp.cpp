#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define snuke(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)

int B;
vector <int> sep[10];
double dp[10][100010];
double sum[200010];

int small[100];

class OptimalBetting{
  public:
  
  void func(int id){
    int p,i,j;
    
    sum[0] = 0.0;
    REP(i,2*B+5) sum[i+1] = sum[i] + ((i < B) ? dp[id][i] : 1.0);
    
    int T = sep[id].size() - 1;
    REP(i,2*T+1) small[i] = B;
    REP(i,T+1) REP(j,T+1) small[i+j] = min(small[i+j], (sep[id][i] + sep[id][j] + 1) / 2);
    REP(i,2*T+1) sep[id+1].push_back(small[i]);

    
    
    REP(p,2*T){
      int L = sep[id+1][p];
      int R = sep[id+1][p+1];
      
      for(i=L;i<R;i++){
        int lose,win;
        
        REP(lose,T+1){
          win = p - lose;
          if(win > T) continue;
          
          int low = max(0, sep[id][win] - i);
          int high = min(i, i - sep[id][lose]);
          
          if(low <= high){
            dp[id+1][i] += sum[i-low+1] - sum[i-high];
            dp[id+1][i] += sum[i+high+1] - sum[i+low];
          }
        }
      }
    }
    
    REP(i,B) dp[id+1][i] = dp[id+1][i] / (i + 1.0) / 2.0;
  }

  double findProbability(int a, int b, int k){
    int i;
    
    B = b;
    
    sep[0].push_back(0);
    sep[0].push_back(B);
    
    REP(i,B) dp[0][i] = 1.0;
    REP(i,k) func(i);
    for (int i = 1; i <= b; i++) cout << dp[1][i] << ' ';
    cout << endl;
    return dp[k][a];
  }

};

int main() {
    OptimalBetting solver;
    cout << solver.findProbability(20, 50, 5) << endl;
}