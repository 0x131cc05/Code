#include <cstdio>
#include <algorithm>
 
const int MN = 200005;
 
int N, M, A[MN], Ans;
 
inline bool check(int pos) {
	int Now = 0;
	for (int i = 1; i <= pos; ++i)
		Now = std::max(Now, A[i] + A[2 * pos - i + 1]);
	for (int i = 1; i <= N - pos; ++i) {
		int v = A[2 * pos + i] + A[2 * N - i + 1];
		if (v < M) return 0;
		Now = std::max(Now, v - M);
	}
	printf("check: %d %d\n", pos, Now);
	Ans = std::min(Ans, Now);
	return 1;
}
 
int main() {
	scanf("%d%d", &N, &M), Ans = M;
	for (int i = 1; i <= 2 * N; ++i) scanf("%d", &A[i]);
	std::sort(A + 1, A + 2 * N + 1);
	int l = 0, r = N, mid;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (check(mid)) r = mid - 1;
		else l = mid + 1;
	}
	printf("%d\n", Ans);
	return 0;
}
