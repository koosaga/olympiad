/**
 *    author:  tourist
 *    created: 01.03.2024 22:00:59
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
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    vector<vector<vector<int>>> at(m, vector<vector<int>>(26));
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            if (s[i][j] != '.') {
                at[j][int(s[i][j] - 'A')].push_back(i);
            }
        }
    }
    int low = n;
    vector<vector<int>> f(n + 1, vector<int>(n + 1));
    for (int j = 0; j < m; j++) {
        for (int c = 0; c < 26; c++) {
            auto &v = at[j][c];
            for (int it = 0; it < int(v.size()); it++) {
                if (v[it] > low) {
                    break;
                }
                for (int jt = 0; jt < it; jt++) {
                    f[v[it]][v[jt]] += 1;
                    if (f[v[it]][v[jt]] >= k) {
                        low = min(low, v[it]);
                        break;
                    }
                }
            }
        }
    }
    if (low == n) {
        cout << -1 << '\n';
    } else {
        for (int i = low - 1; i >= 0; i--) {
            int cnt = 0;
            for (int j = 0; j < m; j++) {
                cnt += (s[i][j] == s[low][j] && s[i][j] != '.');
            }
            if (cnt >= k) {
                cout << i + 1 << " " << low + 1 << '\n';
                return 0;
            }
        }
        assert(false);
    }
    return 0;
}
