#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 161616, MAXM = 161616;

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

struct bpm {
    vector<int> gph[MAXN];
    int dis[MAXN], l[MAXN], r[MAXM], vis[MAXN];
    void clear() {
        for (int i = 0; i < MAXN; i++)
            gph[i].clear();
    }
    void add_edge(int l, int r) { gph[l].push_back(r); }
    bool bfs(int n) {
        queue<int> que;
        bool ok = 0;
        memset(dis, 0, sizeof(dis));
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
        memset(l, -1, sizeof(l));
        memset(r, -1, sizeof(r));
        int ret = 0;
        while (bfs(n)) {
            memset(vis, 0, sizeof(vis));
            for (int i = 0; i < n; i++)
                if (l[i] == -1 && dfs(i))
                    ret++;
        }
        return ret;
    }
    bool chk[MAXN + MAXM];
    void rdfs(int x, int n) {
        if (chk[x])
            return;
        chk[x] = 1;
        for (auto &i : gph[x]) {
            chk[i + n] = 1;
            rdfs(r[i], n);
        }
    }
    vector<int> getcover(int n, int m) { // solve min. vertex cover
        match(n);
        memset(chk, 0, sizeof(chk));
        for (int i = 0; i < n; i++)
            if (l[i] == -1)
                rdfs(i, n);
        vector<int> v;
        for (int i = 0; i < n; i++)
            if (!chk[i])
                v.push_back(i);
        for (int i = n; i < n + m; i++)
            if (chk[i])
                v.push_back(i);
        return v;
    }
} bpm;

int vis[MAXN], par[MAXN];
vector<int> gph[MAXN];

void dfs(int x) {
    if (vis[x])
        return;
    vis[x] = 1;
    for (auto &y : gph[x]) {
        if (!vis[y]) {
            par[y] = x;
            dfs(y);
        }
    }
}

pair<bool, vector<pi>> solve(vector<int> v0, vector<int> v1, vector<pi> edges, int Z) {
    for (int i = 0; i < MAXN; i++) {
        gph[i].clear();
        vis[i] = par[i] = 0;
    }
    if (sz(v0) == sz(v1))
        return make_pair(false, vector<pi>());
    if (sz(v0) > sz(v1)) {
        for (auto &[x, y] : edges)
            swap(x, y);
        auto ret = solve(v1, v0, edges, Z);
        for (auto &[x, y] : ret.second)
            swap(x, y);
        return ret;
    }
    for (auto &[u, v] : edges) {
        bpm.add_edge(u, v);
    }
    int ret = bpm.match(Z);
    if (ret != sz(v0))
        return make_pair(false, vector<pi>());
    for (auto &[u, v] : edges) {
        if (bpm.l[u] == v) {
            gph[u].push_back(v);
        } else
            gph[v].push_back(u);
    }
    for (auto &x : v1) {
        if (!vis[x] && bpm.r[x] == -1)
            dfs(x);
    }
    for (auto &x : v0) {
        if (!vis[x])
            return make_pair(false, vector<pi>());
    }
    for (auto &x : v1) {
        if (!vis[x])
            return make_pair(false, vector<pi>());
    }
    vector<pi> consists;
    for (auto &u : v0) {
        consists.push_back({u, bpm.l[u]});
        consists.push_back({u, par[u]});
    }
    dsu.init(Z);
    int ans = sz(v0) + sz(v1) - 1;
    for (auto &[u, v] : consists) {
        assert(dsu.uni(u, v));
        ans--;
    }
    for (auto &[u, v] : edges) {
        if (dsu.uni(u, v))
            consists.push_back({u, v}), ans--;
    }
    if (ans == 0)
        return make_pair(true, consists);
    return make_pair(false, vector<pi>());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<string> a(2 * n + 1);
    for (auto &x : a)
        cin >> x;
    vector<pi> edges;
    auto g = [&](int x, int y) { return x * m + y; };
    auto addEdge = [&](int u1, int v1, int u2, int v2) {
        if ((u1 + v1) % 2)
            swap(u1, u2), swap(v1, v2);
        edges.push_back({g(u1, v1), g(u2, v2)});
    };
    vector<int> verts[2];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[2 * i + 1][2 * j + 2] == '.') {
                addEdge(i, j, i, j + 1);
            }
            if (a[2 * i + 2][2 * j + 1] == '.') {
                addEdge(i, j, i + 1, j);
            }
            if (a[2 * i + 1][2 * j + 1] == '.') {
                verts[(i + j) % 2].push_back(g(i, j));
            }
        }
    }
    auto [ok, edgs] = solve(verts[0], verts[1], edges, n * m);
    if (!ok) {
        cout << "No\n";
        return 0;
    }
    cout << "Yes\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[2 * i + 1][2 * j + 2] == '.') {
                a[2 * i + 1][2 * j + 2] = '#';
            }
            if (a[2 * i + 2][2 * j + 1] == '.') {
                a[2 * i + 2][2 * j + 1] = '#';
            }
        }
    }
    for (auto &[u, v] : edgs) {
        int u1 = u / m, v1 = u % m;
        int u2 = v / m, v2 = v % m;
        a[u1 + u2 + 1][v1 + v2 + 1] = '.';
    }
    for (auto &x : a)
        cout << x << "\n";
}