#include <bits/stdc++.h>

#include "testlib.h"

using namespace std;

void Judge () {
    string str;
	cin >> str;
	if (str == "WA_0\%lavvnw;hafhaefwaaoijvasf") {
		getline(cin, str);
		quitf(_wa, str.c_str());
	} else if (str == "PC_30\%apjfabfa;fbwbca;hvw") {
		getline(cin, str);
		quitp(30, str.c_str());
	} else if (str == "AC_100\%afjiwbbaclvgawdhwal;d") {
		getline(cin, str);
		quitf(_ok, str.c_str());
	} else {
		quitf(_wa, "不是合法的结果(是否向标准输出输出了信息?)");
	}
}

int main(int argc,char *argv[]){
	registerInteraction(argc, argv);
	int n = inf.readInt(), m = inf.readInt(), T = inf.readInt(), subtask = inf.readInt();
	printf("%d %d %d %d\n", n, m, T, subtask);
	for (int i = 0; i < n; i++) {
		int pi = inf.readInt();
		printf("%d%c", pi, " \n"[i == n - 1]);
	}
	for (int i = 0; i < m; i++) {
		int ui = inf.readInt(), vi = inf.readInt();
		printf("%d %d\n", ui, vi);
	}
	fflush(stdout);
    Judge();
    return 0;
}
