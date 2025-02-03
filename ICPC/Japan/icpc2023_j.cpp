#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

vector<vector<int>> gph;
vector<int> din, dout, chn, sub, dep, par;
int piv;

void dfs(int x) {
    sub[x] = 1;
    for (auto &y : gph[x]) {
        dep[y] = dep[x] + 1;
        par[y] = x;
        dfs(y);
        sub[x] += sub[y];
    }
    sort(all(gph[x]), [&](int a, int b) { return sub[a] > sub[b]; });
}

void hld(int x) {
    din[x] = piv++;
    if (sz(gph[x])) {
        chn[gph[x][0]] = chn[x];
        hld(gph[x][0]);
    }
    for (int i = 1; i < sz(gph[x]); i++) {
        chn[gph[x][i]] = gph[x][i];
        hld(gph[x][i]);
    }
    dout[x] = piv;
}

const int MAXT = 1050000;

struct seg {
    lint tree[MAXT], lazy[MAXT];
    void add(int s, int e, int ps, int pe, int p, lint v) {
        if (e < ps || pe < s)
            return;
        if (s <= ps && pe <= e) {
            tree[p] += v;
            lazy[p] += v;
            return;
        }
        for (int i = 2 * p; i < 2 * p + 2; i++) {
            tree[i] += lazy[p];
            lazy[i] += lazy[p];
        }
        lazy[p] = 0;
        int pm = (ps + pe) / 2;
        add(s, e, ps, pm, 2 * p, v);
        add(s, e, pm + 1, pe, 2 * p + 1, v);
        tree[p] = min(tree[2 * p], tree[2 * p + 1]);
    }
    lint query(int s, int e, int ps, int pe, int p) {
        if (e < ps || pe < s)
            return 5e18;
        if (s <= ps && pe <= e) {
            return tree[p];
        }
        int pm = (ps + pe) / 2;
        for (int i = 2 * p; i < 2 * p + 2; i++) {
            tree[i] += lazy[p];
            lazy[i] += lazy[p];
        }
        lazy[p] = 0;
        return min(query(s, e, ps, pm, 2 * p), query(s, e, pm + 1, pe, 2 * p + 1));
    }
} seg;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    cr(gph, n);
    cr(din, n);
    cr(dout, n);
    cr(chn, n);
    cr(sub, n);
    cr(dep, n);
    cr(par, n);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;
        gph[p].push_back(i);
    }
    vector<lint> a(n), t(n, 1);
    for (auto &x : a)
        cin >> x;
    dfs(0);
    hld(0);
    priority_queue<pi, vector<pi>, greater<pi>> pq;
    for (int i = 0; i < n; i++) {
        seg.add(din[i], din[i], 0, n - 1, 1, sub[i]);
        pq.push({a[i] * t[i], i});
    }
    lint ans = 0;
    int cnt = n;
    while (sz(pq) && cnt) {
        auto [v, x] = pq.top();
        pq.pop();
        bool good = true;
        for (int j = x;; j = par[chn[j]]) {
            int l = din[chn[j]];
            int r = din[j];
            if (seg.query(l, r, 0, n - 1, 1) == 0)
                good = false;
            if (l == 0 || !good)
                break;
        }
        if (!good)
            continue;
        ans += v;
        cnt--;
        for (int j = x;; j = par[chn[j]]) {
            int l = din[chn[j]];
            int r = din[j];
            seg.add(l, r, 0, n - 1, 1, -1);
            if (l == 0)
                break;
        }
        t[x] += 2;
        pq.push({a[x] * t[x], x});
    }
    cout << ans << "\n";
}