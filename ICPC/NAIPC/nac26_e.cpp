//kuroni
#include <bits/stdc++.h>
using namespace std;

void solve() {
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; cin >> s;
    int m; cin >> m;
    int a = 0;
    int64_t ans = -m;
    for (char c : s) {
        if (c == 'A') {
            a++;
        } else {
            ans += a;
        }
    }
    cout << max<int64_t>(ans, 0) << '\n';
}