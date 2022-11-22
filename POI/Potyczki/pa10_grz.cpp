#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 1000005;
const int MAXT = 2100000;
const lint inf = 4e18;
const int mod = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<lint> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    q++;
    if (n == 1) {
        cout << a[0] * ((q + 1) / 2) << "\n";
    } else {
        lint sum = a[0];
        lint ans = a[0];
        for (int i = 1; i < n; i++) {
            sum += a[i];
            if (q >= i + 1) {
                int l = (q - i - 1) / 2;
                int r = (q - i) / 2;
                ans = max(ans, sum + r * a[i - 1] + l * a[i]);
            }
        }
        cout << ans << "\n";
    }
}