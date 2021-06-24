#include <bits/stdc++.h>
using namespace std;
int prime[] = {469762049, 998244353, 1004535809, 1e9 + 7, 1e8 + 7, 1e9 + 9, 167772161, 122420729, 29050993, 68861641};
int out[] = {8, 9, 10, 198, 192, 200, 500, 497, 498, 492};
int main() {
	for (int i = 7; i <= 10; i++) {
		char s[10]; sprintf(s, "silver%d.in", i);
		freopen(s, "w", stdout);
		cout << out[i - 1] << ' ' << prime[i - 1] << endl;
		fclose(stdout);
	}
}
