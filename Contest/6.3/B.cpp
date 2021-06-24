#include <bits/stdc++.h>
using namespace std;

int n, d;

typedef long long LL;

struct Matrix {

double A[10][10];

Matrix() { memset(A, 0, sizeof(A)); }

double * operator [] (int t) { return A[t]; }

Matrix operator * (Matrix &b) {
    Matrix res;
    for (int i = 0; i < d; i++)
        for (int k = 0; k < d; k++)
            for (int j = 0; j < d; j++)
                res[i][j] += A[i][k] * b[k][j];
    return res;
}

Matrix operator * (double b) {
    Matrix res;
    for (int i = 0; i < d; i++)
        for (int j = 0; j < d; j++)
            res[i][j] = A[i][j] * b;
    return res;
}

Matrix operator + (Matrix b) {
    Matrix res;
    for (int i = 0; i < d; i++)
        for (int j = 0; j < d; j++)
            res[i][j] = A[i][j] + b[i][j];
    return res;
}

};

inline Matrix Pow(Matrix x, LL y) {
    Matrix res;
    for (int i = 0; i < d; i++) res[i][i] = 1;
    for (; y; y >>= 1, x = x * x) if (y & 1) res = res * x;
    return res; 
}

double wkr[10]; char s[3000010]; LL hh[10][10];

int main() {
    LL m; scanf("%d%d%lld%s", &n, &d, &m, s); double p = 1. / d;
    for (int i = d - 1, nw = 1; i < n; i += d, nw++) {
        for (int j = i - d + 1; j <= i; j++) hh[j % d][s[j] - '0'] += j + 1;
        if (n <= 3e5) {
            Matrix trans;
            for (int i = 0; i < d; i++) {
                int a = i, b = (i + 1) % d; Matrix tmp; tmp[a][b] = tmp[b][a] = 1. / nw, tmp[a][a] = tmp[b][b] = 1 - tmp[a][b];
                for (int j = 0; j < d; j++) if (j != a && j != b) tmp[j][j] = 1;
                trans = trans + tmp * p;
            }
            trans = Pow(trans, m); 
            for (int j = 0; j < d; j++) 
                for (int k = 0; k < d; k++)
                    wkr[k] += hh[j][k] * trans[j][k];
        } else 
            for (int j = 0; j < d; j++) 
                for (int k = 0; k < d; k++)
                    wkr[k] += hh[j][k] * p;
    }
    for (int i = 0; i < d; i++) printf("%.7lf\n", wkr[i]);
    
}
