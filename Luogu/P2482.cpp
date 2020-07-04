#include <bits/stdc++.h>
using namespace std;

enum card { P, K, D, F, N, W, J, Z };

enum ident { ZP, FP, UN }; // 主猪一开始就跳忠

int fuck[11], base[11], n, m; // 类反猪；每只猪一开始的身份

struct pig {

int blood;

ident identity;

vector<card> cards;

bool alive, strong; 
// 是否有连弩

pig() { blood = 4, alive = true, strong = false, identity = UN, cards.clear(); }

inline bool use(card c) {
    for (int i = 0; i < cards.size(); i++) if (cards[i] == c) 
        return cards.erase(cards.begin() + i), true;
    return false;
}

} p[11];

queue<card> pool;

inline void see() { // 重新认识每只猪
    for (int i = 2; i <= n; i++) 
        if (fuck[i] && p[i].identity == ZP) fuck[i] = 0;
}

inline void output(card c) {
    switch (c) {
        case P: putchar('P'); break;
        case K: putchar('K'); break;
        case D: putchar('D'); break;
        case F: putchar('F'); break;
        case N: putchar('N'); break;
        case W: putchar('W'); break;
        case J: putchar('J'); break;
        case Z: putchar('Z'); break;
        default: assert(0);
    }
}

inline card back(char c) {
    switch (c) {
        case 'P': return P;
        case 'K': return K;
        case 'D': return D;
        case 'F': return F;
        case 'N': return N;
        case 'W': return W;
        case 'J': return J;
        case 'Z': return Z;
        default: assert(0);
    }
}

inline void END() {
    if (p[1].alive) puts("MP");
    else puts("FP");
    for (int i = 1; i <= n; i++) {
        if (p[i].alive) {
            for (auto t : p[i].cards) output(t), putchar(' ');
            puts("");
        } else puts("DEAD");
    }
//    cout << 20000 + m - pool.size() << endl;
    exit(0);
}

inline void check() {
    if (!p[1].alive) END();
    bool flag = true;
    for (int i = 2; i <= n; i++) if (base[i] == 2 && p[i].alive == true)
        flag = false;
    if (flag) END();
}

inline void show(int from) {
    p[from].identity = base[from] <= 1 ? ZP : FP;
}

inline void die(int from, int to) { // from 造成了 to 的死亡
    assert(p[to].blood <= 0 && !p[to].use(P) && p[to].alive == true);
    p[to].cards.clear(), p[to].alive = false;
    check();
    if (base[to] == 2) {
        for (int i = 1; i <= 3; i++) {
            card t = pool.front(); pool.pop();
            p[from].cards.push_back(t);
        }
    }
    if (base[to] == 1 && base[from] == 0) 
        p[from].cards.clear(), p[from].strong = false;
}

inline void damage(int from, int to) { // from 对 to 造成伤害
    if (to == 1) fuck[from] = 1;
    p[to].blood--;
    if (p[to].blood <= 0) {
        if (p[to].use(P)) p[to].blood = 1;
        else die(from, to);
    }   
}

inline bool zjk(int a, int b) { // a, b 是否在同一阵营
    return base[a] / 2 == base[b] / 2;
}

inline bool zjk(int a, ident t) {
    if (t == ZP && a <= 1) return true;
    if (t == FP && a == 2) return true;
    return false;
}

bool wkr(int from, ident type) { 
    for (int i = 1; i <= n; i++) {
        int id = from + i - 1;
        if (id > n) id -= n;
        if (!p[id].alive) continue;
        if (type != UN && zjk(base[id], type)) {
            if (!p[id].use(J)) continue;
            show(id);
            if (wkr(id, type == ZP ? FP : ZP)) return false;
        }
    }
    return true;
}

inline void Strong(int u) {
    p[u].use(Z), p[u].strong = 1;
}

