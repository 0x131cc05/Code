#include<bits/stdc++.h>
#define re(x) memset(x,0,sizeof(x))
using namespace std;
typedef long long LL;
const int N=1e6 + 7;
int m,n,ndc;
int book[N],gg[N],rt[N];
char s[N]; LL ans;
struct treenode{int l,r,sumv;}t[N*50];
void modify(int p,int l,int r,int &o){
  t[o=++ndc].sumv++;
  if(l==r) return;
  int mid=l+r>>1;
  if(p<=mid) modify(p,l,mid,t[o].l);
  else modify(p,mid+1,r,t[o].r);
}
int query(int L,int R,int l,int r,int o){
	if(!o||L>R) return 0;
	if(L<=l&&r<=R) return t[o].sumv;
	int mid=l+r>>1,res=0;
	if(L<=mid) res+=query(L,R,l,mid,t[o].l);
	if(R>mid)  res+=query(L,R,mid+1,r,t[o].r);
	return res;
}
int merge(int x,int y){
  	int o=++ndc; if(x*y==0) return x+y;
  	t[o].sumv=t[x].sumv+t[y].sumv;
  	t[o].l=merge(t[x].l,t[y].l);
  	t[o].r=merge(t[x].r,t[y].r);
  	return o;
}
int idx(char c){return c-'a';}
struct SAM{
	int last,ndc,ch[N][26],step[N],fa[N],sa[N],c[N],f[N],pos[N];
	void init(){
		re(ch[1]);ndc=last=1;
	}
	int New(int x){
	  step[++ndc]=x;
	  memset(ch[ndc],0,sizeof(ch[ndc]));
	  fa[ndc]=f[ndc]=0;
	  return ndc;
	}
	void extend(int c,int p){
		int v=last,u=New(step[v]+1);last=u;
		for(;!ch[v][c];v=fa[v]) ch[v][c]=u;
		if(!v) fa[u]=1;
		else{
		  int x=ch[v][c];
		  if(step[v]+1==step[x]) fa[u]=x;
		  else{
		    int y=New(step[v]+1);
		    memcpy(ch[y],ch[x],sizeof(ch[y]));
		    fa[y]=fa[x];
		    fa[x]=fa[u]=y;
		    for(;ch[v][c]==x;v=fa[v]) ch[v][c]=y;
		  }
		}
		if(p) modify(p,1,n,rt[u]),pos[u]=p;
	}
	 void jp(){
  	 	for(int i=1;i<=ndc;i++) c[step[i]]++;
	 	for(int i=1;i<=n;i++) c[i]+=c[i-1];
	 	for(int i=1;i<=ndc;i++) sa[c[step[i]]--]=i;
	 	for(int i=ndc;i;i--){
	 	  int x=sa[i];
	 	  rt[fa[x]]=merge(rt[x],rt[fa[x]]);
		}
    }
}S1,S2;
int main(){
	S1.init();
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=1;i<=n;i++) S1.extend(idx(s[i]),i);
	S1.jp();
	scanf("%d",&m);
	for(int i=1,l,r;i<=m;i++){
		scanf("%s%d%d",s+1,&l,&r);ans=0;
		int l1=strlen(s+1),tot=0;
		S2.init();
		for(int j=1;j<=l1;j++) S2.extend(idx(s[j]),0);
		for(int j=1;j<=S2.ndc;j++) S2.f[j]=S2.step[j];
		
		for(int j=1,u1=1,u2=1;j<=l1;j++){
			int c=idx(s[j]);
			u2=S2.ch[u2][c];
			if(S1.ch[u1][c]&&query(l+tot,r,1,n,rt[S1.ch[u1][c]])) u1=S1.ch[u1][c],tot++;
			else{
			  while(u1&&!(S1.ch[u1][c]&&query(l+tot,r,1,n,rt[S1.ch[u1][c]]))){
			  		if(!tot) {u1=0;break;}
			  		tot--;
					if(tot==S1.step[S1.fa[u1]]) u1=S1.fa[u1];
			  }
			  if(!u1) tot=0,u1=1;
			  else ++tot,u1=S1.ch[u1][c];
			}
			int x=u2;
			for(;x;x=S2.fa[x]) if(tot<=S2.step[S2.fa[x]])
				ans+=S2.f[x]-S2.step[S2.fa[x]],S2.f[x]=S2.step[S2.fa[x]];
			else
			    {ans+=S2.f[x]-tot,S2.f[x]=tot;break;}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
