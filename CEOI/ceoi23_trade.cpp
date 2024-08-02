#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 250005;
const lint inf = 1e18;

// Let a matrix be monotone if Opt(i) <= Opt(i + 1) for all rows i.
// Given a totally monotone matrix (where every 2x2 submatrix is monotone)
// find the list of row maxima positions.
// Source: maroonrk

template <class F, class D = pi> vector<int> smawk(F f, int n, int m) {
    vector<int> ans(n, -1);
    auto rec = [&](auto self, int *const rs, int x, int *const cs, int y) -> void {
        const int t = 8;
        if (x <= t || y <= t) {
            for (int i = 0; i < x; i++) {
                int r = rs[i];
                D mx;
                for (int j = 0; j < y; j++) {
                    int c = cs[j];
                    D w = f(r, c);
                    if (ans[r] == -1 || w > mx) {
                        ans[r] = c;
                        mx = w;
                    }
                }
            }
            return;
        }
        if (x < y) {
            int s = 0;
            for (int i = 0; i < y; i++) {
                int c = cs[i];
                while (s && f(rs[s - 1], cs[s - 1]) < f(rs[s - 1], c))
                    s--;
                if (s < x)
                    cs[s++] = c;
            }
            y = s;
        }
        auto a = rs + x, b = cs + y;
        int z = 0;
        for (int i = 1; i < x; i += 2)
            a[z++] = rs[i];
        for (int i = 0; i < y; i++)
            b[i] = cs[i];
        self(self, a, z, b, y);
        int k = 0;
        for (int i = 0; i < x; i += 2) {
            int to = i + 1 < x ? ans[rs[i + 1]] : cs[y - 1];
            D mx;
            while (1) {
                D w = f(rs[i], cs[k]);
                if (ans[rs[i]] == -1 || w > mx) {
                    ans[rs[i]] = cs[k];
                    mx = w;
                }
                if (cs[k] == to)
                    break;
                k++;
            }
        }
    };
    int *rs = new int[n * 2];
    for (int i = 0; i < n; i++)
        rs[i] = i;
    int *cs = new int[max(m, n * 2)];
    for (int i = 0; i < m; i++)
        cs[i] = i;
    rec(rec, rs, n, cs, m);
    delete[] rs;
    delete[] cs;
    return ans;
}

const int MAXT = 6000000;

struct node {
    int l, r;
    int cnt;
    lint sum;
} pool[MAXT];
int piv;

int newnode() { return ++piv; }
void init(int s, int e, int p) {
    if (s == e) {
        return;
    }
    int m = (s + e) / 2;
    pool[p].l = newnode();
    pool[p].r = newnode();
    init(s, m, pool[p].l);
    init(m + 1, e, pool[p].r);
}

void add(int s, int e, int pos, int prv, int cur, int c1, int c2) {
    pool[cur] = pool[prv];
    pool[cur].cnt += c1;
    pool[cur].sum += c2;
    if (s == e)
        return;
    int m = (s + e) / 2;
    if (pos <= m) {
        pool[cur].l = newnode();
        pool[cur].r = pool[prv].r;
        add(s, m, pos, pool[prv].l, pool[cur].l, c1, c2);
    } else {
        pool[cur].l = pool[prv].l;
        pool[cur].r = newnode();
        add(m + 1, e, pos, pool[prv].r, pool[cur].r, c1, c2);
    }
}

pi query(int s, int e, int k, int p1, int p2) {
    if (k == 0)
        return pi{0, inf};
    if (s == e)
        return pi{pool[p2].sum - pool[p1].sum, s};
    int m = (s + e) / 2;
    if (k <= pool[pool[p2].r].cnt - pool[pool[p1].r].cnt) {
        return query(m + 1, e, k, pool[p1].r, pool[p2].r);
    }
    k -= pool[pool[p2].r].cnt - pool[pool[p1].r].cnt;
    auto qq = query(s, m, k, pool[p1].l, pool[p2].l);
    qq[0] += pool[pool[p2].r].sum - pool[pool[p1].r].sum;
    return qq;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    for (auto &x : a)
        cin >> x;
    for (auto &x : b)
        cin >> x;
    vector<lint> asum(n + 1);
    for (int i = 1; i <= n; i++)
        asum[i] = a[i - 1] + asum[i - 1];

    vector<pi> crd;
    for (int i = 0; i < n; i++)
        crd.push_back({b[i], i});
    sort(all(crd));
    vector<int> roots(n + 1);
    roots[0] = newnode();
    init(0, sz(crd) - 1, roots[0]);
    for (int i = 1; i <= n; i++) {
        roots[i] = newnode();
        int pos = lower_bound(all(crd), pi{b[i - 1], i - 1}) - crd.begin();
        add(0, n - 1, pos, roots[i - 1], roots[i], 1, b[i - 1]);
    }
    auto cost = [&](int l, int r) {
        if (r - l + 1 < k)
            return pi{-inf, r - l + 1};

        lint cost = query(0, n - 1, k, roots[l], roots[r + 1])[0] - (asum[r + 1] - asum[l]);
        return pi{cost, -(r - l + 1)};
    };
    vector<int> optMin = smawk(cost, n - k + 1, n);
    vector<lint> value(n - k + 1);
    for (int i = 0; i <= n - k; i++) {
        value[i] = cost(i, optMin[i])[0];
    }
    lint opt = *max_element(all(value));
    int upto = n - 1;
    vector<lint> kth_threshold(n, inf);
    vector<vector<pi>> event(n);
    for (int i = n - k; i >= 0; i--) {
        if (value[i] != opt)
            continue;
        int new_upto = optMin[i];
        for (int j = new_upto; j <= upto; j++) {
            if (cost(i, j)[0] == opt) {
                event[i].push_back({crd[query(0, n - 1, k, roots[i], roots[j + 1])[1]][0], j});
            }
        }
        upto = new_upto;
    }
    priority_queue<pi, vector<pi>, greater<pi>> sweeps;
    sweeps.push({inf, n});
    for (int i = 0; i < n; i++) {
        for (auto &j : event[i])
            sweeps.push(j);
        while (sz(sweeps) && sweeps.top()[1] < i)
            sweeps.pop();
        kth_threshold[i] = sweeps.top()[0];
    }
    cout << opt << "\n";
    for (int i = 0; i < n; i++) {
        cout << (kth_threshold[i] <= b[i]);
    }
    return 0;
}