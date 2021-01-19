#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=(a),i##end=(b);i<=i##end;++i)
#define per(i,a,b) for(int i=(a),i##end=(b);i>=i##end;--i)
//mt19937 Rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
template<typename T>void chkmax(T&x,T y){if(x<y)x=y;}
template<typename T>void chkmin(T&x,T y){if(x>y)x=y;}
inline int read(){
  #define nc getchar()
  int x=0;char c=nc;bool f=0;
  while(c<48)f|=c=='-',c=nc;
  while(c>47)x=x*10+(c^48),c=nc;
  return f?-x:x;
  #undef nc
}

typedef double db;
typedef long long ll;
typedef vector<int>vi;
typedef pair<int,int>pii;
const int maxn=1e5+10;
int F[maxn],su[maxn];

int P;

inline void Add(int&x,int y){x+=y;if(x>=P)x-=P;}

int mtt=3;
struct matrix{
  int arr[3][3];
  void clear(){memset(arr,0,sizeof arr);}
  inline int*operator[](const int&pos){return arr[pos];}
  inline void print(){rep(i,1,mtt)rep(j,1,mtt)printf("%d%c",arr[i][j],"\n "[j<mtt]);}
}E,M,I;
matrix operator*(matrix A,matrix B){
  matrix res;res.clear();
  rep(k,0,2)rep(i,0,2)rep(j,0,2)Add(res[i][j],1ll*A[i][k]*B[k][j]%P);
  return res;
}
matrix qp(matrix A,int k){
  matrix res=E;
  for(;k;k>>=1,A=A*A)if(k&1)res=res*A;
  return res;
}
void minit(){
  E.clear();rep(i,0,2)E[i][i]=1;
}

void solve(){
  int A,B,X,Y,Z;
  cin>>A>>B>>X>>Y>>Z>>P;
  int C,Q;
  cin>>C>>Q;
  F[1]=A,F[2]=B;
  su[1]=A==C,su[2]=su[1]+(B==C);
  rep(i,3,100000){
    F[i]=(X*F[i-1]+Y*F[i-2]+Z)%P;
    su[i]=su[i-1]+(F[i]==C);
  }
  minit();
  M.clear(),I.clear();
  I[0][0]=B,I[0][1]=A,I[0][2]=Z;
  M[0][0]=X,M[1][0]=Y,M[2][0]=M[2][2]=M[0][1]=1;
  while(Q--){
    ll l=read(),r=read();
//    ll res=0;
//    while(l<=r){
//      int val=l==1?A:l==2?B:(I*qp(M,l-2)).arr[0][0];
//      res+=val==C;
//      l++;
//    }
//    cout<<res<<endl;
    printf("%d\n",su[r]-su[l-1]);
  }
}

signed main(){
  int T=read();
  while(T--)solve();
  return 0;
}

