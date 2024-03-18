#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 1313131;

struct disj {
    int pa[MAXN], sz[MAXN], inc[MAXN], fucked[MAXN];
    void init(int n) {
        iota(pa, pa + n + 1, 0);
        fill(sz, sz + MAXN, 1);
    }
    int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
    bool uni(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v)
            return 0;
        pa[u] = v;
        sz[v] += sz[u];
        inc[v] += inc[u];
        fucked[v] |= fucked[u];
        return 1;
    }
    void compIncr(int v) {
        v = find(v);
        inc[v]++;
    }
    void fuckit(int v) {
        v = find(v);
        fucked[v] = 1;
    }
    bool fuck(int v) {
        v = find(v);
        return fucked[v];
    }
    bool paidFull(int v) {
        v = find(v);
        return inc[v] >= sz[v] - 1;
    }
} disj;

int deg[MAXN], idx[MAXN], vis[MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    disj.init(n + q);
    iota(idx, idx + n, 0);
    for (int i = 0; i < q; i++) {
        string s;
        cin >> s;
        if (s == "+") {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            a = idx[a];
            b = idx[b];
            if (a != b) {
                deg[a]++;
                deg[b]++;
            }
            if (!disj.uni(a, b)) {
                disj.fuckit(a);
            }
        } else if (s == "-") {
            int v;
            cin >> v;
            v--;
            disj.compIncr(idx[v]);
            idx[v] = n++;
        } else {
            int v;
            cin >> v;
            v--;
            v = idx[v];
            if (disj.fuck(v)) {
                cout << "1";
            } else if (deg[v] && !disj.paidFull(v)) {
                cout << "?";
            } else
                cout << "0";
        }
    }
    cout << "\n";
}