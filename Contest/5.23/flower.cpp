#include <bits/stdc++.h>

class Bob {

public : 

inline int UP() { lstx--; return -1;}
inline int DOWN() { lstx++; return -2; }
inline int LEFT() { lsty--; return -3; }
inline int RIGHT() { lsty++; return -4; }

inline bool Center(int x, int y) {
    return min(x, y) >= 2 && max(x, y) <= 3;
}

inline int min(int x, int y) {
    return x < y ? x : y;
}

inline int max(int x, int y) {
    return x + y - min(x, y);
}

inline int GoSlide(int x, int y) {
    if (Center(x, y)) {
        if (x == 2) return UP();
        return DOWN();
    }
    if (x <= 2) return RIGHT();
    return LEFT();
}

inline int GoCenter(int x, int y) {
    if (x == 1 && y == 1) return RIGHT();
    if (x == 1 && y == 4) return LEFT();
    if (x == 4 && y == 1) return UP();
    if (x == 4 && y == 4) return DOWN();
    if (x == 1) return DOWN();
    return UP();
}

int lstx, lsty, a, b, c, d; bool start;

void initB(int type) {
    lstx = lsty = ans = 0, start = false;
}

static int ans;

int moveB(int x, int y) {
    if (ans) return ans;
    if (x == 1) return DOWN();
    else if (!start) return UP();
    if (lstx) {
        if (x == 1 && y == 1)
            GoCenter(x, y);
        if (x == 2 && y == 1)
            GoCenter(x, y);
        if (x == 2 && y == 1)
            DOWN();
        if (x == 2 && y == 3)
            DOWN();
        if (x == 3 && y == 4)
            LEFT();
        if (x == 2 && y == 2)
            LEFT();
        if (x == 2 && y == 3)
            LEFT();
        if (x == 4 && y == 3)
            RIGHT();
        if (x == 4 && y == 4)
            LEFT();
        if (x == 3 && y == 1)
            GoCenter(x, y);
        if (x == 2 && y == 4)
            DOWN();
        if (x == 1 && y == 2)
            LEFT();
        if (x == 3 && y == 3)
            GoCenter(x, y);
        if (x == 4 && y == 2)
            LEFT();
        if (x == 3 && y == 4)
            DOWN();
        if (x == 2 && y == 4)
            DOWN();
        if (x == 4 && y == 3)
            DOWN();
        if (x == 1 && y == 2)
            UP();
        if (x == 1 && y == 1)
            RIGHT();
        if (x == 4 && y == 4)
            UP();
        if (x == 3 && y == 3)
            GoCenter(x, y);
        if (x == 1 && y == 3)
            RIGHT();
        if (x == 3 && y == 3)
            LEFT();
        if (x == 2 && y == 2)
            LEFT();
        if (x == 1 && y == 4)
            DOWN();
        if (x == 2 && y == 1)
            UP();
        if (x == 2 && y == 4)
            DOWN();
        if (x == 1 && y == 1)
            RIGHT();
        if (x == 3 && y == 4)
            GoCenter(x, y);
        if (x == 2 && y == 4)
            RIGHT();
    } 
    if (!start) return GoCenter(x, y);
    if (a == 2 && d == 1) {
        int t = c * 2, delta = b + c - t;
        return UP();
    }
    if (a == 2 && d == 0) {
        int t = c * 2 - 1, delta = b + c - t;
        return DOWN();
    }
    if (a == 3 && d == 1) {
        int t = c * 2 + 1, delta = b + c - t;
        return LEFT();
    }
    if (a == 3 && d == 0) {
        int t = c * 2, delta = b + c - t;
        return RIGHT();
    }
    if (start) {
        int len = (b - 1) * 3 + 1;
        if (a == 1 || a == 3) len++;
        if (d == 1 || d == 3) len++;
        if (a == 2) len += 2;
        if (d == 0) len += 2;
        if (len == 1) return UP();
        if (len == 2) return DOWN();
        if (len == 3) return LEFT();
        return RIGHT();
    }
    return GoCenter(x, y);
}

};int Bob::ans;

