#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int ban[31] = {2, 3, 6, 7, 8, 11, 12, 15, 18, 19, 22, 23, 24, 27, 28, 31, 32, 33, 43, 44, 47, 48, 60, 67, 72, 76, 92, 96, 108, 112, 128};

struct QuadraticJumping {
    LL jump(LL target) {
        LL sum = 0;
        for (int i = 1; i; i++) {
            sum += (LL)i * i;
            if (sum >= target && (sum - target) % 2 == 0) {
                LL diff = (sum - target) / 2;
                if (diff > 128 || find(ban, ban + 31, diff) == ban + 31)
                    return i;
            }
        }
    }
};
