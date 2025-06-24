#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, s, c;
    cin >> n >> s >> c;
    vector<array<lint, 3>> a;
    int tmp = 0;
    for (int i = 0; i < n; i++) {
        int x, l, r;
        cin >> x >> l >> r;
        l = c - l;
        r = r - c;
        a.push_back({l, r, x});
        tmp += x;
    }
    pi L{0, 0}, R{0, 0};
    vector<pi> cvxh;
    pi ans;
    auto query = [&](lint m) {
        pi vec = pi{m, lint(1e12) - m};
        sort(all(a), [&](const array<lint, 3> &x, const array<lint, 3> &y) {
            lint va = x[0] * vec[0] + x[1] * vec[1];
            lint vb = y[0] * vec[0] + y[1] * vec[1];
            if (va == vb)
                return x[1] < y[1];
            return va < vb;
        });
        lint tx = 0, ty = 0, left = s;
        for (int i = 0; i < sz(a); i++) {
            lint d = min(left, a[i][2]);
            tx += a[i][0] * d;
            ty += a[i][1] * d;
            left -= d;
        }
        return pi{tx, ty};
    };
    {
        lint s = 1, e = lint(1e12) - 1;
        while (s != e) {
            lint m = (s + e) / 2;
            auto [tx, ty] = query(m);
            if (tx <= ty) {
                e = m;
            } else {
                s = m + 1;
            }
        }
        L = query(s - 1);
        R = query(s);
    }
    if (L == R) {
        ans[0] = max(L[0], L[1]);
        ans[1] = 1;
    } else {
        auto [x1, y1] = L;
        auto [x2, y2] = R;
        ans[0] = x2 * y1 - x1 * y2;
        ans[1] = (x2 - x1) + (y1 - y2);
        if (ans[1] < 0)
            ans[0] *= -1, ans[1] *= -1;
    }
    ans[1] *= 10000;
    cout << ans[0] / gcd(ans[0], ans[1]) << " " << ans[1] / gcd(ans[0], ans[1]) << "\n";
}
