#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005, MAXM = 100005;

struct bpm {
    vector<int> gph[MAXN];
    int dis[MAXN], l[MAXN], r[MAXM], vis[MAXN];
    void clear(int n) {
        for (int i = 0; i < n; i++)
            gph[i].clear();
    }
    void add_edge(int l, int r) { gph[l].push_back(r); }
    bool bfs(int n) {
        queue<int> que;
        bool ok = 0;
        memset(dis, 0, sizeof(int) * n);
        for (int i = 0; i < n; i++) {
            if (l[i] == -1 && !dis[i]) {
                que.push(i);
                dis[i] = 1;
            }
        }
        while (!que.empty()) {
            int x = que.front();
            que.pop();
            for (auto &i : gph[x]) {
                if (r[i] == -1)
                    ok = 1;
                else if (!dis[r[i]]) {
                    dis[r[i]] = dis[x] + 1;
                    que.push(r[i]);
                }
            }
        }
        return ok;
    }
    bool dfs(int x) {
        if (vis[x])
            return 0;
        vis[x] = 1;
        for (auto &i : gph[x]) {
            if (r[i] == -1 || (!vis[r[i]] && dis[r[i]] == dis[x] + 1 && dfs(r[i]))) {
                l[x] = i;
                r[i] = x;
                return 1;
            }
        }
        return 0;
    }
    int match(int n) {
        memset(l, -1, sizeof(int) * n);
        memset(r, -1, sizeof(int) * n);
        int ret = 0;
        while (bfs(n)) {
            memset(vis, 0, sizeof(int) * n);
            for (int i = 0; i < n; i++)
                if (l[i] == -1 && dfs(i))
                    ret++;
        }
        return ret;
    }
} bpm;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.precision(69);
    int n, k;
    cin >> n >> k;
    if (k == 1) {
        cout << "YES\n" << n * (n - 1) / 2 << "\n";
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                cout << i << " " << j << "\n";
            }
        }
        return 0;
    }
    if (k == n) {
        cout << "NO\n";
        return 0;
    }
    assert(k + 1 >= 3 && n >= 3);
    cout << "YES\n";
    vector<pi> edges;
    vector<int> deg = {1, 1, 2};
    edges.push_back({0, 2});
    edges.push_back({1, 2});
    for (int i = 4; i <= k + 1; i++) {
        vector<int> idx(i - 1);
        iota(all(idx), 0);
        sort(all(idx), [&](int a, int b) { return deg[a] < deg[b]; });
        deg.push_back(0);
        for (int j = 0; j < i - 2; j++) {
            if (deg[idx[j]] == deg[idx[j + 1]]) {
                for (int k = j + 1; k < i - 1; k++) {
                    edges.push_back({i - 1, idx[k]});
                    deg[idx[k]]++;
                    deg[i - 1]++;
                }
                break;
            }
        }
    }
    int prv = 0;
    for (int i = 0; i < sz(deg); i++)
        if (deg[i] == 1)
            prv = i;
    for (int i = k + 2; i <= n; i++)
        edges.push_back({prv, i - 1}), prv = i - 1;
    cout << sz(edges) << "\n";
    for (auto &[p, q] : edges)
        cout << p + 1 << " " << q + 1 << "\n";
}