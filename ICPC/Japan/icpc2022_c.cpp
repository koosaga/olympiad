#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 105;

int n, m;
string str[MAXN];
int ban[MAXN][MAXN], vis[MAXN][MAXN];
int ok(int x, int y) { return x >= 0 && x < n && y >= 0 && y < m && str[x][y] != '#'; };
int ok2(int x, int y) { return x >= 0 && x < n && y >= 0 && y < m; };

int jwasoobup(int pd) {
    memset(vis, 0, sizeof(vis));
    int px = -1, py = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (str[i][j] == 'S') {
                px = i;
                py = j;
            }
        }
    }
    if (ok2(px + dx[pd ^ 2], py + dy[pd ^ 2]))
        return -1;

    while (str[px][py] != 'T') {
        //  cout << px << " " << py << endl;
        vis[px][py] = 1;
        for (int i = 1; i <= 4; i++) {
            int j = ((pd ^ 2) + 4 - i) % 4;
            if (ok(px + dx[j], py + dy[j])) {
                px += dx[j];
                py += dy[j];
                pd = j;
                break;
            }
        }
    }
    vis[px][py] = 1;
    return 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << vis[i][j];
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}

template <class flow_t> struct HLPP {
    struct Edge {
        int to, inv;
        flow_t rem, cap;
    };

    vector<vector<Edge>> G; // Don't use basic_string here, it will fuck up your entire life
    vector<flow_t> excess;
    vector<int> hei, arc, prv, nxt, act, bot;
    queue<int> Q;
    int n, high, cut, work;

    // Initialize for n vertices
    HLPP(int k) : G(k) {}

    int addEdge(int u, int v, flow_t cap, flow_t rcap = 0) {
        G[u].push_back({v, sz(G[v]), cap, cap});
        G[v].push_back({u, sz(G[u]) - 1, rcap, rcap});
        return sz(G[u]) - 1;
    }

    void raise(int v, int h) {
        prv[nxt[prv[v]] = nxt[v]] = prv[v];
        hei[v] = h;
        if (excess[v] > 0) {
            bot[v] = act[h];
            act[h] = v;
            high = max(high, h);
        }
        if (h < n)
            cut = max(cut, h + 1);
        nxt[v] = nxt[prv[v] = h += n];
        prv[nxt[nxt[h] = v]] = v;
    }

    void global(int s, int t) {
        hei.assign(n, n * 2);
        act.assign(n * 2, -1);
        iota(all(prv), 0);
        iota(all(nxt), 0);
        hei[t] = high = cut = work = 0;
        hei[s] = n;
        for (int x : {t, s})
            for (Q.push(x); !Q.empty(); Q.pop()) {
                int v = Q.front();
                for (auto &e : G[v]) {
                    if (hei[e.to] == n * 2 && G[e.to][e.inv].rem)
                        Q.push(e.to), raise(e.to, hei[v] + 1);
                }
            }
    }

    void push(int v, Edge &e, bool z) {
        auto f = min(excess[v], e.rem);
        if (f > 0) {
            if (z && !excess[e.to]) {
                bot[e.to] = act[hei[e.to]];
                act[hei[e.to]] = e.to;
            }
            e.rem -= f;
            G[e.to][e.inv].rem += f;
            excess[v] -= f;
            excess[e.to] += f;
        }
    }

    void discharge(int v) {
        int h = n * 2, k = hei[v];

        for (int j = 0; j < sz(G[v]); j++) {
            auto &e = G[v][arc[v]];
            if (e.rem) {
                if (k == hei[e.to] + 1) {
                    push(v, e, 1);
                    if (excess[v] <= 0)
                        return;
                } else
                    h = min(h, hei[e.to] + 1);
            }
            if (++arc[v] >= sz(G[v]))
                arc[v] = 0;
        }

        if (k < n && nxt[k + n] == prv[k + n]) {
            for (int j = k; j < cut; j++) {
                while (nxt[j + n] < n)
                    raise(nxt[j + n], n);
            }
            cut = k;
        } else
            raise(v, h), work++;
    }

    // Compute maximum flow from src to dst
    flow_t flow(int src, int dst) {
        excess.assign(n = sz(G), 0);
        arc.assign(n, 0);
        prv.assign(n * 3, 0);
        nxt.assign(n * 3, 0);
        bot.assign(n, 0);
        for (auto &e : G[src]) {
            excess[src] = e.rem, push(src, e, 0);
        }

        global(src, dst);

        for (; high; high--)
            while (act[high] != -1) {
                int v = act[high];
                act[high] = bot[v];
                if (v != src && hei[v] == high) {
                    discharge(v);
                    if (work > 4 * n)
                        global(src, dst);
                }
            }

        return excess[dst];
    }

    // Get flow through e-th edge of vertex v
    flow_t getFlow(int v, int e) { return G[v][e].cap - G[v][e].rem; }

    // Get if v belongs to cut component with src
    bool cutSide(int v) { return hei[v] >= n; }
};

