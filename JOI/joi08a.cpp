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
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    vector<array<int, 3>> stk;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0 || stk.back()[2] == a[i]) {
            while (sz(stk) && stk.back()[2] == a[i]) {
                stk.pop_back();
            }
            array<int, 3> toput = {0, i, a[i]};
            if (sz(stk))
                toput[0] = stk.back()[1] + 1;
            stk.push_back(toput);
        } else {
            if (sz(stk)) {
                stk.pop_back();
            }
            while (sz(stk) && stk.back()[2] == a[i]) {
                stk.pop_back();
            }
            array<int, 3> toput = {0, i, a[i]};
            if (sz(stk))
                toput[0] = stk.back()[1] + 1;
            stk.push_back(toput);
        }
    }
    int ans = 0;
    for (auto &x : stk) {
        if (x[2] == 0)
            ans += x[1] - x[0] + 1;
    }
    cout << ans << "\n";
}
