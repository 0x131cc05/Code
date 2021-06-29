#include <bits/stdc++.h>
using namespace std;

const int N = 400010;

int val[N];

vector<int> minimal(vector<int> v) {
    int n = v.size(), i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        if (val[v[(i + k) % n]] == val[v[(j + k) % n]]) k++;
        else {
            if (val[v[(i + k) % n]] > val[v[(j + k) % n]]) i += k + 1;
            else j += k + 1;
            k = 0; 
        }
    }
    i = min(i, j);
    rotate(v.begin(), v.begin() + i, v.end());
    return v;
}