int piv;
int comp[MAXN][MAXN];

void dfs(int x, int y) {
    if (vis[x][y])
        return;
    vis[x][y] = 1;
    comp[x][y] = piv;
    for (int i = 0; i < 4; i++) {
        if (ok(x + dx[i], y + dy[i]) && ((ban[x][y] >> i) % 2) == 0) {
            dfs(x + dx[i], y + dy[i]);
        }
    }
}

int solve() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (vis[i][j]) {
                for (int k = 0; k < 4; k++) {
                    if (ok(i + dx[k], j + dy[k]) && vis[i + dx[k]][j + dy[k]] && (ban[i][j] >> k) % 2) {
                        ban[i][j] ^= (1 << k);
                    }
                }
            }
        }
    }
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (str[i][j] != '#' && !vis[i][j]) {
                dfs(i, j);
                piv++;
            }
        }
    }
    int S = -1, T = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (str[i][j] == 'S') {
                S = comp[i][j];
            }
            if (str[i][j] == 'U') {
                T = comp[i][j];
            }
        }
    }
    if (S > T)
        swap(S, T);
    if (S == T) {
        return -1;
    }
    map<pi, int> edges;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 4; k++) {
                if (ok(i, j) && ok(i + dx[k], j + dy[k]) && comp[i][j] < comp[i + dx[k]][j + dy[k]]) {
                    edges[{comp[i][j], comp[i + dx[k]][j + dy[k]]}]++;
                }
            }
        }
    }
    HLPP<int> mf(2 * piv);
    // cout << S << " " << T << endl;
    for (int i = 0; i < piv; i++) {
        mf.addEdge(i, i + piv, 1e9);
    }
    for (auto &[x, w] : edges) {
        auto [u, v] = x;
        //  cout << u << " " << v << endl;
        if (u == S && v == T)
            return -1;
        for (int j = 0; j < 1; j++) {
            mf.addEdge(u + piv * j, v + piv * (j + 1), 1e9);
            mf.addEdge(v + piv * j, u + piv * (j + 1), 1e9);
        }
        for (int j = 0; j < 2; j++) {
            mf.addEdge(u + piv * j, v + piv * j, w, w);
        }
    }
    return mf.flow(S, piv + T);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> str[i];
    }
    int q;
    cin >> q;
    while (q--) {
        int r, c;
        string d;
        cin >> r >> c >> d;
        r--;
        c--;
        if (d == "r") {
            ban[r][c] |= 2;
            ban[r][c + 1] |= 8;
        } else {
            ban[r][c] |= 1;
            ban[r + 1][c] |= 4;
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            if (jwasoobup(j) == -1) {
                continue;
            }
            bool fallback = 0;
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < m; k++) {
                    if (str[j][k] == 'U' && vis[j][k])
                        fallback = 1;
                }
            }
            if (!fallback) {
                cout << solve() << "\n";
                return 0;
            }
        }
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                if (str[j][k] == 'S' || str[j][k] == 'T') {
                    str[j][k] = 'S' + 'T' - str[j][k];
                }
            }
        }
    }
    cout << "-1\n";
}