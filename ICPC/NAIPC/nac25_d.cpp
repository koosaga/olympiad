//kuroni
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, w, h; cin >> n >> m >> w >> h;
    vector<pair<int64_t, int64_t>> top(n), bot(m);
    vector<int64_t> hi(w + 1, h + 2), lo(w + 1, -h - 2);
    for (auto& [x, y] : top) {
        cin >> x >> y;
    }
    for (auto& [x, y] : bot) {
        cin >> x >> y;
    }
    {
        // build top
        for (int i = 0; i + 1 < n; i++) {
            auto [px, py] = top[i];
            auto [nx, ny] = top[i + 1];
            if (px == nx) {
                hi[px] = min({hi[px], py - 1, ny - 1});
            } else {
                assert(px < nx);
                for (int x = px; x <= nx; x++) {
                    int64_t cur = 1.0L * (ny - py) / (nx - px) * (x - px) + py;
                    while ((cur - py) * (nx - px) >= (ny - py) * (x - px)) {
                        cur--;
                    }
                    while ((cur + 1 - py) * (nx - px) < (ny - py) * (x - px)) {
                        cur++;
                    }
                    hi[x] = min(hi[x], cur);
                }
            }
        }
        // build bottom
        for (int i = 0; i + 1 < m; i++) {
            auto [px, py] = bot[i];
            auto [nx, ny] = bot[i + 1];
            if (px == nx) {
                lo[px] = max({lo[px], py + 1, ny + 1});
            } else {
                assert(px < nx);
                for (int x = px; x <= nx; x++) {
                    int64_t cur = 1.0L * (ny - py) / (nx - px) * (x - px) + py;
                    while ((cur - py) * (nx - px) <= (ny - py) * (x - px)) {
                        cur++;
                    }
                    while ((cur - 1 - py) * (nx - px) > (ny - py) * (x - px)) {
                        cur--;
                    }
                    lo[x] = max(lo[x], cur);
                }
            }
        }
    }
    int64_t l = 0, r = 0;
    for (int x = 1; x <= w; x++) {
        l--; r++;
        l = max(l, lo[x]); r = min(r, hi[x]);
        if ((l + x) % 2 != 0) {
            l++;
        }
        if ((r + x) % 2 != 0) {
            r--;
        }
        if (l > r) {
            cout << "impossible\n"; return;
        }
    }
    cout << l << " " << r << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1; // cin >> t;
    while (t--) {
        solve();
    }
}