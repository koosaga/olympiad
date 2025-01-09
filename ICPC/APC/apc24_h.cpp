/**
 *    author:  tourist
 *    created: 01.03.2024 21:44:16
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
  int n;
  cin >> n;
  const int inf = int(1e9);
  vector<int> dp(4, inf);
  dp[0] = 0;
  vector<int> total(2);
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    vector<int> cnt(2);
    for (char c : s) {
      cnt[int(c - '0')] += 1;
    }
    total[0] += cnt[0];
    total[1] += cnt[1];
    vector<int> new_dp(4, inf);
    for (int t = 0; t < 4; t++) {
      for (int j = 0; j < 2; j++) {
        new_dp[t | (1 << j)] = min(new_dp[t | (1 << j)], dp[t] + cnt[j]);
      }
    }
    swap(dp, new_dp);
  }
  cout << (min(total[0], total[1]) == 0 ? 0 : dp[3]) << '\n';
  return 0;
}
