#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    vector<array<int, 26>> rowds(n), colds(m);
    int rcnt = m, ccnt = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            rowds[i][a[i][j] - 'A']++;
            colds[j][a[i][j] - 'A']++;
        }
    }
    vector<int> visR(n), visC(m);
    vector<array<int, 3>> ans;
    while (rcnt > 0 && ccnt > 0) {
        bool ok = 0;
        for (int j = 0; j < n; j++) {
            if (!visR[j] && *max_element(all(rowds[j])) == rcnt) {
                visR[j] = 1;
                ok = 1;
                for (int k = 0; k < 26; k++) {
                    if (rowds[j][k] == rcnt) {
                        ans.push_back({0, j, k});
                        break;
                    }
                }
                for (int k = 0; k < m; k++) {
                    rowds[j][a[j][k] - 'A']--;
                    colds[k][a[j][k] - 'A']--;
                }
                ccnt--;
                break;
            }
        }
        if (ok)
            continue;
        for (int j = 0; j < m; j++) {
            if (!visC[j] && *max_element(all(colds[j])) == ccnt) {
                // ok, eliminate j
                visC[j] = 1;
                ok = 1;
                for (int k = 0; k < 26; k++) {
                    if (colds[j][k] == ccnt) {
                        ans.push_back({1, j, k});
                        break;
                    }
                }
                for (int k = 0; k < n; k++) {
                    rowds[k][a[k][j] - 'A']--;
                    colds[j][a[k][j] - 'A']--;
                }
                rcnt--;
                break;
            }
        }
        if (ok)
            continue;
        assert(0);
    }
    reverse(all(ans));
    cout << sz(ans) << "\n";
    for (auto &[x, y, z] : ans) {
        cout << "RK"[x] << " " << y + 1 << " " << (char)('A' + z) << "\n";
    }
}