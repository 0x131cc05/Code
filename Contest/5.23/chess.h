/*
        -1 up
        -2 down
        -3 left
        -4 right
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read(){
	int x=0,w=1;
	char ch=0;
	while (ch<'0' || ch>'9'){
		ch=getchar();
		if (ch=='-') w=-1;	
	}
	while (ch<='9' && ch>='0'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*w;
}
inline void move_chess(int &x,int &y,int k){
	if (k==-1) --x;
	if (k==-2) ++x;
	if (k==-3) --y;
	if (k==-4) ++y;
}
inline void WA(){
	puts("Wrong Answer!");
	exit(0);
}
inline void chk_pos(int x,int y){
	if (x<1 || x>4 || y<1 || y>4) WA(), cout << "No" << endl;
}
int Type,T,sx,sy,Val;
char s[10005];
Alice girl;
Bob boy;
int main(){
//	freopen("chess.in","r",stdin);
//	freopen("chess.out","w",stdout);
	Type=read(),T=read(),Val=read(),sx=read(),sy=read();
	girl.initA(Type,Val),boy.initB(Type);
	scanf("%s",s+1);
	for (int i=1;i<=T;++i){
		if (s[i]=='A'){
			int now_move=girl.moveA(sx,sy);
			if (now_move>-1 || now_move<-4) WA();
			move_chess(sx,sy,now_move);
			chk_pos(sx,sy);
		}else{
			int now_move=boy.moveB(sx,sy);
			if (now_move>=-4 && now_move<=-1){
				move_chess(sx,sy,now_move);
				chk_pos(sx,sy);
			}else if (now_move>=1){
			    cout << now_move << endl;
				if (now_move==Val){
					puts("Accepted!");
					return 0;
				}else WA();
			}
		}
	}
	cout << "FUCK" << endl;
	WA();
	return 0;
}
