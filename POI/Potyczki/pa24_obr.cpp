#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int h, w, n;
    cin >> h >> w >> n;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    if (h % a[0] || w % a[0]) {
        cout << "-1\n";
        return 0;
    }
    h /= a[0];
    w /= a[0];
    lint ans = 0;
    for (int i = 0; i < n - 1; i++) {
        int d = a[i + 1] / a[i];
        ans += 1ll * h * w - 1ll * (h - h % d) * (w - w % d);
        h /= d;
        w /= d;
    }
    ans += 1ll * h * w;
    cout << ans << "\n";
}