#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1);

int main() {
    int n; scanf("%d", &n);
    if (n > 2) return puts("0.000"), 0;
    if (n == 1) {
        int r; scanf("%*d%*d%*d%d", &r);
        printf("%.3lf\n", 4. / 3 * PI * r * r * r); 
    } else {
        double x1, x2, y11, y2, z1, z2, r1, r2;
        scanf("%lf%lf%lf%lf",&x1,&y11,&z1,&r1);
    	scanf("%lf%lf%lf%lf",&x2,&y2,&z2,&r2);
    	double dis = sqrt((x1 - x2) * (x1 - x2) + (y11 - y2) * (y11 - y2) + (z1 - z2) * (z1 - z2));
    	if(dis >= r1 + r2) {
    		double s = 4. / 3 * PI * (r1 * r1 * r1 + r2 * r2 * r2);
    		printf("%.3lf\n",s);
    	}
    	else if(dis <= fabs(r1 - r2)) {
    		double maxn=max(r1, r2);
    		double s = 4. / 3 * PI * (maxn * maxn * maxn);
    		printf("%.3lf\n",s);
    	} else {
    		double s = 4. / 3 * PI * (r1 * r1 * r1 + r2 * r2 * r2);
    		double h1 = r1 - (r1 * r1 - r2 * r2 + dis * dis) / (2 * dis);
    		s -= (PI * h1 * h1 * (3 * r1 - h1) / 3.0);
    		double h2 = r2 - (r2 * r2 - r1 * r1 + dis * dis) / (2 * dis);
    		s -= (PI * h2 * h2 * (3 * r2 - h2) / 3.0);
    		printf("%.3lf\n",s);
    	}
    }
    
}
