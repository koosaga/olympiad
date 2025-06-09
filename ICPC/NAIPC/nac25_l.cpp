//kuroni
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t r, w, h; cin >> r >> w >> h;
    int64_t ans = 0;
    for (int _ = 0; _ < 2; _++) {
        int64_t bound_on_w = sqrt(2.0L * r * r / w / w);
        // cerr << w << " " << h << " " << bound_on_w << '\n';
        auto check = [&](int64_t xw, int64_t xh) {
            if (xw * w > 2 * r || xh * h > 2 * r) {
                return false;
            }
            return (xw * w) * (xw * w) + (xh * h) * (xh * h) <= 4 * r * r;
        };
        for (int i = -5000; i <= 5000; i++) {
            if (bound_on_w + i <= 0) {
                continue;
            }
            int64_t xw = bound_on_w + i;
            if (!check(xw, 0)) {
                continue;
            }
            int64_t xh = sqrt((4.0L * r * r - 1.0 * (xw * w) * (xw * w)) / h / h);
            while (!check(xw, xh)) {
                xh--;
            }
            while (check(xw, xh + 1)) {
                xh++;
            }
            // cerr << xw << " " << xh << '\n';
            ans = max(ans, xw * xh);
        }
        swap(w, h);
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1; cin >> t;
    while (t--) {
        solve();
    }
}