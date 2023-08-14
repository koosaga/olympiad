#include <bits/stdc++.h>
using namespace std;
using lint = long long;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 100005;
const int MAXT = 10000000;

using pi = array<lint, 2>;

vector<int> v;

struct event {
    int x, s, e;
    lint val;
    bool operator<(const event &b) const { return x < b.x; }
    bool operator>(const event &b) const { return x > b.x; }
};

struct node {
    int l, r;
    array<array<lint, 2>, 2> sum;
} tree[MAXT];

int root[MAXN], piv;

int newnode() { return ++piv; }

void init(int s, int e, int p) {
    if (s == e)
        return;
    int m = (s + e) / 2;
    tree[p].l = newnode();
    tree[p].r = newnode();
    init(s, m, tree[p].l);
    init(m + 1, e, tree[p].r);
}

void add(int pos, int s, int e, int prv, int cur, array<array<lint, 2>, 2> v) {
    if (s == e) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                tree[cur].sum[i][j] = tree[prv].sum[i][j] + v[i][j];
            }
        }
        return;
    }
    int m = (s + e) / 2;
    if (pos <= m) {
        tree[cur].l = newnode();
        tree[cur].r = tree[prv].r;
        add(pos, s, m, tree[prv].l, tree[cur].l, v);
    } else {
        tree[cur].l = tree[prv].l;
        tree[cur].r = newnode();
        add(pos, m + 1, e, tree[prv].r, tree[cur].r, v);
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            tree[cur].sum[i][j] = tree[tree[cur].l].sum[i][j] + tree[tree[cur].r].sum[i][j];
        }
    }
}

array<array<lint, 2>, 2> query(int s, int e, int ps, int pe, int p) {
    if (e < ps || pe < s) {
        return {pi{0, 0}, pi{0, 0}};
    }
    if (s <= ps && pe <= e) {
        return tree[p].sum;
    }
    int pm = (ps + pe) / 2;
    auto q1 = query(s, e, ps, pm, tree[p].l);
    auto q2 = query(s, e, pm + 1, pe, tree[p].r);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            q1[i][j] += q2[i][j];
        }
    }
    return q1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int r, c, n, q, mod;
    cin >> r >> c >> n >> q >> mod;
    vector<event> rect;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2, w = 1;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2)
            swap(x1, x2);
        if (y1 > y2)
            swap(y1, y2);
        rect.push_back({x1, y1, y2, lint(w)});
        rect.push_back({x2, y1, y2, -lint(w)});
        v.push_back(y1);
        v.push_back(y2);
    }
    sort(all(rect));
    sort(all(v));
    v.resize(unique(all(v)) - v.begin());
    for (auto &x : rect) {
        x.s = lower_bound(all(v), x.s) - v.begin();
        x.e = lower_bound(all(v), x.e) - v.begin();
    }
    root[0] = newnode();
    init(0, sz(v) - 1, root[0]);
    auto Add = [&](int prv, int cur, int s, int e, lint v1, lint v2) {
        array<array<lint, 2>, 2> u1 = {pi{v1, -v1 * v[s]}, pi{v2, -v2 * v[s]}};
        array<array<lint, 2>, 2> u2 = {pi{-v1, v1 * v[e]}, pi{-v2, v2 * v[e]}};
        int wcur = newnode();
        add(s, 0, sz(v) - 1, prv, wcur, u1);
        add(e, 0, sz(v) - 1, wcur, cur, u2);
    };
    for (int i = 0; i < sz(rect); i++) {
        root[i + 1] = newnode();
        Add(root[i], root[i + 1], rect[i].s, rect[i].e, rect[i].val, -1ll * rect[i].val * rect[i].x);
    }
    auto Aux = [&](int root, int x, int e) {
        int pos = lower_bound(all(v), e) - v.begin();
        auto quer = query(0, pos - 1, 0, sz(v) - 1, root);
        lint sum0 = quer[0][0] * e + quer[0][1];
        lint sum1 = quer[1][0] * e + quer[1][1];
        return sum0 * x + sum1;
    };
    auto Query = [&](lint x, lint s, lint e) {
        int pos = upper_bound(all(rect), (event){(int)x, -1, -1}) - rect.begin();
        pos = root[pos];
        return Aux(pos, x, e) - Aux(pos, x, s);
    };
    lint l = 0;
    for (int i = 0; i < q; i++) {
        int x1, y1, x2, y2, vv;
        cin >> x1 >> y1 >> x2 >> y2 >> vv;
        x1 = (x1 + l * vv) % mod;
        x2 = (x2 + l * vv) % mod;
        y1 = (y1 + l * vv) % mod;
        y2 = (y2 + l * vv) % mod;
        if (x1 > x2)
            swap(x1, x2);
        if (y1 > y2)
            swap(y1, y2);
        l = Query(x2, y1, y2) - Query(x1, y1, y2);
        cout << l << "\n";
        l %= mod;
    }
}