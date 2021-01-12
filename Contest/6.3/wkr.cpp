#include <bits/stdc++.h>

using namespace std;

char s[300050];
int nxt[300050][26];
long long f[300050];
int pre[1000050],pcnt;
int son[300050][20];
int wy[300050];
long long su[300050][20];

struct omfg
{
	int len;
	int st,ed;
};

omfg hev(int len,int st,int ed)
{
	return (omfg){len,st,ed};
}

void OPU(int st = 0)
{
	for(int i = st + 1;i <= pcnt; ++ i)
		putchar('a' + pre[i]);
	putchar('\n');
}

omfg OOOOOaaaa[300050];
int c1; 
int brain_power[300050];
int to_rev[300050];
int c2;

void Toaster(int p,int fg)
{
	pcnt = p;
//	cerr << c2 << endl;
	if(fg) // ½áÎ²ÊÇÖØ
	{
		for(int i = c2;i >= 0; -- i)
		{
			if(OOOOOaaaa[i].len)
			{
				if(OOOOOaaaa[i].len > p)
				{
					int ned = OOOOOaaaa[i].len - p;
					int st = OOOOOaaaa[i].st;
					for(int j = 18;j >= 0; -- j)
						if(ned - (1 << j) >= 0)
							st = son[st][j],
							ned -= (1 << j);
					int cn = 0;
					for(int j = st;;j = son[j][0])
					{
						if(j == OOOOOaaaa[i].ed) break;
						to_rev[++ cn] = wy[j];
					}
					reverse(to_rev + 1,to_rev + cn + 1);
			//		assert(to_rev.size() == p);
					for(int i = 1;i <= cn; ++ i)
						pre[p --] = to_rev[i];
				}
				else
				{
					int cn = 0;
					for(int j = OOOOOaaaa[i].st;;j = son[j][0])
					{
						if(j == OOOOOaaaa[i].ed) break;
						to_rev[++ cn] = wy[j];
					}
					reverse(to_rev + 1,to_rev + cn + 1);
			//		assert(to_rev.size() == p);
					for(int i = 1;i <= cn; ++ i)
						pre[p --] = to_rev[i];
				}
			}
			if(!p)
			{
				OPU();
				return ;
			}
			if(i)
			{
				pre[p --] = brain_power[i - 1];
				if(!p)
				{
					OPU();
					return ;
				}
			}
		}
		OPU(p);
	}
	else
	{
		for(int i = c2 - 1;i >= 0; -- i)
		{
			pre[p --] = brain_power[i];
			if(!p)
			{
				OPU();
				return ;
			}
			if(OOOOOaaaa[i].len)
			{
				if(OOOOOaaaa[i].len > p)
				{
					int ned = OOOOOaaaa[i].len - p;
					int st = OOOOOaaaa[i].st;
					for(int j = 18;j >= 0; -- j)
						if(ned - (1 << j) >= 0)
							st = son[st][j],
							ned -= (1 << j);
					int cn = 0;
					for(int j = st;;j = son[j][0])
					{
						if(j == OOOOOaaaa[i].ed) break;
						to_rev[++ cn] = wy[j];
					}
					reverse(to_rev + 1,to_rev + cn + 1);
			//		assert(to_rev.size() == p);
					for(int i = 1;i <= cn; ++ i)
						pre[p --] = to_rev[i];
				}
				else
				{
					int cn = 0;
					for(int j = OOOOOaaaa[i].st;;j = son[j][0])
					{
						if(j == OOOOOaaaa[i].ed) break;
						to_rev[++ cn] = wy[j];
					}
					reverse(to_rev + 1,to_rev + cn + 1);
			//		assert(to_rev.size() == p);
					for(int i = 1;i <= cn; ++ i)
						pre[p --] = to_rev[i];
				}
			}
			if(!p)
			{
				OPU();
				return ;
			}
		}
		OPU(p);
	}
}

int main()
{
    freopen("ex_A2.in", "r", stdin);
	scanf("%s",s + 1);
	int len = strlen(s + 1);
	for(int i = len - 1;i >= 0; -- i)
	{
		memcpy(nxt[i],nxt[i + 1],sizeof(nxt[i]));
		nxt[i][s[i + 1] - 'a'] = i + 1;
	}
	for(int i = len;i >= 0; -- i)
	{
		if(i == 0)
		{
	//		printf("fuck\n");
		}
		f[i] = i > 0;
		for(int j = 0;j < 26; ++ j)
			if(nxt[i][j])
			{
				f[i] = min(f[i] + f[nxt[i][j]],1000000000000000000ll);
				if(f[i] == 1000000000000000000ll)
				{
					if(!son[i][0])
					{
						son[i][0] = nxt[i][j],wy[i] = j;
						for(int k = 0;k < j; ++ k)
							if(nxt[i][k])
								su[i][0] = min(su[i][0] + f[nxt[i][k]],1000000000000000000ll);
					}
				}
			}
		if(!son[i][0])
		{
			long long mx = 0,pr = 0,pp = 0,ppp;
			int mxp = 0;
			for(int j = 0;j < 26; ++ j)
				if(nxt[i][j])
				{
					if(f[nxt[i][j]] > mx)
						mx = f[nxt[i][j]],pr = pp,mxp = nxt[i][j],ppp = j;
					pp += f[nxt[i][j]];
				}
			wy[i] = ppp;
			son[i][0] = mxp;
			su[i][0] = pr;
		}
		for(int j = 1;j <= 18; ++ j)
		{
			if(son[i][j - 1])
				son[i][j] = son[son[i][j - 1]][j - 1],
				su[i][j] = min(su[i][j - 1] + su[son[i][j - 1]][j - 1] + 1,1000000000000000000ll);
			else
				son[i][j] = 0,
				su[i][j] = su[i][j - 1];
		}
	}
	int q; scanf("%d",&q);
	while(q --)
	{
		long long k;int p; scanf("%lld%d",&k,&p);
		if(k > f[0])
		{
			puts("-1");
			continue;
		}
		c1 = c2 = 0;
		int cur = 0;
		while(k)
		{
			bool fg = 0;
			int ls = cur;
			int len = 0;
			if(su[cur][0] < k && su[cur][0] + f[son[cur][0]] >= k)
			{
				for(int j = 18;j >= 0; -- j)
					if(son[cur][j] && (su[cur][j] < k && su[cur][j] + f[son[cur][j]] >= k))
					{
						k -= su[cur][j];
						cur = son[cur][j];
						len += 1 << j;
						if(k == 1)
						{
							OOOOOaaaa[c1 ++] = hev(len,ls,cur);
							Toaster(p,1); fg = 1; break;
						}
						else k --;
					}
				OOOOOaaaa[c1 ++] = hev(len,ls,cur);
				if(fg) break;
			}
			else
			{
				OOOOOaaaa[c1 ++] = hev(0,cur,cur);
			}
			for(int i = 0;i < 26; ++ i)
			{
				if(nxt[cur][i])
				{
					if(k <= f[nxt[cur][i]])
					{
						cur = nxt[cur][i];
						brain_power[c2 ++] = i;
						if(k == 1)
							Toaster(p,0),fg = 1;
						else k --;
						break;
					}
					k -= f[nxt[cur][i]];
				}
			}
			if(fg) break;
		}
	}
	return 0;
}