inline bool Kill(int u) { // u 尝试使用杀
    int target = 0; 
    if (u == 1) see();
    for (int i = 1; i < n; i++) {
        int id = u + i;
        if (id > n) id -= n;
        if (!p[id].alive) continue;
        if ((u == 1 && fuck[id]) || (p[id].identity != UN && !zjk(id, u))) {
            target = id; break;
        }
        return false;
    }
    if (u != 1 && p[1].alive && base[u] == 2) target = 1;
    if (!target) return false;
    if (!p[u].use(K)) return false;
    if (u != 1) show(u);
    if (!p[target].use(D)) damage(u, target);
    return true;
}

inline bool Arrow(int u) {
    if (!p[u].use(W)) return false;
    for (int i = 1; i < n; i++) {
        int id = u + i;
        if (id > n) id -= n;
        if (!p[id].alive) continue;
        if (wkr(u, p[id].identity)) {
            if (!p[id].use(D)) damage(u, id);
        }
    }
    return true;
}

inline bool Fight(int u) {
    int target = 0;
    for (int i = 1; i < n; i++) {
        int id = u + i;
        if (id > n) id -= n;
        if (!p[id].alive) continue;
        if ((u == 1 && fuck[id]) || (p[id].identity != UN && !zjk(id, u))) {
            target = id; break;
        }
    }
    if (u != 1 && p[1].alive && base[u] == 2) target = 1;
    if (!target) return false;
    if (!p[u].use(F)) return false;
    show(u);
    if (wkr(u, p[target].identity)) {
        int type = 1;
        while (233) {
            int nw = type ? target : u;
            if ((type == 1 && base[target] == 1) || !p[nw].use(K)) {
                damage(target ^ u ^ nw, nw); break;
            }
            type ^= 1;
        }
    } 
    return true;
}

inline bool Invasion(int u) {
    if (!p[u].use(N)) return false;
    for (int i = 1; i < n; i++) {
        int id = u + i;
        if (id > n) id -= n;
        if (!p[id].alive) continue;
        if (wkr(u, p[id].identity)) {
            if (!p[id].use(K)) damage(u, id);
        }
    }
    return true;
}

inline void process(int u) {
    if (!p[u].alive) return;
    for (int i = 1; i <= 2; i++)
        p[u].cards.push_back(pool.front()), pool.pop();
    bool used = false;
    while (233) {
        bool flag = false;
        for (auto t : p[u].cards) {
            if (t == P && p[u].blood < 4) {
                p[u].use(P), p[u].blood++, flag = true; break;
            } 
            if (t == K) {
                if (!p[u].strong && used) continue;
                if (Kill(u)) { flag = true, used = true; break; }
            }
            if (t == F) {
                if (Fight(u)) { flag = true; break; }
            }
            if (t == W) { Arrow(u), flag = true; break; }
            if (t == N) { Invasion(u), flag = true; break; }
            if (t == Z) { Strong(u), flag = true; break; }
        }
        if (!flag) break;
    }   
}

int main() {
//    freopen("P2482_9.in", "r", stdin);
    freopen("7.in", "r", stdin);
//    freopen("out.out", "w", stdout);
    scanf("%d%d", &n, &m); char s[5];
    for (int i = 1; i <= n; i++) {
        scanf("%s", s + 1);
        base[i] = s[1] == 'Z' ? 1 : 2;
        if (s[1] == 'M') base[i] = 0, p[i].identity = ZP;
        for (int j = 1; j <= 4; j++) 
            scanf("%s", s + 1), p[i].cards.push_back(back(s[1]));
    }
    for (int i = 1; i <= m; i++) 
        scanf("%s", s + 1), pool.push(back(s[1]));
    for (int i = 1; i <= 20000; i++) pool.push(back(s[1]));
    for (int i = 1; i; i++) {
        if (i > n) i -= n;
        process(i);
        for (int j = 1; j <= n; j++) {
            printf("%d ", p[j].blood);
            for (auto t : p[j].cards) output(t), putchar(' ');
            puts("");
        }
        puts("-----------------");
    }
}
