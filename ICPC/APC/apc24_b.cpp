#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = array<int, 2>;
using llf = long double;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
    }
    vector<vector<pi>> gph(n);
    int ans = 0;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        ans = max(ans, w);
        gph[u].push_back({v, w});
        gph[v].push_back({u, w});
    }
    priority_queue<pi, vector<pi>, greater<pi>> pq;
    vector<int> deg(n), marked(n);
    for (int i = 0; i < n; i++) {
        sort(all(gph[i]));
        deg[i] = sz(gph[i]);
        pq.push({deg[i], i});
    }
    auto hasEdge = [&](int u, int v) {
        auto l = lower_bound(all(gph[u]), pi{v, -1});
        if (l != gph[u].end() && (*l)[0] == v) {
            return (*l)[1];
        }
        return -1;
    };
    int D[6][6] = {};
    vector<vector<int>> trips, quads;
    while (sz(pq)) {
        auto x = pq.top()[1];
        pq.pop();
        if (marked[x])
            continue;
        marked[x] = 1;
        vector<pi> adjs;
        for (auto &[y, w] : gph[x]) {
            if (!marked[y]) {
                deg[y]--;
                pq.push({deg[y], y});
                adjs.push_back({y, w});
            }
        }
        assert(sz(adjs) <= 5);
        for (int i = 1; i < (1 << sz(adjs)); i++) {
            vector<int> subs = {x};
            for (int j = 0; j < sz(adjs); j++) {
                if ((i >> j) & 1) {
                    D[0][sz(subs)] = D[sz(subs)][0] = adjs[j][1];
                    subs.push_back(adjs[j][0]);
                }
            }
            if (sz(subs) <= 2 || sz(subs) >= 5)
                continue;
            bool bad = 0;
            for (int i = 1; i < sz(subs); i++) {
                for (int j = 1; j < i; j++) {
                    D[i][j] = D[j][i] = hasEdge(subs[i], subs[j]);
                    if (D[i][j] == -1)
                        bad = 1;
                }
            }
            if (bad)
                continue;
            int csum = 0;
            for (int i = 0; i < sz(subs); i++) {
                for (int j = 0; j < i; j++) {
                    csum += D[i][j];
                }
            }
            ans = max(ans, csum);
            if (sz(subs) == 3) {
                for (int j = 0; j < sz(subs); j++) {
                    vector<int> foo;
                    int sum = 0;
                    for (int k = 0; k < sz(subs); k++) {
                        if (j == k)
                            continue;
                        foo.push_back(subs[k]);
                        sum += D[j][k];
                    }
                    sort(all(foo));
                    foo.push_back(csum - sum);
                    foo.push_back(sum);
                    trips.push_back(foo);
                }
            }
            if (sz(subs) == 4) {
                for (int j = 0; j < sz(subs); j++) {
                    vector<int> foo;
                    int sum = 0;
                    for (int k = 0; k < sz(subs); k++) {
                        if (j == k)
                            continue;
                        foo.push_back(subs[k]);
                        sum += D[j][k];
                    }
                    sort(all(foo));
                    foo.push_back(csum - sum);
                    foo.push_back(sum);
                    quads.push_back(foo);
                }
            }
        }
    }
    auto match = [&](vector<int> &a, vector<int> &b, int t) {
        for (int i = 0; i < t; i++) {
            if (a[i] != b[i])
                return false;
        }
        return true;
    };
    sort(all(trips));
    sort(all(quads));
    for (int i = 0; i < sz(trips);) {
        int j = i;
        while (j < sz(trips) && match(trips[i], trips[j], 2))
            j++;
        if (j - i >= 2) {
            ans = max(ans, trips[j - 1][3] + trips[j - 2][3] + trips[j - 2][2] - int(1e6));
        }
        i = j;
    }
    for (int i = 0; i < sz(quads);) {
        int j = i;
        while (j < sz(quads) && match(quads[i], quads[j], 3))
            j++;
        if (j - i >= 2) {
            ans = max(ans, quads[j - 1][4] + quads[j - 2][4] + quads[j - 2][3] - int(1e6));
        }
        i = j;
    }
    cout << ans << "\n";
}