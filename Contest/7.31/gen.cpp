#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef long long LL;

int A[N], B[N]; LL C[N];

int main() {
    ofstream inp,oup; inp.open("N5.in"); oup.open("N5.out");
//    freopen("N1.in", "r", stdin), freopen("N1.out", "w", stdout);
    srand(((long long)new char) + time(0));
    int n = 50000;
    inp << n << endl;
    for (int i = 0; i <= n; i++) A[i] = rand(), inp << A[i] << ' ';
    inp << endl;
    for (int i = 0; i <= n; i++) B[i] = rand(), inp << B[i] << ' ';
    inp << endl;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            C[i + j] += (LL)A[i] * B[j];
    bool flag = true;
    if (rand() % 3 < 3) {
        int pos = rand() % (n + 1);
        C[pos]++, flag = false;
    }  
    for (int i = 0; i <= n * 2; i++) inp << C[i] << ' ';
    inp << endl;
    if (!flag) oup << "No" << endl;
    else oup << "Yes" << endl;
} 
