#include <bits/stdc++.h>
using namespace std;

template<class T> void read(T &x) {
	x = 0; char c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

template<class T, class... Tail> void read(T &x, Tail& ...tail) {
	read(x), read(tail...);
}

int main() {
	int n; read(n);
	for (int i = 1, t; i <= n; i++) {
		read(t);
	}
}
