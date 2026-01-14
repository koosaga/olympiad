#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
struct disj {
  vector<int> pa;
  void init(int n) {
    pa.clear();
    pa.resize(n);
    iota(all(pa), 0);
  }
  int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
  bool uni(int p, int q) {
    p = find(p);
    q = find(q);
    if (p == q)
      return 0;
    pa[q] = p;
    return 1;
  }
} dsu;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, m;
  cin >> n >> m;
  dsu.init(2 * n);
  int cut = 0;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    if (dsu.find(u) == dsu.find(v))
      continue;
    dsu.uni(u, v + n);
    dsu.uni(u + n, v);
    cut++;
  }
  cout << cut + 1 << "\n";
}