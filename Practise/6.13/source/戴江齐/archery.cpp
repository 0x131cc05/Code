//O(n^2), but can be optimalized with a bit of data structure
//terribly sorry to be too cai to solve this problem
#include <bits/stdc++.h>
#define rep(i, n) for(int i = 0; i < (int)(n); i ++)
#define rep1(i, n) for(int i = 1; i <= (int)(n); i ++)
#define MP make_pair

using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int INF = 0x3f3f3f3f;

int n, r, x, y, arr[400005];

vector<int> chv0, chv1;
int ret[400005];

bool ex0[400005], ex1[400005];
vector<int> pm, sm;
void calc(vector<int>& fr, bool to[])
{
	if(fr[2] == 0) fr[1] = 0;
	pm.clear(); sm.clear();
	int ct = INF;
	rep(i, n + 2) if(ct > fr[i]) {
		ct = fr[i]; if(i != 0) pm.push_back(i - 1);
	}
	ct = INF;
	for(int i = n + 1; i >= 0; i --) if(ct > fr[i]) {
		ct = fr[i]; if(i != n + 1) sm.push_back(i);
	}
	
	rep(i, n + 1) to[i] = false;
	if(pm.size() < sm.size()) swap(pm, sm);
	for(int i = (int)sm.size(); i < (int)pm.size(); i ++) to[pm[i]] = true;
}
int calc()
{
	calc(chv0, ex0); calc(chv1, ex1);
	rep(i, n + 1) ex0[i] ^= ex1[i];
	int pos = -1;
	rep(i, n + 1) if(ex0[i]) pos = i;
	bool dec = chv0[pos] > chv0[pos + 1] || chv1[pos] > chv1[pos + 1];
	if(arr[pos + 1] == -(pos + 1)) pos ++;
	if(dec) pos = (pos - r % n + n - 1) % n + 1;
	return pos;
}

int main()
{
	freopen("archery.in", "r", stdin);
	freopen("archery.out", "w", stdout); 
	
	scanf("%d%d%d", &n, &r, &x);
	arr[0] = 0; arr[1] = -2;
	for(int i = 2; i <= 2 * n; i ++) {
		scanf("%d", &y);
		arr[i] = arr[i - 1] + (y < x ? 1 : -1);
	}
	
	if(x == 1) {
		printf("%d\n", n); return 0;
	} else if(x == 2 * n) {
		printf("2\n"); return 0;
	}
	
	for(int i = 2; i <= 2 * n; i += 2) {
		chv0.clear(); chv1.clear();
		rep(j, 2 * n + 1) {
			int cval0 = arr[j] + (j >= i), cval1 = arr[j] - (j >= i);
			if(cval0 % 2 == 0) {
				chv0.push_back(cval0 / 2); chv1.push_back(cval1 / 2);
			}
		}
		ret[i / 2] = calc();
	}
	
	int mp = n;
	for(int i = n - 1; i >= 1; i --) if(ret[i] < ret[mp]) mp = i;
	printf("%d\n", mp);
	return 0;
}
