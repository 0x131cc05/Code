#include <cstdio>
#include <algorithm>
#include <assert.h>
int TC, N, C, Q, a[30001];
long long count[30002][5]; // count[start][c]
long long marginL[30002][5], marginR[30002][5];
int F(int pos, long long t)
{
	if (t > count[1][C])
		return -1;
	int start = 1, rC = C;
	while (1)
	{
		int l = start, r = N + 1;
		while (l < r)
		{
			int m = l + r >> 1;
			if (marginL[m][rC] - marginL[start - 1][rC] < t && t <= count[start][rC] - marginR[m][rC] + marginR[start - 1][rC])
				l = m + 1;
			else
				r = m;
		}
		t -= marginL[l - 1][rC] - marginL[start - 1][rC];
		if (pos < l)
			return a[pos];
		std::pair < int, std::pair < int, long long > > Q[7];
		int D = 0;
		for (int i = 0; i <= rC && l + i <= N; i++)
			Q[++D] = { a[l + i], { i, count[l + i + 1][rC - i] } };
		std::sort(Q + 1, Q + D + 1);
		for (int i = 1; i <= D; i++)
		{
			if (t <= Q[i].second.second)
			{
				if (l <= pos && pos <= l + Q[i].second.first)
				{
					return a[l + l + Q[i].second.first - pos];
				}
				start = l + Q[i].second.first + 1;
				rC -= Q[i].second.first;
				break;
			}
			else
				t -= Q[i].second.second;
		}
	}
}
int main()
{
	for (scanf("%d", &TC); TC--; )
	{
		scanf("%d%d%d", &N, &C, &Q);
		for (int i = 1; i <= N; i++)
			scanf("%d", a + i);
		for (int i = 1; i <= N + 1; i++)
		{
			count[i][0] = 1;
			marginL[i][0] = marginR[i][0] = 0;
		}
		for (int j = 0; j <= C; j++)
		{
			count[N][j] = count[N + 1][j] = 1;
			marginL[N][j] = marginR[N][j] = 1;
			for (int i = N - 1; i; i--)
			{
				count[i][j] = count[i + 1][j];
				marginL[i][j] = marginR[i][j] = 0;
				for (int k = 1; k <= j && i + k <= N; k++)
				{
					count[i][j] += count[i + k + 1][j - k];
					if (a[i] > a[i + k])
						marginL[i][j] += count[i + k + 1][j - k];
					else
						marginR[i][j] += count[i + k + 1][j - k];
				}
			}
		}
		for (int j = 0; j <= C; j++)
			for (int i = 1; i <= N; i++)
			{
				marginL[i][j] += marginL[i - 1][j];
				marginR[i][j] += marginR[i - 1][j];
			}
		while (Q--)
		{
			int pos;
			long long t;
			scanf("%d%lld", &pos, &t);
			printf("%d\n", F(pos, t));
		}
	}
	return 0;
}