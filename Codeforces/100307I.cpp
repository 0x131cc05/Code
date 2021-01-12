#include <bits/stdc++.h>
using namespace std;

int main() {
    int p, v, l, r; cin >> p >> v, l = 0, r = p;
    vector<int> L, R;
    for (int l1 = 0, r1 = v, t = 0; l != r; t++) {
        int mid = (l + r) >> 1; string a;
        cout << "check " << l << ' ' << mid << endl;
        cin >> a;
        if (a[0] == 'Y') r = mid;
        else l = mid + 1;
        for (int i = 0; i < t; i++) {
            r1 = min(r1, (r - L[i]) / (t - i));
            l1 = max(l1, (l - R[i] + t - i - 1) / (t - i));
        }
        L.push_back(l), R.push_back(r);
        l += l1, r += r1;
    }
    cout << "answer " << l << endl;
}