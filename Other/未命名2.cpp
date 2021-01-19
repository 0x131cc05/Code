#include <bits/stdc++.h>
using namespace std;

int main() {
    for (int i = 0; i < 3; i++)
        for (int k = 0; k < 3; k++) 
            for (int j = 0; j < 3; j++) {
                cout << "res[" << i << "][" << j << "] += a[" << i << "][" << k << "] * b[" << k << "][" << j << "];" << endl; 
            }  
}
