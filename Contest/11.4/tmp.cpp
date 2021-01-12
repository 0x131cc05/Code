#include <bits/stdc++.h>
using namespace std;

int A[2][2] = {1, 2, 3, 4};

int main() {
    while (233) {
        int a, b; scanf("%d%d", &a, &b), a--, b--, swap(A[a][0], A[a][1]), swap(A[0][b], A[1][b]);
        cout << A[0][0] << ' ' << A[0][1] << endl << A[1][0] << ' ' << A[1][1] << endl;
    }
}
