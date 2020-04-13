#include<bits/stdc++.h>

using namespace std;

const int N = 510, max_node = 3e4 + 10;
const double eps = 1e-10, inf = 1e9;

struct point {
  int id;
  double x, y;

  point () {}
  point (double x, double y): x(x), y(y) {}

  point operator + (point a) {
    return point (x + a.x, y + a.y);
  }

  point operator - (point a) {
    return point (x - a.x, y - a.y);
  }

  point operator * (double a) {
    return point (x * a, y * a);
  }

  point operator / (double a) {
    return point (x / a, y / a);
  }

  bool operator == (const point& a) const {
    return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
  }

  bool operator != (const point& a) const {
    return !(*this == a);
  }
} points[N], point_q[N << 1];

double dot(point a, point b) {
  return a.x * b.x + a.y * b.y;
}

double cross(point a, point b) {
  return a.x * b.y - a.y * b.x;
}

double dist(point a, point b) {
  return sqrt(dot(a - b, a - b));
}

point rotate(point a, double rad) {
  return point (a.x * cos(rad) - a.y * sin(rad), a.x * sin(rad) + a.y * cos(rad));
}       

bool on_segment(point p, point a, point b) {
  double d = dist(a, b);
  return dist(a, p) <= d && dist(b, p) <= d;
}

struct circle {
  point center;
  double r;

  circle () {}
  circle (point center, double r): center(center), r(r) {}
} stone[N];

struct line {
  int id;
  point p, v;
  double angle;

  line () {}
  line (point p, point v, int id): p(p), v(v), id(id) {
    angle = atan2(v.y, v.x);
  }

  bool operator < (const line& a) const {
    return angle < a.angle;
  }
} line_q[N << 1];

int n, m, days, cost, type[N];
double p0, all_dist;
vector<pair<point, point>> control[N][N];

point line_intersection(line a, line b) {
  if (fabs(cross(a.v, b.v)) > eps) {
    double t = cross(b.v, a.p - b.p) / cross(a.v, b.v);
    return a.p + a.v * t;
  } else {
    return point (inf, inf);
  }
}

bool on_left(point p, line x) {
  return cross(x.v, p - x.p) > 0;
}

vector<line> half_plane_intersection(vector<line>& s) {
  sort(s.begin(), s.end());
  int first = 0, last = 0;
  line_q[0] = s[0];
  for (int i = 1; i < s.size(); ++i) {
    for (; first < last && !on_left(point_q[last - 1], s[i]); --last);
    for (; first < last && !on_left(point_q[first], s[i]); ++first);
    line_q[++last] = s[i];
    if (first < last && fabs(cross(line_q[last].v, line_q[last - 1].v)) < eps) {
      --last;
      if (on_left(s[i].p, line_q[last])) {
        line_q[last] = s[i];
      }
    }
    if (first < last) {
      point_q[last - 1] = line_intersection(line_q[last - 1], line_q[last]);
    }
  }
  for (; first < last && !on_left(point_q[last - 1], line_q[first]); --last);
  vector<line> result;
  for (int i = first; i <= last; ++i) {
    result.push_back(line_q[i]);
  }
  return result;
}

struct edge {
  int to;
  double refer, cap, flow;

  edge () {}
  edge (int to, double refer): to(to), refer(refer) {}
};

vector<edge> edges;
vector<int> graph[max_node];
int s, t, node_cnt, stone_id[N], cur[max_node], dis[max_node];
double dinic_flow;

void add_edge(int u, int v, double cap) {
  edges.emplace_back(v, cap);
  edges.emplace_back(u, 0);
  graph[u].push_back(edges.size() - 2);
  graph[v].push_back(edges.size() - 1);
}

bool bfs() {
  queue<int> que;
  memset(dis, 0, sizeof dis);
  memset(cur, 0, sizeof cur);
  que.push(s);
  dis[s] = 1;
  while (!que.empty()) {
    int x = que.front();
    que.pop();
    for (auto v : graph[x]) {
      edge& e = edges[v];
      if (e.cap - e.flow > eps && !dis[e.to]) {
        dis[e.to] = dis[x] + 1;
        que.push(e.to);
      }
    }
  }
  return dis[t] > 0;
}

double dfs(int u, double a) {
  if (u == t || a < eps) {
    return a;
  } else {
    double flow = 0, f;
    for (int& i = cur[u]; i < graph[u].size(); ++i) {
      edge& e = edges[graph[u][i]];
      if (dis[e.to] == dis[u] + 1 && (f = dfs(e.to, min(a, e.cap - e.flow))) > eps) {
        e.flow += f;
        edges[graph[u][i] ^ 1].flow -= f;
        flow += f;
        a -= f;
        if (a < eps) {
          break;
        }
      }
    }
    return flow;
  }
}

double dinic() {
  for (; bfs(); dinic_flow -= dfs(s, inf));
  return dinic_flow;
}

struct state {
  int p_id, stone_id;
  double d;
  point p;

  state () {}
  state (int p_id, int stone_id, double d, point p): p_id(p_id), stone_id(stone_id), d(d), p(p) {}

  bool operator < (const state& a) const {
    return p_id == a.p_id ? d < a.d : p_id < a.p_id;
  }
};

vector<state> cover[N];
bool appeared[N];