class Alice {
    
public :
int msg[15], lstx, lsty, nw, a, b, c, d, t, vv; bool start;

void initA(int type, int v) {
    Bob::ans = 0, vv = v;
    for (int i = 0; i < 15; i++) 
        msg[i] = v % 4, v /= 4;
    lstx = lsty = 0, nw = 0, start = false;
}

inline int GoCenter(int x, int y) {
    if (x == 1 && y == 1) return RIGHT();
    if (x == 1 && y == 4) return LEFT();
    if (x == 4 && y == 1) return UP();
    if (x == 4 && y == 4) return DOWN();
    if (x == 1) return DOWN();
    return UP();
}


inline int UP() { lstx--; return -1;}
inline int DOWN() { lstx++; return -2; }
inline int LEFT() { lsty--; return -3; }
inline int RIGHT() { lsty++; return -4; }

inline int min(int x, int y) {
    return x < y ? x : y;
}

inline int max(int x, int y) {
    return x + y - min(x, y);
}

inline bool Center(int x, int y) {
    return min(x, y) >= 2 && max(x, y) <= 3;
}

inline int GoSlide(int x, int y) {
    if (Center(x, y)) {
        if (x == 2) return UP();
        return DOWN();
    }
    if (x <= 2) return RIGHT();
    return LEFT();
}

int moveA(int x, int y) { 
    Bob::ans = vv;
    if (!start) {
        if (x == 1) return DOWN();
        return UP();
    }
    if (lstx != x || lsty != y) {
        if (Center(x, y)) {
            if (lstx == 0) return GoSlide(x, y);
            int len = (b - 1) * 3 + 1;
            if (a == 1 || a == 3) len++;
            if (d == 1 || d == 3) len++;
            if (a == 2) len += 2;
            if (d == 0) len += 2;
            if (len == 1) return UP();
            if (len == 2) return DOWN();
            if (len == 3) return LEFT();
            return DOWN();
        } else return GoSlide(x, y);
    }
    if (start) {
        if (a == 2 && d == 1) {
        int t = c * 2, delta = b + c - t;
        return UP();
        }
        if (a == 2 && d == 0) {
            int t = c * 2 - 1, delta = b + c - t;
            return DOWN();
        }
        if (a == 3 && d == 1) {
            int t = c * 2 + 1, delta = b + c - t;
            return LEFT();
        }
        if (a == 3 && d == 0) {
            int t = c * 2, delta = b + c - t;
            return RIGHT();
        }
    } else {
        if (x == 2 && y == 2)
            RIGHT();
        if (x == 3 && y == 2)
            GoCenter(x, y);
        if (x == 3 && y == 2)
            LEFT();
        if (x == 3 && y == 4)
            DOWN();
        if (x == 4 && y == 1)
            RIGHT();
        if (x == 3 && y == 3)
            DOWN();
        if (x == 3 && y == 4)
            DOWN();
        if (x == 1 && y == 4)
            LEFT();
        if (x == 1 && y == 1)
            UP();
        if (x == 4 && y == 2)
            GoCenter(x, y);
        if (x == 3 && y == 1)
            LEFT();
        if (x == 2 && y == 3)
            UP();
        if (x == 4 && y == 4)
            UP();
        if (x == 1 && y == 3)
            GoCenter(x, y);
        if (x == 4 && y == 1)
            LEFT();
        if (x == 3 && y == 1)
            DOWN();
        if (x == 1 && y == 4)
            RIGHT();
        if (x == 2 && y == 3)
            UP();
        if (x == 2 && y == 2)
            GoCenter(x, y);
        if (x == 1 && y == 1)
            RIGHT();
        if (x == 4 && y == 4)
            DOWN();
        if (x == 2 && y == 4)
            LEFT();
        if (x == 4 && y == 4)
            LEFT();
        if (x == 3 && y == 3)
            LEFT();
        if (x == 2 && y == 1)
            UP();
        if (x == 3 && y == 2)
            GoCenter(x, y);
        if (x == 3 && y == 1)
            UP();
        if (x == 2 && y == 2)
            LEFT();
        if (x == 4 && y == 1)
            DOWN();
        if (x == 3 && y == 1)
            GoCenter(x, y);
        if (x == 4 && y == 2)
            RIGHT();
        if (x == 3 && y == 1)
            GoCenter(x, y);
        if (x == 1 && y == 4)
            RIGHT();
        if (x == 3 && y == 4)
            LEFT();
        if (x == 4 && y == 1)
            LEFT();
        if (x == 4 && y == 3)
            LEFT();
        if (x == 3 && y == 3)
            DOWN();
        if (x == 1 && y == 1)
            UP();
        if (x == 1 && y == 3)
            RIGHT();
        if (x == 4 && y == 1)
            UP();
        if (x == 1 && y == 4)
            UP();
        if (x == 4 && y == 2)
            GoCenter(x, y);
        if (x == 1 && y == 4)
            UP();
        if (x == 1 && y == 4)
            LEFT();
        if (x == 2 && y == 1)
            UP();
        if (x == 3 && y == 4)
            GoCenter(x, y);
        if (x == 1 && y == 1)
            RIGHT();
        if (x == 3 && y == 3)
            DOWN();
        if (x == 1 && y == 1)
            UP();
        if (x == 4 && y == 3)
            LEFT();
    }
}

};

#include "chess.h"

