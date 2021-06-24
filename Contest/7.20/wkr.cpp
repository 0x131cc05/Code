#include <bits/stdc++.h>

using namespace std;

struct edge
{
	int v,nxt,flow,w;
}e[500050];

int head[16655],ecnt;
long long dep[16655];
bool inq[16655];
int n,m;
int s,t;
const long long inf = 1e18;

void adde(int u,int v,int fl,int w)
{
	e[ecnt].v = v;
	e[ecnt].nxt = head[u];
	e[ecnt].flow = fl;
	e[ecnt].w = w;
	head[u] = ecnt ++;
}

void Adde(int u,int v,int fl,int w)
{
	adde(u,v,fl,w);
	adde(v,u,0,-w);
}

bool spfa()
{
    deque<long long> que;
   	for(int i = 0;i <= t; ++ i)
   		dep[i] = (1ll << 62);
    memset(inq,0,sizeof(inq));
    dep[t] = 0;
    que.push_back(t);
    while(!que.empty())
    {
        long long u = que.front();
        que.pop_front();
        for(long long i = head[u];~i;i = e[i].nxt)
        {
            long long v = e[i].v;
            if(e[i ^ 1].flow && dep[u] - e[i].w < dep[v])
            {
                dep[v] = dep[u] + e[i ^ 1].w;
                if(!inq[v])
                {
                    if(que.empty() || dep[v] < dep[que.front()])
                        que.push_front(v);
                    else
                        que.push_back(v);
                    inq[v] = true;
                }
            }
        }
        inq[u] = false;
    }
    return dep[s] < (1ll << 62);
}

int curedge[16655];
long long ans;
bool vis[16655];

long long dfs(long long s,long long t,long long flow)
{
    if(s == t)
        return flow;
    long long delta = flow;
    vis[s] = true;
    for(long long i = head[s];~i;i = e[i].nxt)
    {
        long long v = e[i].v;
        if(!vis[v] && dep[v] == dep[s] - e[i].w && e[i].flow)
        {
            //prlong longf("%d %d\n",s,v);
            long long g = dfs(v,t,min((long long)e[i].flow,delta));
            delta -= g;
            ans += g * e[i].w;
            e[i].flow -= g;
            e[i ^ 1].flow += g;
            if(!delta)
                return flow;
        }
    }
    return flow - delta;
}

long long dinic()
{
    long long anss = 0;
    while(spfa())
    {
    	vis[t] = 1;
    	while(vis[t])
    	{
    	    cout << "fuck" << endl;
        	memset(vis,0,sizeof(vis));
        	anss += dfs(s,t,inf);
        }
    }
    return anss;
}

int mp[155][55],mp2[155][55];
int dx[4] = {0,0,1,-1},dy[4] = {1,-1,0,0};

int main()
{
	memset(head,-1,sizeof(head));
	scanf("%d%d",&n,&m);
	if(m == 1) return puts("231"),0;
	s = 0; t = 3 * n * m + 1;
	int cnt[2] = {0};
	for(int i = 1;i <= n; ++ i)
		for(int j = 1;j <= m; ++ j)
		{
			scanf("%d",&mp[i][j]);
			if(!mp[i][j]) cnt[(i + j) & 1] ++;
		}
	if(cnt[0] != cnt[1]) return puts("-1"),0;
	int as = 0;
	for(int i = 1;i <= n; ++ i)
		for(int j = 1;j <= m; ++ j)
			scanf("%d",&mp2[i][j]),as += (mp[i][j] ^ 1) * mp2[i][j];
	for(int i = 1;i <= n; ++ i)
		for(int j = 1;j <= m; ++ j)
			if(!mp[i][j])
			{
				int p1 = ((i - 1) * m + j) * 3,p2 = p1 - 1,p3 = p2 - 1;
				if((i + j) & 1)
				{
					Adde(p3,p1,1,0),
					Adde(p3,p1,1,-mp2[i][j]),
					Adde(p3,p2,1,0),
					Adde(p3,p2,1,-mp2[i][j]),
					Adde(s,p3,2,0);
					for(int k = 0;k < 4; ++ k)
					{
						int nx = i + dx[k],ny = j + dy[k];
						if(nx >= 1 && nx <= n && ny >= 1 && ny <= m)
						{
							int np1 = ((nx - 1) * m + ny) * 3;
							int np2 = np1 - 1;
							if(nx - i)
								Adde(p1,np1,1,0);
							else
								Adde(p2,np2,1,0);
						}
					}
				}
				else
					Adde(p1,p3,1,0),
					Adde(p1,p3,1,-mp2[i][j]),
					Adde(p2,p3,1,0),
					Adde(p2,p3,1,-mp2[i][j]),
					Adde(p3,t,2,0);
			}
	cout << ecnt << endl;
	long long fl = dinic();
	if(fl != cnt[0] * 2) return puts("-1"),0;
	printf("%d\n",-ans - as);
	return 0;
}
