#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

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
            comp[i] = ncomps - comp[i] - 1;
        }
        piv = ncomps;
    }
} scc;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<vector<lint>> a(n, vector<lint>(n));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int x;
            cin >> x;
            if (x > 0)
                a[j][i] = x;
            else
                a[i][j] = -x;
        }
    }
    scc.init(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && a[i][j] == 0)
                scc.add_edge(i, j);
        }
    }
    scc.get_scc(n);
    vector<int> indeg(scc.piv), outdeg(scc.piv);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && a[i][j] == 0 && scc.comp[i] != scc.comp[j]) {
                indeg[scc.comp[j]] = 1;
                outdeg[scc.comp[i]] = 1;
            }
        }
    }
    priority_queue<pi, vector<pi>, greater<pi>> pq;
    vector<lint> dist(n, 1e18);
    vector<int> par(n);
    auto enq = [&](int x, lint v, int p) {
        if (dist[x] > v) {
            dist[x] = v;
            par[x] = p;
            pq.push({v, x});
        }
    };
    for (int i = 0; i < n; i++) {
        if (!outdeg[scc.comp[i]]) {
            enq(i, 0, -1);
        }
    }
    while (sz(pq)) {
        auto [d, x] = pq.top();
        pq.pop();
        if (dist[x] != d)
            continue;
        if (!indeg[scc.comp[x]]) {
            cout << dist[x] << "\n";
            break;
        }
        for (int y = 0; y < n; y++) {
            enq(y, d + a[x][y], x);
        }
    }
}