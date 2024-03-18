#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using bs = bitset<640>;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> cnt(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x - 1]++;
    }
    sort(all(cnt));
    reverse(all(cnt));
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += 2 * cnt[i] - 1;
        if (sum >= n) {
            cout << i + 1 << "\n";
            return 0;
        }
    }
}