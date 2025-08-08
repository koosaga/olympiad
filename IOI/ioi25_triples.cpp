#include "triples.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

lint count_triples(vector<int> H) {
  int n = sz(H);
  set<array<int, 3>> S;
  auto go = [&](int a, int b, int c) {
    if (a >= n)
      return;
    vector<int> cb, cc;
    if (b == -1) {
      if (c < n)
        cb.push_back(c - H[c]);
      cb.push_back(c - H[a]);
      cb.push_back(a + H[a]);
      if (c < n)
        cb.push_back(a + H[c]);
    } else
      cb.push_back(b);
    if (c == -1) {
      if (b < n)
        cc.push_back(b + H[b]);
      cc.push_back(b + H[a]);
      cc.push_back(a + H[a]);
      if (b < n)
        cc.push_back(a + H[b]);
    } else
      cc.push_back(c);
    int i = a;
    for (auto &j : cb) {
      for (auto &k : cc) {
        if (j >= n || k >= n || !(i < j && j < k)) {
          continue;
        }
        if (H[k] == j - i && H[j] == k - i && H[i] == k - j)
          continue;
        vector<int> p = {j - i, k - i, k - j};
        vector<int> q = {H[i], H[j], H[k]};
        sort(all(p));
        sort(all(q));
        if (p == q)
          S.insert({i, j, k});
      }
    }
  };
  for (int i = 0; i < n; i++) {
    go(i, -1, i + H[i]);
    go(i, i + H[i], -1);
    if (i - H[i] >= 0)
      go(i - H[i], i, -1);
  }
  vector<vector<int>> in(n), out(n);
  for (int i = 0; i < n; i++) {
    if (i + H[i] < n)
      in[i + H[i]].push_back(i);
    if (i - H[i] >= 0)
      out[i - H[i]].push_back(i);
  }
  lint ans = sz(S);
  for (int i = 0; i < n; i++) {
    if (1ll * sz(in[i]) * sz(out[i]) <= n) {
      for (auto &a : in[i]) {
        for (auto &c : out[i]) {
          int b = a + c - i;
          if (H[c] == b - a && H[b] == c - a && H[a] == c - b)
            ans++;
        }
      }
    } else {
      for (int b = 0; b < n; b++) {
        int p = b + i, q = H[b];
        if (p % 2 == q % 2 && p >= q && p + q <= 2 * n - 2) {
          int a = (p - q) / 2, c = (p + q) / 2;
          if (H[c] == b - a && H[b] == c - a && H[a] == c - b)
            ans++;
        }
      }
    }
  }
  return ans;
}

vector<int> construct_range(int M, int K) {
  vector<int> opt;
  lint cur = 0;
  vector<int> x;
  for (int i = -M / 8; i < M + M / 8; i++) {
    if (i % 2 == 0)
      x.push_back(i);
  }
  for (int i = 0; cur < K; i++) {
    auto rng = mt19937(0x1557 + i);
    shuffle(all(x), rng);
    vector<int> h(M);
    int tol = (int)(sqrt(M) * 4);
    for (int i = 0; i < sz(x) && i < tol; i++) {
      for (int j = 0; j < i; j++) {
        int L = (x[i] + x[j]) / 2;
        if (L < 0 || L >= M)
          continue;
        int R = abs(x[j] - x[i]) / 2;
        R = min(R, M - 1);
        if (!h[L])
          h[L] = R;
      }
    }
    for (auto &v : h)
      if (v == 0)
        v = 1;

    lint ans = count_triples(h);
    if (ans > cur) {
      cur = ans;
      opt = h;
      cerr << cur << endl;
    }
  }
  return opt;
}
