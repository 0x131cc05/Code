#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;

typedef pair<int, int> P;

int w, h, osu[N], arc[N];

int id(int x, int y) {
    if (!y) return x;
    if (x == w) return y + w;
    if (y == h) return 2 * w - x + h;
    if (!x) return 2 * w + 2 * h - y;
}

void output(double pos) {
    if (pos <= w) printf("%.1lf 0 ", pos);
    else if (pos <= w + h) printf("%d %.1lf ", w, pos - w);
    else if (pos <= w * 2 + h) printf("%.1lf %d ", w * 2 + h - pos, h);
    else printf("0 %.1lf ", w * 2 + h * 2 - pos);
}

int main() {
    int n; scanf("%d%d%d", &n, &w, &h);
    vector<P> vec;
    for (int i = 1; i <= n; i++) {
        int x0, y0, x1, y1; scanf("%d%d%d%d", &x0, &y0, &x1, &y1);
        int A = id(x0, y0), B = id(x1, y1);
        if (A > B) swap(A, B);
        vec.push_back(P(A, B));
    }
    sort(vec.begin(), vec.end(), [](P a, P b) {
        return a.first < b.first;
    });
    for (int i = 0, mx = 0, mn = w * 2 + h * 2; i < vec.size(); i++) 
        osu[i] = mx, arc[i] = mn, mn = min(mn, vec[i].second), mx = max(mx, vec[i].second);
    int mn = w * 2 + h * 2, mx = 0;
    for (int i = (int)vec.size() - 1; i >= 0; i--) {
        if (mn <= mx) break;
        if (mn > osu[i] && vec[i].first < arc[i] && mn > vec[i].second) {
            puts("1"), output(vec[i].first + 0.5), output(mn - 0.5), exit(0);
        }
        mn = min(mn, vec[i].second);
        mx = max(mx, vec[i].first);
    }
    puts("2"), output(0.5), output(w + h - 0.5), puts(""), output(w * 2 + h + 0.5), output(w - 0.5); 
}
