#include <bits/stdc++.h>
using namespace std;
const int N = 100000;
int a[N], b[N];
inline int Rand() {return rand() << 16 | rand();}
int main() {
	freopen("cave20.in", "w", stdout);
    srand((long long)new char);
    printf("%d\n", N);
    for (int i = 1; i <= N; i++) a[i] = Rand() % 20000;
    //random_shuffle(a + 1, a + N + 1);
    for (int i = 1; i <= N; i++) printf("%d ", a[i]);
    puts("");
    for (int i = 1; i <= N; i++) printf("%d ", Rand() % 1000000000);
    puts("");
    for (int i = 2; i <= N; i++) printf("%d %d\n", min(max(rand() % 5000 + i - 5000, 1), i - 1), i);
}
