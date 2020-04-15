#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<vector>
#include<map>
using namespace std;
vector<int>now,x[4000];
map<vector<int>,int>M;
int R,m,len,go[9][4000][9][4],bo[9][4000],tot[9];
long long C;
double P,dp[51][9][4000];
double quick(double k1,long long k2){
	double k3=1;
	while (k2){
		if (k2&1) k3=k3*k1; k2>>=1; k1=k1*k1;
	}
	return k3;
}
void solve(){
	scanf("%d%lld%lf",&R,&C,&P);
	memset(dp,0x00,sizeof dp);
	m=min(C,50ll); int len=tot[R];
	dp[1][1][1]=1;
	double W0=P*P,W1=P*(1-P),W2=P*(1-P),W3=(1-P)*(1-P);
	for (int i=1;i<=m;i++)
		for (int j=1;j<=R;j++){
			if (i==1&&j==1) continue;
			double *pre,*now=dp[i][j];
			if (j==1) pre=dp[i-1][R]; else pre=dp[i][j-1];
			double w0=W0,w1=W1,w2=W2,w3=W3;
			if (i==1){
				w0=0; w1=0; w2=P; w3=(1-P); 
			} else if (j==1){
				w0=P; w1=0; w2=1-P; w3=0;
			}
			for (int k=1;k<=len;k++)
			{
				int k1=go[R][k][j][0];
				if (k1!=-1) now[k1]+=pre[k]*w0;
				k1=go[R][k][j][1];
				if (k1!=-1) now[k1]+=pre[k]*w1;
				k1=go[R][k][j][2];
				if (k1!=-1) now[k1]+=pre[k]*w2;
				k1=go[R][k][j][3];
				if (k1!=-1) now[k1]+=pre[k]*w3;
			}
//			cout<<"fa "<<i<<" "<<j<<endl;
//			for (int k=1;k<=len;k++) cout<<now[k]<<" "; cout<<endl;
		}
	double ans=0;
	for (int i=1;i<=len;i++) if (bo[R][i]) ans+=dp[m][R][i];
	if (m==C) {printf("%.11lf\n",ans); return;}
	double ans2=0;
	for (int i=1;i<=len;i++) if (bo[R][i]) ans2+=dp[m-1][R][i];
	if (ans2<1e-8) printf("0.000000\n");
	else printf("%.11lf\n",ans2*quick(ans/ans2,C-m+1));
}
int check(vector<int>&A){
	int pd[10],now=0,flag=0; memset(pd,0x00,sizeof pd);
	for (int i=0;i<=R;i++){
		if (pd[A[i]]==0) pd[A[i]]=++now;
		A[i]=pd[A[i]]; if (i&&A[i]==1) flag=1;
	}
	if (flag==0) return -1;
	int k=M[A];
	if (k==0){
		M[A]=len+1; bo[R][len+1]=(A[R]==A[0]); return len+1;
	}
	return k;
}
void dfs(int k){
	for (int i=1;i<=R;i++){
		vector<int>A=x[k];
		A[i]=R+1;
		go[R][k][i][0]=check(A);
		if (go[R][k][i][0]==len+1){
			len++; x[len]=A; dfs(len);
		}
		if (i!=1){
			A=x[k];
			A[i]=A[i-1];
			go[R][k][i][1]=check(A);
			if (go[R][k][i][1]==len+1){
				len++; x[len]=A; dfs(len);
			}
		}
		go[R][k][i][2]=k;
		if (i!=1){
			A=x[k]; int pre=A[i-1];
			for (int j=0;j<=R;j++) if (A[j]==pre) A[j]=A[i];
			go[R][k][i][3]=check(A);
			if (go[R][k][i][3]==len+1){
				len++; x[len]=A; dfs(len);
			}
		}
	}
}
void firget(int r){
	R=r; len=1; now.clear(); M.clear(); bo[r][1]=(r==1);
	for (int i=0;i<=R;i++) now.push_back(max(i,1));
	M[now]=1; x[1]=now; dfs(1); tot[R]=len;
/*	if (r==2){
		for (int i=1;i<=len;i++){
			cout<<"num "<<i<<endl;
			for (int j=0;j<=r;j++) cout<<x[i][j]<<" "; cout<<endl;
			for (int j=1;j<=r;j++){
				cout<<"go "<<j<<endl;
				for (int k=0;k<4;k++) cout<<go[r][i][j][k]<<" "; cout<<endl;
			}
		}
	}*/
}
int main(){
	memset(go,0xff,sizeof go);
	for (int i=1;i<=8;i++) firget(i);
	int t; scanf("%d",&t);
	for (;t;t--) solve();
	return 0;
}