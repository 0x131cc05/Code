#include <bits/stdc++.h>
using namespace std;

#define db long double

struct WaitingForBusAgain {
    double expectedBus(vector<int> f) {
        int n = f.size(), mn = 1e9;
        for (int i = 0; i < n; i++) 
            mn = min(mn, f[i]);
        db ans = 0;
        for (int i = 1; i < n; i++) {
            vector<db> coef = {i * ((db)mn / f[i])};
            for (int j = 0; j < n; j++) if (j != i) {
                vector<db> nxt(coef.size() + 1);
                db w = -(db)mn / f[j];
                for (int j = 0; j < coef.size(); j++)
                    nxt[j + 1] = coef[j] * w;
                coef.push_back(0);
                for (int j = 0; j < coef.size(); j++)
                    coef[j] += nxt[j];
            }
            db res = 0; 
            for (int j = 0; j < coef.size(); j++) 
                res += coef[j] / (j + 1);
            ans += res;
        }
        return ans;
    }
};