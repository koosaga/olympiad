/**
 *    author:  tourist
 *    created: 01.03.2024 22:11:00
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

template <typename T>
class fenwick {
 public:
  vector<T> fenw;
  int n;

  fenwick(int _n) : n(_n) {
    fenw.resize(n);
  }

  void modify(int x, T v) {
    while (x < n) {
      fenw[x] += v;
      x |= (x + 1);
    }
  }

  T get(int x) {
    T v{};
    while (x >= 0) {
      v += fenw[x];
      x = (x & (x + 1)) - 1;
    }
    return v;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, q;
  cin >> n >> q;
  vector<int> p(n);
  vector<vector<int>> g(n);
  int root = -1;
  for (int i = 0; i < n; i++) {
    cin >> p[i];
    --p[i];
    if (p[i] == -1) {
      assert(root == -1);
      root = i;
    } else {
      g[p[i]].push_back(i);
    }
  }
  vector<int64_t> qs(q);
  vector<int> x(q);
  vector<int> cc(q);
  for (int i = 0; i < q; i++) {
    cin >> qs[i];
    --qs[i];
    x[i] = int(qs[i] / n);
    cc[i] = int(qs[i] % n);
  }
  assert(root != -1);
  vector<int> order;
  vector<int> pos(n, -1);
  vector<int> end(n, -1);
  vector<int> sz(n);
  vector<int> depth(n);
  auto Dfs = [&](auto&& self, int v) -> void {
    pos[v] = int(order.size());
    order.push_back(v);
    sz[v] = 1;
    for (int u : g[v]) {
      depth[u] = depth[v] + 1;
      self(self, u);
      sz[v] += sz[u];
    }
    end[v] = int(order.size());
  };
  Dfs(Dfs, root);
  const int LOG = 20;
  vector<vector<int>> jump(n, vector<int>(LOG));
  for (int i = 0; i < n; i++) {
    jump[i][0] = (p[i] == -1 ? i : p[i]);
  }
  for (int j = 1; j < LOG; j++) {
    for (int i = 0; i < n; i++) {
      jump[i][j] = jump[jump[i][j - 1]][j - 1];
    }
  }
  vector<int> sub(q, 0);
  vector<int> low(q, 0), high(q, n - 1);
  while (true) {
    vector<int> mid(q);
    vector<vector<int>> at(n);
    bool any = false;
    for (int i = 0; i < q; i++) {
      if (low[i] < high[i]) {
        any = true;
        mid[i] = (low[i] + high[i]) >> 1;
        at[mid[i]].push_back(i);
      }
    }
    if (!any) {
      break;
    }
    fenwick<int> fenw(n);
    for (int i = 0; i < n; i++) {
      fenw.modify(pos[i], +sz[i]);
      fenw.modify(end[i], -sz[i]);
      for (int j : g[i]) {
        fenw.modify(pos[j], -sz[j]);
        fenw.modify(end[j], +sz[j]);
      }
      for (int qid : at[i]) {
        auto num = fenw.get(pos[x[qid]]);
        if (num > cc[qid]) {
          high[qid] = mid[qid];
        } else {
          sub[qid] = num;
          low[qid] = mid[qid] + 1;
        }
      }
    }
  }
  auto lca = low;
  low.assign(q, 0);
  high.assign(q, n - 1);
  while (true) {
    vector<int> mid(q);
    vector<vector<int>> at(n);
    bool any = false;
    for (int i = 0; i < q; i++) {
      if (low[i] < high[i]) {
        any = true;
        mid[i] = (low[i] + high[i]) >> 1;
        at[mid[i]].push_back(i);
      }
    }
    if (!any) {
      break;
    }
    fenwick<int> fenw(n);
    for (int i = 0; i < n; i++) {
      fenw.modify(pos[i], +1);
      for (int qid : at[i]) {
        int cnt = fenw.get(end[lca[qid]] - 1) - fenw.get(pos[lca[qid]] - 1);
        if (lca[qid] != x[qid]) {
          int h = depth[x[qid]] - depth[lca[qid]] - 1;
          int v = x[qid];
          for (int j = 0; j < LOG; j++) {
            if (h & (1 << j)) {
              v = jump[v][j];
            }
          }
          cnt -= fenw.get(end[v] - 1) - fenw.get(pos[v] - 1);
        }
        if (cnt > cc[qid] - sub[qid]) {
          high[qid] = mid[qid];
        } else {
          low[qid] = mid[qid] + 1;
        }
      }
    }
  }
  for (int i = 0; i < q; i++) {
    cout << int64_t(x[i]) * n * n + int64_t(lca[i]) * n + low[i] << '\n';
  }
  return 0;
}
