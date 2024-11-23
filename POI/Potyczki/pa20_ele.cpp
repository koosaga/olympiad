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
    int n;
    cin >> n;
    vector<lint> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    if (a[n] < a[0]) {
        cout << "-1\n";
        return 0;
    }
    vector<lint> v;
    for (int i = 0; i <= n; i++) {
        if (a[i] < a[0] || a[i] > a[n])
            continue;
        auto it = upper_bound(all(v), a[i]);
        if (it == v.end())
            v.push_back(a[i]);
        else
            *it = a[i];
    }
    cout << n + 1 - sz(v) << "\n";
}