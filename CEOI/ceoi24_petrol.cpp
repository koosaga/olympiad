#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 140005;

lint on, k, ans[MAXN];
int actual[MAXN];

inline int good(int v) { return v < on; }

vector<pi> gph[MAXN];
vector<int> dfn;
int vis[MAXN], sz[MAXN], msz[MAXN];

void dfs(int x, int p = -1) {
    dfn.push_back(x);
    sz[x] = 1, msz[x] = 0;
    for (auto &y : gph[x]) {
        if (y[1] != p && !vis[y[1]]) {
            dfs(y[1], x);
            sz[x] += sz[y[1]];
            msz[x] = max(msz[x], sz[y[1]]);
        }
    }
}

int get_center(int x) {
    dfn.clear();
    dfs(x);
    pi ret{int(1e9), -1};
    for (auto &x : dfn) {
        int w = max(sz(dfn) - sz[x], msz[x]);
        ret = min(ret, pi{w, x});
    }
    return ret[1];
}

vector<lint> stk;
vector<int> nodes, din;

int parent[MAXN], label[MAXN], subcnt[MAXN], realsub[MAXN];
lint depth[MAXN];

void dfs_count(int x, int p = -1, int subnum = -1) {
    subcnt[x] = good(x); // TODO: change for non-binary
    realsub[x] = good(x);
    label[x] = (subnum == -1 ? x : subnum);
    if (subnum != -1) {
        int pos = lower_bound(all(stk), stk.back() - k) - stk.begin();
        parent[x] = nodes[pos];
    }
    din.push_back(x);
    for (auto &[w, y] : gph[x]) {
        if (y == p || vis[y])
            continue;
        lint bk = stk.back() + w;
        stk.push_back(bk);
        nodes.push_back(y);
        depth[y] = depth[x] + w;
        dfs_count(y, x, subnum == -1 ? y : subnum);
        realsub[x] += realsub[y];
        stk.pop_back();
        nodes.pop_back();
    }
}

vector<pi> v;
lint ptr, sum;

void dfs_down(int x, int p, int w) {
    lint pptr = ptr;
    lint psum = sum;
    {
        sum += w;
        int npptr = -1;
        {
            int s = 1, e = sz(v);
            while (s != e) {
                int m = (s + e) / 2;
                if (v[m][0] < sum - k)
                    s = m + 1;
                else
                    e = m;
            }
            npptr = s;
        }
        assert(npptr >= ptr);
        lint cur = v[npptr - 1][1] - v[ptr - 1][1];
        ans[actual[p]] += cur * realsub[x];
        cur += v.back()[1];
        v.push_back({sum - w, cur});
        ptr = npptr;
    }
    for (auto &[w, y] : gph[x]) {
        if (!vis[y] && y != p) {
            dfs_down(y, x, w);
        }
    }
    ptr = pptr;
    sum = psum;
    v.pop_back();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n >> k;
    on = n;
    iota(actual, actual + n, 0);
    {
        vector<map<lint, lint>> adj(n);
        for (int i = 0; i < n - 1; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u][v] = w;
            adj[v][u] = w;
        }
        int nv = n;
        for (int i = 0; i < n; i++) {
            while (sz(adj[i]) > 3) {
                adj.emplace_back();
                auto [v1, w1] = *adj[i].begin();
                adj[i].erase(adj[i].begin());
                adj[v1].erase(adj[v1].find(i));
                auto [v2, w2] = *adj[i].begin();
                adj[i].erase(adj[i].begin());
                adj[v2].erase(adj[v2].find(i));
                adj[nv][v1] = adj[v1][nv] = w1;
                adj[nv][v2] = adj[v2][nv] = w2;
                adj[i][nv] = adj[nv][i] = 0;
                actual[nv] = i;
                nv++;
            }
        }
        n = nv;
        for (int i = 0; i < n; i++) {
            for (auto &[y, x] : adj[i]) {
                gph[i].push_back({x, y});
            }
        }
    }
    queue<int> que;
    que.push(0);
    while (sz(que)) {
        auto x = que.front();
        que.pop();
        x = get_center(x);
        //  cout << "cent" << x << endl;
        vis[x] = 1;
        depth[x] = 0;
        stk = {0};
        nodes = {x};
        din.clear();
        dfs_count(x);
        reverse(all(din));
        for (auto &v : din) {
            if (v != x) {
                subcnt[parent[v]] += subcnt[v];
            }
        }
        vector<array<lint, 3>> boxofchocolates;
        for (auto &v : din) {
            if (v == x)
                boxofchocolates.push_back({x, good(v), k});
            else if (parent[v] == x) {
                boxofchocolates.push_back({label[v], subcnt[v], k - depth[v]});
            }
        }
        int total = 0;
        map<int, int> mp;
        for (auto &[subtree, count, remain] : boxofchocolates) {
            //  cout << subtree << " " << remain << " " << count << endl;
            mp[subtree] += count;
            total += count;
        }
        for (auto &v : din) {
            if (v != x) {
                ans[actual[v]] += 1ll * (total - mp[label[v]]) * (subcnt[v] - good(v));
            }
        }
        for (auto &y : gph[x]) {
            if (vis[y[1]])
                continue;
            v.clear();
            v.push_back({0, 0});
            for (auto &[subtree, count, remain] : boxofchocolates) {
                if (y[1] == subtree)
                    continue;
                v.push_back(pi{remain, count});
            }
            sort(all(v));
            for (int i = 1; i < sz(v); i++)
                v[i][1] += v[i - 1][1];
            ptr = 1;
            sum = k;
            dfs_down(y[1], x, y[0]);
        }
        for (auto &y : gph[x]) {
            if (!vis[y[1]]) {
                que.push(y[1]);
            }
        }
    }
    for (int i = 0; i < on; i++)
        cout << ans[i] << "\n";
}