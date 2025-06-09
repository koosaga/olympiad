//kuroni
#include <bits/stdc++.h>
using namespace std;

const int MX = 1E4;

void solve() {
    vector<int> div(MX + 1, 1);
    for (int i = 2; i <= MX; i++) {
        if (div[i] == 1) {
            for (int j = i; j <= MX; j += i) {
                div[j] = i;
            }
        }
    }
    vector<int> pr(MX + 1);
    auto adjust = [&](int u, int coef) {
        while (u != 1) {
            pr[div[u]] += coef;
            u /= div[u];
        }
    };
    auto pw = [&](int64_t p, int k) {
        int64_t ans = 1;
        while (k--) {
            ans *= p;
        }
        return ans;
    };
    int a, b; cin >> a >> b; adjust(a, 1); adjust(b, -1);
    int64_t m = 1, n = 1;
    for (int p = MX; p >= 2; p--) {
        if (pr[p] == 0) {
            continue;
        }
        if (pr[p] % 2 == 0) {
            int dif = pr[p] / 2;
            int pm, pn;
            if (dif < 0) {
                pm = 1; pn = 1 - dif;
            } else {
                pm = dif + 1; pn = 1;
            }
            m *= pw(p, pm); n *= pw(p, pn);
        } else {
            if (pr[p] >= 1) {
                int pm = (pr[p] + 1) / 2;
                m *= pw(p, pm);
                adjust(p - 1, -1);
            } else {
                int pn = (-pr[p] + 1) / 2;
                n *= pw(p, pn);
                adjust(p - 1, 1);
            }
        }
    }
    cout << m << " " << n << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1; // cin >> t;
    while (t--) {
        solve();
    }
}