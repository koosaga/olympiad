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
    int t;
    cin >> t;
    while (t--) {
        vector<lint> stk;
        int n;
        cin >> n;
        lint sum = 0;
        for (int i = 0; i < n; i++) {
            lint x;
            cin >> x;
            sum += x;
            while (sz(stk) >= 2 && stk[sz(stk) - 2] <= stk.back() && stk.back() >= x) {
                x += stk[sz(stk) - 2] - stk.back();
                stk.pop_back();
                stk.pop_back();
            }
            stk.push_back(x);
        }
        sort(all(stk)); reverse(all(stk));
        lint ans = 0;
        for(int i = 0; i< sz(stk); i++) ans += (i % 2 ? -stk[i] : stk[i]);
        cout << (sum + ans) / 2 << "\n";
    }
}