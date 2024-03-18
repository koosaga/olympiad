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
    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        mp[x]++;
    }
    map<int, int> counts;
    for (auto &[k, v] : mp)
        counts[v]++;
    vector<int> ans(n + 1);
    for (auto &[k, v] : counts) {
        for (int j = 1; j <= n; j++) {
            ans[j] += v * (k - k % j);
        }
    }
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
}