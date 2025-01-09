#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
using llf = long double;

bool cmp(pi a, pi b) { return a[0] * b[1] < b[0] * a[1]; }

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int z = n;
    vector<int> pdivs;
    for (int i = 2; i * i <= n; i++) {
        if (z % i == 0) {
            pdivs.push_back(i);
            while (z % i == 0)
                z /= i;
        }
    }
    if (z > 1)
        pdivs.push_back(z);
    pi ans{1, 0};
    for (auto &k : pdivs) {
        vector<int> counts(k);
        multiset<int> mses;
        for (int i = 0; i < n; i++) {
            counts[i % k] += a[i];
        }
        for (int i = 0; i < k; i++) {
            mses.insert(counts[i]);
        }
        auto upd = [&]() {
            int minv = *mses.begin();
            int maxv = *mses.rbegin();
            ans = min(ans, pi{maxv, minv}, cmp);
        };
        upd();
        for (int i = 1; i < n; i++) {
            mses.erase(mses.find(counts[(i - 1) % k]));
            mses.erase(mses.find(counts[(i - 0) % k]));
            counts[(i - 1) % k] -= a[i - 1];
            counts[i % k] -= a[i];
            swap(a[i - 1], a[i]);
            counts[(i - 1) % k] += a[i - 1];
            counts[i % k] += a[i];
            mses.insert(counts[(i - 1) % k]);
            mses.insert(counts[(i - 0) % k]);
            upd();
        }
        for (int i = n - 1; i > 0; i--) {
            swap(a[i - 1], a[i]);
        }
    }
    int g = gcd(ans[0], ans[1]);
    cout << ans[0] / g << " " << ans[1] / g << "\n";
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
        solve();
}