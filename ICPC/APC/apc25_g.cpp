#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    string s, t;
    int n, m, j = 0, ok = 1;
    cin >> n >> m >> s >> t;
    if (count(all(t), '0') == 0) {
      cout << (count(all(s), '0') == 0 ? "yes" : "no") << "\n";
      continue;
    }
    for (int i = 0; i < m; i++) {
      if (t[i] == '0') {
        while (j < n && s[j] != '0')
          j++;
        if (j == n) {
          ok = 0;
          break;
        }
        j++;
      }
      if (t[i] == '1') {
        int k = i, cons = 0;
        while (k < m && t[k] == '1')
          k++;
        if (k == m) {
          if (j > n - (k - i)) {
            ok = 0;
            break;
          }
          j = n - (k - i);
        }
        while (j < n && cons < k - i) {
          if (s[j] == '0') {
            if (i == 0) {
              ok = 0;
              break;
            }
            cons = 0;
          } else
            cons++;
          j++;
        }
        if (ok == 0)
          break;
        if (cons < k - i) {
          ok = 0;
          break;
        }
        i = k - 1;
      }
    }
    cout << (ok ? "yes" : "no") << "\n";
  }
}