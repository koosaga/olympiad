#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int mod = 998244353; // 1e9 + 7;//993244853;

vector<vector<int>> gph;

void init(int n) { gph.resize(n); }

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
template <class G, class F> void scc(G &g, int n, F f) {
    val.assign(n, 0);
    comp.assign(n, -1);
    Time = ncomps = 0;
    for (int i = 0; i < n; i++)
        if (comp[i] < 0)
            dfs(i, g, f);
}

int piv;
void get_scc(int n) {
    scc(gph, n, [&](vector<int> &v) {});
    for (int i = 0; i < n; i++) {
        comp[i] = ncomps - comp[i] - 1;
    }
    piv = ncomps;
}

int n, m, s, p;
int dp[500005], cost[500005];

int main() {
    scanf("%d %d", &n, &m);
    init(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x - 1, y - 1);
    }
    get_scc(n);
    vector<int> ord(n);
    iota(all(ord), 0);
    sort(all(ord), [&](const int &a, const int &b) { return comp[a] < comp[b]; });
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        cost[comp[i]] += x;
    }
    scanf("%d %d", &s, &p);
    s--;
    fill(dp, dp + n, -1e9);
    int j = 0;
    for (int i = 0; i < piv; i++) {
        if (i == comp[s])
            dp[i] = max(dp[i], 0);
        dp[i] += cost[i];

        while (j < n && comp[ord[j]] == i) {
            for (auto &k : gph[ord[j]]) {
                dp[comp[k]] = max(dp[i], dp[comp[k]]);
            }
            j++;
        }
    }
    int ans = 0;
    for (int i = 0; i < p; i++) {
        int x;
        scanf("%d", &x);
        ans = max(ans, dp[comp[x - 1]]);
    }
    printf("%d\n", ans);
}