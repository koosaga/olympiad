#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXT = 530000;

struct rectangle {
    int sx, ex, sy, ey;
};

struct event {
    int pos, s, e, dx;
};

vector<int> v;

struct seg {
    struct node {
        int minv, cnt[11], lazy;
        node operator+(const node &x) const {
            node ret;
            ret.minv = min(minv, x.minv);
            ret.lazy = 0;
            memset(ret.cnt, 0, sizeof(ret.cnt));
            for (int i = 0; i < 11; i++) {
                int d = minv - ret.minv + i;
                if (d < 11)
                    ret.cnt[d] += cnt[i];
            }
            for (int i = 0; i < 11; i++) {
                int d = x.minv - ret.minv + i;
                if (d < 11)
                    ret.cnt[d] += x.cnt[i];
            }
            return ret;
        }
    } tree[MAXT];
    void init(int s, int e, int p) {
        if (s == e) {
            tree[p].minv = tree[p].lazy = 0;
            memset(tree[p].cnt, 0, sizeof(tree[p].cnt));
            tree[p].cnt[0] = v[e + 1] - v[s];
            return;
        }
        int m = (s + e) / 2;
        init(s, m, 2 * p);
        init(m + 1, e, 2 * p + 1);
        tree[p] = tree[2 * p] + tree[2 * p + 1];
    }
    void lazydown(int p) {
        for (int i = 2 * p; i < 2 * p + 2; i++) {
            tree[i].lazy += tree[p].lazy;
            tree[i].minv += tree[p].lazy;
        }
        tree[p].lazy = 0;
    }
    void add(int s, int e, int ps, int pe, int p, int v) {
        if (e < ps || pe < s)
            return;
        if (s <= ps && pe <= e) {
            tree[p].lazy += v;
            tree[p].minv += v;
            return;
        }
        lazydown(p);
        int pm = (ps + pe) / 2;
        add(s, e, ps, pm, 2 * p, v);
        add(s, e, pm + 1, pe, 2 * p + 1, v);
        tree[p] = tree[2 * p] + tree[2 * p + 1];
    }
} seg;

vector<lint> count_small_insec(vector<rectangle> rec, int sx, int ex, int sy, int ey, int k) {
    v.clear();
    vector<lint> ret(k);
    for (auto &x : rec) {
        v.push_back(x.sy);
        v.push_back(x.ey + 1);
    }
    v.push_back(sy);
    v.push_back(ey + 1);
    sort(all(v));
    v.resize(unique(all(v)) - v.begin());
    for (auto &x : rec) {
        x.sy = lower_bound(all(v), x.sy) - v.begin();
        x.ey = lower_bound(all(v), x.ey + 1) - v.begin();
    }
    seg.init(0, sz(v) - 2, 1);
    vector<event> ev;
    ev.push_back({sx, 0, sz(v) - 1, +0});
    ev.push_back({ex + 1, 0, sz(v) - 1, +0});
    for (auto &x : rec) {
        ev.push_back({x.sx, x.sy, x.ey, +1});
        ev.push_back({x.ex + 1, x.sy, x.ey, -1});
    }
    sort(all(ev), [&](event &a, event &b) { return a.pos < b.pos; });
    for (int i = 0; i < sz(ev);) {
        int j = i;
        while (j < sz(ev) && ev[j].pos == ev[i].pos)
            j++;
        for (int k = i; k < j; k++) {
            seg.add(ev[k].s, ev[k].e - 1, 0, sz(v) - 2, 1, ev[k].dx);
        }

        if (j < sz(ev)) {
            lint d = ev[j].pos - ev[i].pos;
            for (int x = 0; x + seg.tree[1].minv < k; x++) {
                ret[x + seg.tree[1].minv] += seg.tree[1].cnt[x] * d;
            }
        }

        i = j;
    }

    return ret;
}
int main() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> a(2);
    for (int i = 0; i < 2; i++) {
        a[i].resize(n);
        for (auto &j : a[i])
            cin >> j;
    }
    vector<rectangle> rect;
    for (int i = 0; i < n; i++) {
        vector<array<int, 3>> v = {{a[0][i], 0, 0}, {a[1][i], 1, 0}, {a[0][(i + 1) % n], 0, 1}, {a[1][(i + 1) % n], 1, 1}, {0, -1, -1}, {2 * n + 1, -1, -1}};
        sort(all(v));
        for (int j = 1; j <= 4; j++) {
            for (int k = j; k <= 4; k++) {
                int chk[2][2] = {};
                for (int z = j; z <= k; z++) {
                    chk[v[z][1]][v[z][2]] = 1;
                }
                if (chk[0][0] || chk[1][0]) {
                    int valid = 1;
                    if (chk[0][1] && chk[0][0])
                        valid = 0;
                    if (chk[1][1] && chk[1][0])
                        valid = 0;
                    if (valid)
                        rect.push_back({v[j - 1][0] + 1, v[j][0], v[k][0], v[k + 1][0] - 1});
                }
            }
        }
    }
    auto ans = count_small_insec(rect, 1, 2 * n, 1, 2 * n, k + 1);
    ans[1] += ans[0] - 1ll * 2 * n * (2 * n - 1) / 2;
    for (int i = 1; i <= k; i++)
        cout << ans[i] << " ";
    cout << "\n";
}

