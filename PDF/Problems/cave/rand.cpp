#include <bits/stdc++.h>
using namespace std;
const int N = 6;
int a[N], b[N];
inline int Rand() {return rand() << 16 | rand();}
int main() {
    srand((long long)new char);
    printf("%d\n", N);
    for (int i = 1; i <= N; i++) a[i] = i;
    random_shuffle(a + 1, a + N + 1);
    for (int i = 1; i <= N; i++) printf("%d ", a[i]);
    puts("");
    for (int i = 1; i <= N; i++) printf("%d ", Rand() % 10);
    puts("");
    for (int i = 2; i <= N; i++) printf("%d %d\n", rand() % (i - 1) + 1, i);
}
