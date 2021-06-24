#include<bits/stdc++.h>
#define LL long long
#define mp make_pair
#define pb push_back
#define pii pair<int,int>
using namespace std;
inline int read(){
    int v=0,f=1;
    char c=getchar();
    while (c<'0' || c>'9'){
        if (c=='-') f=-1;
        c=getchar();
    }
    while (c>='0' && c<='9'){
        v=v*10+c-'0';
        c=getchar();
    }
    return v*f;
}

const int Maxn=50005;
const int delta=10000;
int n,q,A[Maxn];
int tree[Maxn*20],S[Maxn*20],lson[Maxn*20],rson[Maxn*20],kt,rt[Maxn];
int build(int l,int r){
    int np=++kt;
    if (l==r){
        return np;
    }
    int mid=(l+r)>>1;
    lson[np]=build(l,mid);
    rson[np]=build(mid+1,r);
    return np;
}
int modify(int p,int l,int r,int pos){
    int np=++kt;
    if (l==r){
        tree[np]=tree[p]+1;
        S[np]=S[p]+(l-delta);
        return np;
    }
    int mid=(l+r)>>1;
    if (pos<=mid){
        lson[np]=modify(lson[p],l,mid,pos);
        rson[np]=rson[p];
    }
    else{
        lson[np]=lson[p];
        rson[np]=modify(rson[p],mid+1,r,pos);
    }
    tree[np]=tree[lson[np]]+tree[rson[np]];
    S[np]=S[lson[np]]+S[rson[np]];
    return np;
}
int query_kth(int lp,int rp,int l,int r,int k){
    if (!k) return 0;
    if (l==r){
        return k*(l-delta);
    }
    int mid=(l+r)>>1;
    if (tree[lson[rp]]-tree[lson[lp]]>=k){
        return query_kth(lson[lp],lson[rp],l,mid,k);
    }
    else{
        int ans=S[lson[rp]]-S[lson[lp]];
        
        k-=tree[lson[rp]]-tree[lson[lp]];
        
        ans+=query_kth(rson[lp],rson[rp],mid+1,r,k);
        return ans;
    }
}

int Spos[Maxn],SC[Maxn],Tpos[Maxn],Sa[Maxn];

const int B=1000;

struct poly{
    int a[505],deg;
    poly(int _d=0){
        memset(a,0,sizeof(a));
        deg=_d;
    }
    pair<int,int> query(int W){
        int lo=0,hi=deg+1;
        if (a[1]-a[0]<=W) hi=1;
        while (hi-lo>1){
            int mid=(lo+hi)>>1;
            (a[mid]-a[mid-1]>W)? (lo=mid):(hi=mid);
        }
        return mp(a[lo]-lo*W,lo);
    }
};
void Ckmax(poly &x,poly y){
    if (y.deg>x.deg){
        for (int i=x.deg+1;i<=y.deg;i++) x.a[i]=-1e9;
        x.deg=y.deg;
    }
    
    for (int i=0;i<=y.deg;i++){
        if (y.a[i]>x.a[i]){
            x.a[i]=y.a[i];
        }
    }
}
poly Mul(poly x,poly y){
    poly z(x.deg+y.deg);
    for (int i=0;i<=z.deg;i++) z.a[i]=-1e9;
    for (int i=0;i<=x.deg;i++){
        for (int j=0;j<=y.deg;j++){
            z.a[i+j]=max(z.a[i+j],x.a[i]+y.a[j]);
        }
    }
    return z;
}

