//kuroni
#include <bits/stdc++.h>
using namespace std;

const double EPS = 1E-7;
const double INF = 1E18;

void solve() {
    int n; cin >> n;
    vector<array<int, 3>> a(n);
    for (auto &[x, y, v] : a) {
        cin >> x >> y >> v;
    }
    double le = 0, ri = 4E6;
    auto check = [&](double t) -> bool {
        vector<tuple<double, double, double, bool>> vec;
        long double mla = -INF, mlb = -INF;
        long double mra = INF, mrb = INF;
        for (auto [x, y, v] : a) {
            long double r = 1.0L * v * t;
            long double lb = x - y - r, rb = x - y + r;
            long double la = x + y - r, ra = x + y + r;
            mlb = max(lb, mlb); mrb = min(mrb, rb);
            mla = max(la, mla); mra = min(mra, ra);
        }
        if (mlb <= mrb && mla <= mra) {
            return true;
        } else {
            return false;
        }
    };
    while (le + EPS < ri) {
        double mi = (le + ri) / 2;
        (check(mi) ? ri : le) = mi;
    }
    cout << fixed << setprecision(10) << (le + ri) / 2 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1; // cin >> t;
    while (t--) {
        solve();
    }
}