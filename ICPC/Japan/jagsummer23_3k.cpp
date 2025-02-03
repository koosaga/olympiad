#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 200005;

struct disj {
    int pa[MAXN], sz[MAXN];
    void init(int n) {
        iota(pa, pa + n, 0);
        fill(sz, sz + n, 1);
    }
    int find(int x) { return (pa[x] == x ? x : find(pa[x])); }
    bool uni(int p, int q, vector<pair<int *, int>> &rb) {
        p = find(p);
        q = find(q);
        if (p == q)
            return 0;
        if (sz[p] > sz[q])
            swap(p, q);
        rb.push_back({&pa[p], pa[p]});
        rb.push_back({&sz[q], sz[q]});
        pa[p] = q;
        sz[q] += sz[p];
        return 1;
    }
} disj;

void rollback(vector<pair<int *, int>> &rb) {
    reverse(all(rb));
    for (auto &[a, b] : rb) {
        *a = b;
    }
}

int n, comp;
vector<pi> ask;
bool ok[MAXN];

void solve(int s, int e, vector<array<int, 4>> &edges, bool good = 0) {

    vector<pair<int *, int>> rb;
    rb.push_back({&comp, comp});
    vector<array<int, 4>> L, R;
    int m = (s + e) / 2;

    for (auto &[u, v, l, r] : edges) {
        if (l <= s && e <= r) {
            if (disj.uni(u, v + n, rb))
                comp--;
            if (disj.uni(u + n, v, rb))
                comp--;
            if (disj.find(u) == disj.find(u + n)) {
                good = 1;
            }
        } else {
            if (l < m)
                L.push_back({u, v, l, r});
            if (r > m)
                R.push_back({u, v, l, r});
        }
    }
    if (e - s == 1) {
        if (comp <= 2) {
            auto [x, y] = ask[s];
            if ((good && comp == 1) || (!good && comp <= 2 && ((disj.find(x) == disj.find(y)) == (n % 2 == 1))))
                ok[s] = 1;
        }
    } else {
        solve(s, m, L, good);
        solve(m, e, R, good);
    }
    rollback(rb);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int m, q;
    cin >> n >> m >> q;
    comp = 2 * n;
    map<pi, int> mp;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        mp[pi{u, v}] = 0;
    }
    vector<array<int, 4>> edges;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y;
            cin >> x >> y;
            x--;
            y--;
            if (mp.count(pi{x, y})) {
                if (mp[pi{x, y}] < sz(ask))
                    edges.push_back({x, y, mp[pi{x, y}], sz(ask)});
                mp.erase(pi{x, y});
            } else {
                mp[pi{x, y}] = sz(ask);
            }
        }
        if (t == 2) {
            int x, y;
            cin >> x >> y;
            x--;
            y--;
            ask.push_back({x, y});
        }
    }
    for (auto &[k, v] : mp) {
        if (v < sz(ask))
            edges.push_back({k[0], k[1], v, sz(ask)});
    }
    disj.init(n * 2);
    solve(0, sz(ask), edges);
    for (int i = 0; i < sz(ask); i++)
        cout << (ok[i] ? "Yes" : "No") << "\n";
}