poly R[50005][2][2],L[50005][2][2],fuck[2][2];
int E[50005],NE[50005];
pair<int,int> __[2][2];
void DO(poly _[2][2],int &F,int &G,int &pF,int &pG,int X){
    
    for (int i=0;i<2;i++) for (int j=0;j<2;j++){
        __[i][j]=_[i][j].query(X);
    }
    
    int nF,nG,npF,npG;
    nF=F+__[0][0].first;
    npF=pF+__[0][0].second;
    if (G+__[1][0].first>nF){
        nF=G+__[1][0].first;
        npF=pG+__[1][0].second;
    }
    else if (G+__[1][0].first==nF){
        npF=min(npF,pG+__[1][0].second);
    }
    
    nG=F+__[0][1].first;
    npG=pF+__[0][1].second;
    if (G+__[1][1].first>nG){
        nG=G+__[1][1].first;
        npG=pG+__[1][1].second;
    }
    else if (G+__[1][1].first==nG){
        npG=min(npG,pG+__[1][1].second);
    }
    F=nF;G=nG;pF=npF;pG=npG;
    if (F<-1e9) F=-1e9;
    if (G<-1e9) G=-1e9;
}
int main(){
    freopen("sequence.in","r",stdin);
    freopen("sequence.out","w",stdout);
    n=read();q=read();
    for (int i=1;i<=n;i++){
        A[i]=read();Sa[i]=A[i];
        if (A[i]>0) Spos[i]=A[i],Tpos[i]=1;
    }
    
    for (int i=1;i<=n;i++){
        if (A[i]>=0 && A[i+1]<0) SC[i]=1;
    }
    for (int i=1;i<=n;i++){
        Spos[i]+=Spos[i-1];
        SC[i]+=SC[i-1];
        Tpos[i]+=Tpos[i-1];
        Sa[i]+=Sa[i-1];
    }
    rt[0]=build(0,20000);
    
    for (int i=1;i<=n;i++){
        rt[i]=modify(rt[i-1],0,20000,A[i]+delta);
    }
    
    for (int i=n;i>=1;i-=B) E[i]=1;
    
    for (int i=n;i>=1;i--){
        if (E[i]) NE[i]=i;
        else NE[i]=NE[i+1];
    }
    
    for (int i=n;i>=1;i--){
        fuck[0][1].deg=1;
        fuck[0][1].a[0]=-1e9;
        fuck[0][1].a[1]=A[i];
        fuck[1][1].a[0]=A[i];
        if (E[i]){
            for (int j=0;j<2;j++){
                for (int k=0;k<2;k++){
                    R[i][j][k]=fuck[j][k];
                }
            }
        }
        else{
            for (int j=0;j<2;j++){
                for (int k=0;k<2;k++){
                    R[i][j][k].a[0]=-1e9;
                    for (int l=0;l<2;l++){
                        Ckmax(R[i][j][k],Mul(fuck[j][l],R[i+1][l][k]));
                    }
                }
            }
        }
    }
    
    for (int i=1;i<=n;i++){
        fuck[0][1].deg=1;
        fuck[0][1].a[0]=-1e9;
        fuck[0][1].a[1]=A[i];
        fuck[1][1].a[0]=A[i];
        if (E[i-1]){
            for (int j=0;j<2;j++){
                for (int k=0;k<2;k++){
                    L[i][j][k]=fuck[j][k];
                }
            }
        }
        else{
            for (int j=0;j<2;j++){
                for (int k=0;k<2;k++){
                    L[i][j][k].a[0]=-1e9;
                    for (int l=0;l<2;l++){
                        Ckmax(L[i][j][k],Mul(L[i-1][j][l],fuck[l][k]));
                    }
                }
            }
        }
    }
    /*
    for (int i=1;i<=n;i++){
        for (int j=0;j<2;j++){
            for (int k=0;k<2;k++){
                cout<<"DEBUG"<<i<<' '<<j<<' '<<k<<" "<<R[i][j][k].deg<<endl;
                for (int l=0;l<=R[i][j][k].deg;l++){
                    cout<<R[i][j][k].a[l]<<' ';
                }
                cout<<endl;
            }
        }
    }*/
    
    
    for (int i=1;i<=q;i++){
        int l,r,k;
        l=read();r=read();k=read();
        
        int C=SC[r]-SC[l-1];
        if (A[r]>=0) C++;
        int Cp=Tpos[r]-Tpos[l-1];
        
        if (k>=Cp){
            int S=Sa[r]-Sa[l-1];
            printf("%d\n",S-query_kth(rt[l-1],rt[r],0,20000,(r-l+1)-k));
            continue;
        }
        if (k>=C){
            printf("%d\n",Spos[r]-Spos[l-1]);
            continue;
        }
        int lo=0,hi=5e8;
        
        vector<int> PS;
        
        poly F,G,FF,GG;
        if (NE[l]>=r){
            F.a[0]=0;G.a[0]=-1e9;
            poly tf,tg;
            for (int i=l;i<=r;i++){
                FF=F;Ckmax(FF,G);
                
                tf.deg=1;tf.a[0]=-1e9;tf.a[1]=A[i];
                tg.deg=0;tg.a[0]=A[i];
                GG=Mul(tf,F);
                Ckmax(GG,Mul(tg,G));
                F=FF;G=GG;
            }
            Ckmax(F,G);
            //cerr<<"FDEG"<<' '<<F.deg<<endl;
            //for (int i=0;i<=F.deg;i++) cout<<F.a[i]<<' ';
            //cout<<endl;
        }
    
        while (hi-lo>1){
            int mid=(lo+hi)>>1;
            int _l=l,_r=r;
            //X=mid
            
            if (NE[l]>=r){
                pair<int,int> Qr=F.query(mid);
                if (Qr.second<=k) hi=mid;
                else lo=mid;
                continue;
            }
            
            int nF=0,nG=-1e9;
            int pF=0,pG=-1e9;
            //cerr<<"FK"<<NE[l]<<' '<<r<<endl;
            while (NE[l]<r){
                
                DO(R[l],nF,nG,pF,pG,mid);
               // cerr<<"SHIT"<<nF<<' '<<nG<<' '<<pF<<' '<<pG<<endl;
                l=NE[l]+1;
            }
            
            DO(L[r],nF,nG,pF,pG,mid);
            l=_l;r=_r;
            if (nG>nF){
                pF=pG;nF=nG;
            }
            else if (nG==nF){
                pF=min(pF,pG);
            }
            //cerr<<mid<<' '<<nF<<' '<<pF<<endl;
            if (pF<=k) hi=mid;
            else lo=mid;
        }
        
        int _l=l,_r=r;
        //X=mid
        
        if (NE[l]>=r){
            pair<int,int> Qr=F.query(hi);
            printf("%d\n",Qr.first+k*hi);
            continue;
        }
        
        int nF=0,nG=-1e9;
        int pF=0,pG=-1e9;
        //cerr<<"FK"<<NE[l]<<' '<<r<<endl;
        while (NE[l]<r){
            
            DO(R[l],nF,nG,pF,pG,hi);
           // cerr<<"SHIT"<<nF<<' '<<nG<<' '<<pF<<' '<<pG<<endl;
            l=NE[l]+1;
        }
        
        DO(L[r],nF,nG,pF,pG,hi);
        l=_l;r=_r;
        if (nG>nF){
            pF=pG;nF=nG;
        }
        else if (nG==nF){
            pF=min(pF,pG);
        }
        //cerr<<"K="<<' '<<hi<<' '<<nF<<endl;
        printf("%d\n",nF+k*hi);
    }
    
    
    return 0;
}
