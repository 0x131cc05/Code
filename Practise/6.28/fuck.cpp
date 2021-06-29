#include<bits/stdc++.h>
using namespace std;

const int maxn=8005;
const int INF=0x3f3f3f3f;
int n,m1,m2,k1,k2,p1,p2,ans;
char s[maxn];
int a[maxn],b[maxn],c[maxn],c1[maxn],c2[maxn],d[maxn],f[maxn][maxn];

int main(){
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=1;i<=n;i++){
		if(s[i]=='o'||s[i]=='x')a[++m1]=i;
		else if(s[i]=='(')c1[++k1]=i;
		else c2[++k2]=i;
	}
	while(p1<k1||p2<k2){
		if(!c[m2]||(p1<k1&&c1[p1+1]<c2[p2+1]))b[++m2]=c1[++p1],c[m2]=c[m2-1]+1;
		else b[++m2]=c2[++p2],c[m2]=c[m2-1]-1;
	}
	for(int i=1;i<=m2;i++)for(int j=i+1;j<=m2;j++)ans+=(b[i]>b[j]);
	for(int i=0;i<=m1;i++)for(int j=0;j<=m2;j++)f[i][j]=INF;
	f[0][0]=0;
	for(int i=0;i<=m1;i++){
		int e=0;
		for(int j=0;j<=m2;j++){
			if(i+1<=m1){
				if(j)e+=(b[j]>a[i+1]);
				if(c[j]>0||s[a[i+1]]=='o')f[i+1][j]=min(f[i+1][j],f[i][j]+e);
			}
			if(j+1<=m2){
				if(i)d[j]+=(a[i]>b[j+1]);
				f[i][j+1]=min(f[i][j+1],f[i][j]+d[j]);
			}
		}
	}
	printf("%d\n",ans+f[m1][m2]);
	return 0;
}