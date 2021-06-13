#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100,B=10000,MAXL=25;
int cur,v[N][N][2];
struct Num{
  int a[MAXL],len,fu;
  Num(){len=1,fu=a[1]=0;}
  void clr(){len=1,fu=a[1]=0;}
  Num operator+(const Num&b)const{
    Num c;
    c.len=max(len,b.len)+2;
    int i;
    for(i=1;i<=c.len;i++)c.a[i]=0;
    if(fu==b.fu){
      for(i=1;i<=len;i++)c.a[i]=a[i];
      for(i=1;i<=b.len;i++)c.a[i]+=b.a[i];
      for(i=1;i<=c.len;i++)if(c.a[i]>=B)c.a[i+1]++,c.a[i]-=B;
      while(c.len>1&&!c.a[c.len])c.len--;
      c.fu=fu;
    }else{
      bool flag=0;
      if(len==b.len){
        for(i=len;i;i--)if(a[i]!=b.a[i]){
          if(a[i]>b.a[i])flag=1;
          break;
        }
      }else{
        if(len>b.len)flag=1;
      }
      if(flag){
        for(i=1;i<=len;i++)c.a[i]=a[i];
        for(i=1;i<=b.len;i++)c.a[i]-=b.a[i];
        for(i=1;i<=c.len;i++)if(c.a[i]<0)c.a[i+1]--,c.a[i]+=B;
        while(c.len>1&&!c.a[c.len])c.len--;
        c.fu=fu;
      }else{
        for(i=1;i<=b.len;i++)c.a[i]=b.a[i];
        for(i=1;i<=len;i++)c.a[i]-=a[i];
        for(i=1;i<=c.len;i++)if(c.a[i]<0)c.a[i+1]--,c.a[i]+=B;
        while(c.len>1&&!c.a[c.len])c.len--;
        c.fu=b.fu;
      }
    }
    return c;
  }
  Num operator-(Num b)const{
    b.fu^=1;
    return *this+b;
  }
  Num operator*(const Num&b)const{
    Num c;
    c.len=len+b.len+2;
    c.fu=fu^b.fu;
    int i,j;
    for(i=1;i<=c.len;i++)c.a[i]=0;
    for(i=1;i<=len;i++)for(j=1;j<=b.len;j++){
      c.a[i+j-1]+=a[i]*b.a[j];
      if(c.a[i+j-1]>=B){
        c.a[i+j]+=c.a[i+j-1]/B;c.a[i+j-1]%=B;
        if(c.a[i+j]>=B)c.a[i+j+1]+=c.a[i+j]/B,c.a[i+j]%=B;
      }
    }
    while(c.len>1&&!c.a[c.len])c.len--;
    return c;
  }
  bool iszero()const{
    return len==1&&!a[1];
  }
  void write(){
    if(len==1&&!a[1])fu=0;
    if(fu)putchar('-');
    printf("%d",a[len]);
    for(int i=len-1;i;i--)printf("%04d",a[i]);
  }
  void set(int x){
    if(x<0)fu=1,x=-x;else fu=0;
    if(x>=B){
      len=2;
      a[1]=x%B;
      a[2]=x/B;
    }else{
      len=1;
      a[1]=x;
    }
  }
  int sgn()const{
    if(iszero())return 0;
    return fu==1?-1:1;
  }
  int cmp(const Num&b)const{
    int x=sgn(),y=b.sgn();
    if(x!=y)return x<y?-1:1;
    if(!x)return 0;
    if(x>0){
      if(len!=b.len)return len<b.len?-1:1;
      for(int i=len;i;i--)if(a[i]!=b.a[i])return a[i]<b.a[i]?-1:1;
      return 0;
    }
    if(len!=b.len)return len>b.len?-1:1;
    for(int i=len;i;i--)if(a[i]!=b.a[i])return a[i]>b.a[i]?-1:1;
    return 0;
  }
  bool operator<(const Num&b)const{return cmp(b)<0;}
  bool operator==(const Num&b)const{return cmp(b)==0;}
  bool operator>(const Num&b)const{return cmp(b)>0;}
}ans,val[11];
struct P{
  Num f,s;
  P(){f.clr();s.clr();}
  void clr(){f.clr();s.clr();}
  P(Num _f,Num _s){f=_f,s=_s;}
  P operator+(const P&b)const{return P(min(f,s+b.f),s+b.s);}
  void operator+=(const P&b){*this=*this+b;}
}base,f[N][N][2];
P dfs(int x,int y,int z){
  if(x==0){
    P t;
    t.f.set(-y);
    t.s.set(-y);
    return base+t;
  }
  if(v[x][y][z]==cur+1)return f[x][y][z];
  v[x][y][z]=cur+1;
  P t;
  t.clr();
  for(int i=z;i<10;i++)t+=dfs(x-1,y+(i==cur),0);
  return f[x][y][z]=t;
}
Num solve(int _cur,int _base){
  cur=_cur;
  base.f.set(0);
  base.s.set(_base);
  int i,j,len;
  P pre;
  pre.clr();
  for(len=1;;len++){
    P now=dfs(len,0,1);
    if((pre+now).f.sgn()<0)break;
    pre+=now;
  }
  Num ans=val[0];
  int sum=0;
  for(i=len;i;i--)for(j=i==len?1:0;;j++){
    int nowsum=sum+(j==cur);
    P now=dfs(i-1,nowsum,0);
    if((pre+now).f.sgn()<0){
      sum=nowsum;
      ans=ans*val[10]+val[j];
      break;
    }
    pre+=now;
  }
  return ans;
}
int main(){
  for(int i=0;i<11;i++)val[i].set(i);
  for(int i=0;i<10;i++){
    int x;
    scanf("%d",&x);
    if(i==0)ans=solve(i,x);
    else ans=min(ans,solve(i,x));
  }
  ans=ans-val[1];
  ans.write();
  return 0;
}
