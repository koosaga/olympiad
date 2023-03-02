#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int d, n, m;
    cin >> d >> n >> m;
    vector<int> a(n);
    for (int i = 1; i < n; i++)
        cin >> a[i];
    a.push_back(d);
    sort(all(a));
    lint ans = 0;
    while (m--) {
        int z;
        cin >> z;
        auto it = lower_bound(all(a), z + 1);
        ans += min(*it - z, z - *prev(it));
    }
    cout << ans << "\n";
}