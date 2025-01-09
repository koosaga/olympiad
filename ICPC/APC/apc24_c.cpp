/**
 *    author:  tourist
 *    created: 01.03.2024 21:47:32
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    if (n == 1) {
      cout << (int64_t(1) << a[0]) - 1 << '\n';
      continue;
    }
    int at = 0;
    int md = 123;
    for (int i = 0; i < n - 1; i++) {
      if (a[i + 1] - a[i] < md) {
        md = a[i + 1] - a[i];
        at = i;
      }
    }
    if (md >= 2) {
      cout << -1 << '\n';
      continue;
    }
    auto dv = int64_t(1) << (1 - md);
    auto x = dv * ((int64_t(1) << a[at + 1]) - 1) - at - 1;
    if (x < 0) {
      cout << -1 << '\n';
      continue;
    }
    bool ok = true;
    for (int i = 0; i < n; i++) {
      ok &= (__builtin_popcountll(x + i) == a[i]);
    }
    cout << (ok ? x : -1) << '\n';
  }
  return 0;
}
