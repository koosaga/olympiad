#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 1000005;
const int MAXM = 1000005;

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

} bpm;

struct strongly_connected {
    vector<vector<int>> gph;

    void init(int n) {
        gph.clear();
        gph.resize(n);
    }

    void add_edge(int s, int e) { gph[s].push_back(e); }

    vector<int> val, comp, z, cont;
    int Time, ncomps;
    template <class G, class F> int dfs(int j, G &g, F f) {
        int low = val[j] = ++Time, x;
        z.push_back(j);
        for (auto e : g[j])
            if (comp[e] < 0)
                low = min(low, val[e] ?: dfs(e, g, f));

        if (low == val[j]) {
            do {
                x = z.back();
                z.pop_back();
                comp[x] = ncomps;
                cont.push_back(x);
            } while (x != j);
            f(cont);
            cont.clear();
            ncomps++;
        }
        return val[j] = low;
    }
    template <class G, class F> void scc(G &g, F f) {
        int n = sz(g);
        val.assign(n, 0);
        comp.assign(n, -1);
        Time = ncomps = 0;
        for (int i = 0; i < n; i++)
            if (comp[i] < 0)
                dfs(i, g, f);
    }

    int piv;
    void get_scc(int n) {
        scc(gph, [&](vector<int> &v) {});
        for (int i = 0; i < n; i++) {
            comp[i] = ncomps - comp[i];
        }
        piv = ncomps;
    }
} scc;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.precision(69);
    int n, m;
    cin >> n >> m;
    vector<string> str(n);
    for (auto &x : str)
        cin >> x;
    auto ok = [&](int x, int y) { return x >= 0 && x < n && y >= 0 && y < m && str[x][y] != '#'; };
    lint oneside = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (str[i][j] == '#') {
                continue;
            }
            if (i % 2 == j % 2) {
                oneside++;
                for (int k = 0; k < 4; k++) {
                    if (ok(i + dx[k], j + dy[k])) {
                        int v = (i + dx[k]) * m + (j + dy[k]);
                        bpm.add_edge(i * m + j, v);
                    }
                }
            }
        }
    }
    bpm.match(n * m);
    vector<int> idx(n * m, -1);
    int V = 0;
    for (int i = 0; i < n * m; i++) {
        if (bpm.l[i] != -1)
            idx[i] = V++;
    }
    scc.init(V);
    for (int i = 0; i < n * m; i++) {
        if (bpm.l[i] != -1) {
            for (auto &j : bpm.gph[i]) {
                if (j != bpm.l[i]) {
                    scc.add_edge(idx[i], idx[bpm.r[j]]);
                }
            }
        }
    }
    scc.get_scc(V);
    if (scc.piv >= 1557) {
        cout << "1000000\n";
        return 0;
    }
    int C = scc.piv;
    vector<vector<int>> gph(C);
    vector<int> siz(C);
    for (int i = 0; i < V; i++) {
        siz[scc.comp[i] - 1]++;
        for (auto &j : scc.gph[i]) {
            if (scc.comp[i] != scc.comp[j]) {
                //      cout << scc.comp[i] << " " << scc.comp[j] << "\n";
                gph[scc.comp[i] - 1].push_back(scc.comp[j] - 1);
            }
        }
    }
    lint sum = oneside * (oneside - 1);
    vector<bitset<1557>> reach(C);
    for (int i = C - 1; i >= 0; i--) {
        reach[i][i] = 1;
        for (auto &j : gph[i])
            reach[i] |= reach[j];
        for (int j = 0; j < C; j++) {
            if (!reach[i][j])
                sum += 1ll * siz[i] * siz[j];
        }
    }
    cout << min(1000000ll, sum) << "\n";
}