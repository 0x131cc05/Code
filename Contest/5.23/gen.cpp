#include <bits/stdc++.h>
using namespace std;

string t = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";

int main() {
    srand((long long)new char);
    for (int i = 1; i <= 30; i++) {
        printf("if (x == %d && y == %d)\n", rand() % 4 + 1, rand() % 4 + 1);
        int t = rand() % 5;
        if (t == 0) puts("    UP();");
        else if (t == 1) puts("    DOWN();");
        else if (t == 2) puts("    LEFT();");
        else if (t == 3) puts("    RIGHT();");
        else puts("    GoCenter(x, y);");
    }
}
