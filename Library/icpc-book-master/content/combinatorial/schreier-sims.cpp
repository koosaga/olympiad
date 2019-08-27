/**
 * Author: THU
 * Description: Check group membership of permutation groups
 */
struct Perm {
  int a[N];
  Perm() {
    for (int i = 1; i <= n; ++i) a[i] = i;
  }
  friend Perm operator* (const Perm &lhs, const Perm &rhs) {
    static Perm res;
    for (int i = 1; i <= n; ++i) res.a[i] = lhs.a[rhs.a[i]];
    return res;
  }
  friend Perm inv(const Perm &cur) {
    static Perm res;
    for (int i = 1; i <= n; ++i) res.a[cur.a[i]] = i;
    return res;
  }
};
class Group {
  bool flag[N];
  Perm w[N];
  std::vector<Perm> x;
public:
  void clear(int p) {
    memset(flag, 0, sizeof flag);
    for (int i = 1; i <= n; ++i) w[i] = Perm();
    flag[p] = true;
    x.clear();
  }
  friend bool check(const Perm&, int);
  friend void insert(const Perm&, int);
  friend void updateX(const Perm&, int);
} g[N];
bool check(const Perm &cur, int k) {
  if (!k) return true;
  int t = cur.a[k];
  return g[k].flag[t] ? check(g[k].w[t] * cur, k - 1) : false;
}
void updateX(const Perm&, int);
void insert(const Perm &cur, int k) {
  if (check(cur, k)) return;
  g[k].x.push_back(cur);
  for (int i = 1; i <= n; ++i) if (g[k].flag[i]) updateX(cur * inv(g[k].w[i]), k);
}
void updateX(const Perm &cur, int k) {
  int t = cur.a[k];
  if (g[k].flag[t]) {
    insert(g[k].w[t] * cur, k - 1);
  } else {
    g[k].w[t] = inv(cur);
    g[k].flag[t] = true;
    for (int i = 0; i < g[k].x.size(); ++i) updateX(g[k].x[i] * cur, k);
  }
}
