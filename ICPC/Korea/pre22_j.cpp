#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

lint count_rectangles(vector<vector<int>> gph) {
    int n = sz(gph);
    vector<int> idx(n);
    iota(all(idx), 0);
    sort(all(idx), [&](int p, int q) { return sz(gph[p]) > sz(gph[q]); });
    vector<int> chk(n);
    lint ret = 0;
    for (int i = 0; i < min(500, n); i++) {
        for (auto &j : gph[idx[i]]) {
            chk[j] = 1;
        }
        for (int j = i + 1; j < n; j++) {
            int cnt = 0;
            for (auto &j : gph[idx[j]]) {
                if (chk[j])
                    cnt++;
            }
            ret += cnt * (cnt - 1) / 2;
        }
        for (auto &j : gph[idx[i]]) {
            chk[j] = 0;
        }
    }
    unordered_map<lint, int> counts;
    for (int i = 500; i < n; i++) {
        sort(all(gph[idx[i]]));
        for (int j = 0; j < sz(gph[idx[i]]); j++) {
            for (int k = 0; k < j; k++) {
                lint foo = 1ll * gph[idx[i]][k] * n + gph[idx[i]][j];
                ret += counts[foo];
                counts[foo]++;
            }
        }
    }
    assert(ret % 2 == 0);
    return ret / 2;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.precision(69);
    int n;
    cin >> n;
    vector<pi> v(n);
    for (auto &[x, y] : v)
        cin >> x >> y;
    vector<int> vx, vy;
    for (auto &[x, y] : v) {
        vx.push_back(x);
        vy.push_back(y);
    }
    sort(all(vx));
    sort(all(vy));
    vx.resize(unique(all(vx)) - vx.begin());
    vy.resize(unique(all(vy)) - vy.begin());
    n = sz(vx) + sz(vy);
    vector<vector<int>> gph(n);
    for (auto &[x, y] : v) {
        x = lower_bound(all(vx), x) - vx.begin();
        y = lower_bound(all(vy), y) - vy.begin();
        gph[x].push_back(sz(vx) + y);
        gph[sz(vx) + y].push_back(x);
    }
    cout << count_rectangles(gph) << "\n";
}