#include <bits/stdc++.h>

using namespace std;

bool flg[11]; // 是否是类反猪 
// 桃 - 0 杀 - 1 闪 - 2 
// 决斗 - 3 南蛮入侵 - 4 万箭齐发 - 5 无懈可击 - 6
// 猪哥连弩 - 7 
struct Pig
{
	int typ; // 0 - 主猪  1 - 忠猪  2 - 反猪 
	int killc; // 本回合使用 "杀" 的数量 
	vector<int> card; // 卡牌
	bool zhong,fan; // 跳忠/跳反
	bool zhuge; // 是否有连弩
	int blo; // 血量上限
	int id; // 猪的编号，写着好玩 
	bool Era(int tar)
	{
		for(int i = 0;i < card.size(); ++ i)
			if(card[i] == tar)
			{
				card.erase(card.begin() + i);
				return true;
			}
		return false;
	}
	bool GetShan()
	{
		return Era(2);
	}
	bool GetSha()
	{
		return Era(1);
	}
	bool GetTao()
	{
		blo += Era(0);
		return blo > 0;
	}
	bool GetJD(Pig oth)
	{
		if(typ == 1 && oth.typ == 0) return 0;
		return GetSha();
	}
	bool GetWuXie(Pig oth,bool help) 
	{
		if(!help)
		{
			if(!oth.zhong && !oth.fan && oth.typ)
			{
				if(flg[oth.id] && typ == 0)
					return Era(6); 
			}
			if(oth.zhong || oth.typ == 0) 
				if(typ == 2)
				{
					bool f = Era(6);
					fan |= f;
					return f; 
				}
			if(oth.fan && oth.typ != 0)
				if(typ != 2)
				{
					bool f = Era(6);
					zhong |= f;
					return f;
				}
		}
		else
		{
			if(oth.zhong || oth.typ == 0) 
				if(typ != 2)
				{
					bool f = Era(6);
					zhong |= f;
					return f; 
				}
			if(oth.fan && oth.typ != 0)
				if(typ == 2)
				{
					bool f = Era(6);
					fan |= f;
					return f;
				}
		}
		return 0;
	}
}P[11];

int n,m;
int pd[2050],tp;
int fan;
char sp[11] = "PKDFNWJZ";

void Out(bool win)
{
	puts(win ? "MP" : "FP");
	for(int i = 1;i <= n; ++ i,printf("\n"))
		if(P[i].blo <= 0) printf("DEAD");
		else for(auto v : P[i].card)
			printf("%c ",sp[v]);
	exit(0);
}

void Draw(int id,int ct)
{
	for(int i = 1;i <= ct; ++ i)
	{
		P[id].card.push_back(pd[++ tp]);
		if(tp == m) tp --;
	}
}

bool ChkWuXie(int tar,bool help,int root)
{
	int fg = 0;
	for(int i = tar;;i ++)
	{
		if(i > n) i = 1;
		if(i == tar && fg) break; fg = 1;
		if(P[i].blo <= 0) continue;
		if(P[i].GetWuXie(P[root],help)) 
			return ChkWuXie(i,help ^ 1,root) ^ 1;
	}
	return 1;
}

void TakeDamage(int i,int st)
{
	P[i].blo --;
	if(P[i].blo <= 0)
	{
		P[i].GetTao();
		if(P[i].blo <= 0)
		{
			if(P[i].typ == 2)
			{
				cerr << i << endl;
				fan --;
				if(!fan)
					Out(1);
				Draw(st,3);
			}
			else if(P[i].typ == 1 && st == 1)
			{
				P[st].card.clear();
				P[st].zhuge = 0;
			}
			else if(P[i].typ == 0)
				Out(0);
		}
	}
	if(P[i].typ == 0)
		flg[st] = 1;
}

void UseNanZhu(int st)
{
	for(int i = st + 1;;i ++)
	{
		if(i > n) i = 1;
		if(i == st) break;
		if(P[i].blo <= 0) continue;
		if(ChkWuXie(st,1,i)) // 生效 
		{
			bool f = P[i].GetSha();
			if(!f)
			{
				TakeDamage(i,st);
			}
		}
	}
}

void UseWanJian(int st)
{
	for(int i = st + 1;;i ++)
	{
		if(i > n) i = 1;
		if(i == st) break;
		if(P[i].blo <= 0) continue;
		if(ChkWuXie(st,1,i)) // 生效 
		{
			bool f = P[i].GetShan();
			if(!f)
			{
				TakeDamage(i,st);
			}
		}
	}
}