void add_edge(int i, int j, point a, point b) {
  if (control[i][j].size()) {
    point p = control[i][j][0].first;
    point q = control[i][j][0].second;
    double dist0 = dist(points[j], p);
    double dist1 = dist(points[j], a);
    double dist2 = dist(points[j], q);
    double dist3 = dist(points[j], b);
    if (max(dist0, dist1) <= min(dist2, dist3)) {
      point l = dist0 > dist1 ? p : a;
      point r = dist2 < dist3 ? q : b;
      ++node_cnt;
      double d = dist(l, r) / all_dist;
      p0 -= d;
      add_edge(s, node_cnt, d * days);
      dinic_flow += d * days;
      for (int k = 1; k <= m; ++k) {
        if (appeared[k]) {
          add_edge(node_cnt, stone_id[k], inf);
        }
      }
    }
  }
}

void add_edge() {
  s = ++node_cnt;
  t = ++node_cnt;
  for (int i = 1; i <= m; ++i) {
    stone_id[i] = ++node_cnt;
    add_edge(stone_id[i], t, -cost);
  }
  for (int i = 1; i <= n; ++i) {
    if (type[i]) {
      memset(appeared, false, sizeof appeared);
      for (int j = 0, k, last = -1; j < cover[i].size(); j = k) {
        if (~last) {
          for (int l = last == n ? 1 : last + 1; l != cover[i][j].p_id; l = l == n ? 1 : l + 1) {
            add_edge(i, l, points[l], points[l == n ? 1 : l + 1]);
          }
        }
        for (k = j; k < cover[i].size() && cover[i][j].p_id == cover[i][k].p_id; ++k);
        last = cover[i][j].p_id;
        add_edge(i, last, points[last], cover[i][j].p);
        for (int l = j; l < k; ++l) {
          int u = cover[i][l].stone_id;
          if (!appeared[u]) {
            appeared[u] = true;
          } else {
            appeared[u] = false;
          }
          if (l + 1 < k) {
            add_edge(i, last, cover[i][l].p, cover[i][l + 1].p);
          }
        }
        add_edge(i, last, cover[i][k - 1].p, points[last == n ? 1 : last + 1]);
      }
    }
  }
}

bool check(double answer) {
  dinic_flow = 0;
  for (auto& v : edges) {
    v.flow = 0;
    if (v.refer >= 0) {
      v.cap = v.refer;
      if (v.refer < inf) {
        dinic_flow += v.refer;
      }
    } else {
      v.cap = -answer * v.refer;
    }
  }
  return (p0 - answer) * days + dinic() >= 0;
}

int main() {
  scanf("%d%d%d%d", &n, &m, &days, &cost);
  for (int i = 1; i <= n; ++i) {
    scanf("%lf%lf%d", &points[i].x, &points[i].y, &type[i]);
  }
  for (int i = 1; i <= n; ++i) {
    if (type[i]) {
      vector<line> half_plane;
      for (int j = 1; j <= n; ++j) {
        int k = j == n ? 1 : j + 1;
        half_plane.emplace_back(points[j], points[k] - points[j], j);
        if (i != j) {
          point mid = point ((points[i].x + points[j].x) / 2, (points[i].y + points[j].y) / 2);
          point v = point (points[j].y - points[i].y, points[i].x - points[j].x);
          half_plane.emplace_back(mid, v, -1);
        }
      }
      vector<line> convex_hull = half_plane_intersection(half_plane);
      if (convex_hull.size() > 2) {
        for (int j = 0; j < convex_hull.size(); ++j) {
          if (~convex_hull[j].id) {
            int l = j == 0 ? convex_hull.size() - 1 : j - 1;
            int r = j + 1 == convex_hull.size() ? 0 : j + 1;
            point a = line_intersection(convex_hull[l], convex_hull[j]);
            point b = line_intersection(convex_hull[j], convex_hull[r]);
            p0 += dist(a, b);
            control[i][convex_hull[j].id].emplace_back(a, b);
          }
        }
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    int j = i == n ? 1 : i + 1;
    all_dist += dist(points[i], points[j]);
  }
  p0 /= all_dist;
  for (int i = 1; i <= m; ++i) {
    scanf("%lf%lf%lf", &stone[i].center.x, &stone[i].center.y, &stone[i].r);
  }
  for (int i = 1; i <= n; ++i) {
    if (type[i]) {
      for (int j = 1; j <= m; ++j) {
        point v = stone[j].center - points[i];
        double angle = asin(stone[j].r / dist(points[i], stone[j].center));
        line a = line (points[i], rotate(v, angle), -1);
        line b = line (points[i], rotate(v, -angle), -1);
        for (int k = 1; k <= n; ++k) {
          int p = k == n ? 1 : k + 1;
          point intersection = line_intersection(line(points[k], points[p] - points[k], -1), a);
          if (intersection != points[i] && on_segment(intersection, points[k], points[p])) {
            cover[i].emplace_back(k < i ? k + n : k, j, dist(points[k], intersection), intersection);
          }
          intersection = line_intersection(line(points[k], points[p] - points[k], -1), b);
          if (intersection != points[i] && on_segment(intersection, points[k], points[p])) {
            cover[i].emplace_back(k < i ? k + n : k, j, dist(points[k], intersection), intersection);
          }
        }
      }
      sort(cover[i].begin(), cover[i].end());
      for (auto& v : cover[i]) {
        if (v.p_id > n) {
          v.p_id -= n;
        }
      }
    }
  }
  add_edge();
  double l = 0, r = 1;
  while (r - l > 1e-5) {
    double mid = (l + r) / 2;
    if (check(mid)) {
      l = mid;
    } else {
      r = mid;
    }
  }
  printf("%.4lf\n", l);
  return 0;
}