void UseJueDou(int st,int tar)
{
	if(P[tar].id != 1)
	{
		if(P[tar].fan) P[st].zhong = 1;
		else P[st].fan = 1;
	}
	else
		P[st].fan = 1;
	if(ChkWuXie(st,1,tar))
	{
		while(1)
		{
			bool ftar = P[tar].GetJD(P[st]);
			if(!ftar)
			{
				TakeDamage(tar,st);
				return ;
			}
			ftar = P[st].GetJD(P[tar]);
			if(!ftar)
			{
				TakeDamage(st,tar);
				return ;
			}
		}
	}
}

void UseSha(int st,int tar)
{
	if(P[tar].id != 1)
	{
		if(P[tar].fan) P[st].zhong = 1;
		else P[st].fan = 1;
	}
	else
		P[st].fan = 1;
	bool ftar = P[tar].GetShan();
	if(!ftar) TakeDamage(tar,st);
}

int Nxt(int id)
{
	for(int i = id + 1;;i ++)
	{
		if(i > n) i = 1;
		if(P[i].blo > 0) return i;
	}
}

void Use(int i,int j)
{
	P[i].card.erase(P[i].card.begin() + j);
}

int mp[1050];

int main()
{
    freopen("7.in", "r", stdin);
	scanf("%d%d",&n,&m);
	mp['P'] = 0; mp['K'] = 1; mp['D'] = 2;
	mp['F'] = 3; mp['N'] = 4; mp['W'] = 5; mp['J'] = 6;
	mp['Z'] = 7;
	for(int i = 1;i <= n; ++ i)
	{
		char str[55]; scanf("%s",str);
		if(str[0] == 'M') P[i].typ = 0;
		else if(str[0] == 'Z') P[i].typ = 1;
		else P[i].typ = 2,fan ++;
		P[i].blo = 4; P[i].id = i;
		for(int j = 1;j <= 4; ++ j)
			scanf("%s",str),P[i].card.push_back(mp[str[0]]); 
	}
	for(int i = 1;i <= m; ++ i)
	{
		char str[5]; scanf("%s",str);
		pd[i] = mp[str[0]];
	}
	for(int i = 1;; ++ i)
	{
		if(i > n) i = 1;
		if(P[i].blo <= 0) continue;
		for(int j = 1;j <= n; ++ j)
		{
			printf("%d | ",P[j].blo);
			for(auto v : P[j].card)
				printf("%c ",sp[v]);
			printf("\n");
		}
		printf("---------------\n");
		Draw(i,2);
		P[i].killc = 0;
		bool fg = 1;
		while(fg && P[i].blo)
		{
			fg = 0;
			for(int j = 0;j < P[i].card.size() && !fg; ++ j)
			{
				if(P[i].card[j] == 0)
				{
					if(P[i].blo < 4)
					{
						P[i].blo ++;
						Use(i,j);
						fg = 1;
						break;
					}
				}
				else if(P[i].card[j] == 1)
				{
					if(P[i].zhuge || !P[i].killc)
					{
						int nx = Nxt(i);
						if(P[i].typ == 0)
						{
							if(P[nx].fan || (!P[nx].zhong && flg[nx]))
							{
								P[i].killc ++;
								Use(i,j);
								UseSha(i,nx);
								fg = 1;
								break;
							}
						}
						else if(P[i].typ == 1)
						{
							if(P[nx].fan && P[nx].typ)
							{
								P[i].killc ++;
								Use(i,j);
								UseSha(i,nx);
								fg = 1;
								break;
							}
						}
						else if(P[i].typ == 2)
						{
							if(P[nx].zhong || !P[nx].typ)
							{
								P[i].killc ++;
								Use(i,j);
								UseSha(i,nx); 
								fg = 1; 
								break;
							}
						}
					}
				}
				else if(P[i].card[j] == 3)
				{
					if(P[i].typ == 2)
					{
						Use(i,j);
						UseJueDou(i,1);
						fg = 1;
						break;
					}
					for(int k = i + 1;; ++ k)
					{
						if(k > n) k = 1;
						if(k == i) break;
						if(P[k].blo <= 0) continue;
						if(P[i].typ == 0)
						{
							if(P[k].fan || (!P[k].zhong && flg[k]))
							{
								Use(i,j);
								UseJueDou(i,k);
								fg = 1;
								break;
							}
						}
						else if(P[k].fan && P[k].typ)
						{
							Use(i,j);
							UseJueDou(i,k);
							fg = 1;
							break;
						}
					}
				}
				else if(P[i].card[j] == 4)
				{
					Use(i,j);
					UseNanZhu(i);
					fg = 1;
					break; 
				}
				else if(P[i].card[j] == 5)
				{
					Use(i,j);
					UseWanJian(i);
					fg = 1;
					break;
				}
				else if(P[i].card[j] == 7)
				{
					Use(i,j);
					P[i].zhuge = 1;
					fg = 1;
					break;
				}
			}
		}
	}
}
