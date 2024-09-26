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
    int n, s;
    cin >> n >> s;
    vector<array<int, 3>> v;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        r = min(r, s - 1);
        if (l <= r) {
            v.push_back({l, r, i + 1});
        }
    }
    vector<pi> matches;
    sort(all(v), [&](const array<int, 3> &a, const array<int, 3> &b) { return a[1] < b[1]; });
    int ptr = sz(v);
    set<pi> st;
    for (auto &[l, r, idx] : v) {
        if (r * 2 < s) {
            while (ptr > 0 && v[ptr - 1][1] + r >= s) {
                ptr--;
                st.insert({v[ptr][0], v[ptr][2]});
            }
            auto it = st.lower_bound({s - l + 1, -1});
            if (it != st.begin()) {
                it--;
                matches.push_back({idx, (*it)[1]});
                st.erase(it);
            }
        } else
            break;
    }
    vector<int> marks(n + 1);
    for (auto &[x, y] : matches)
        marks[x] = marks[y] = 1;
    vector<pi> vect;
    for (auto &[l, r, idx] : v) {
        if (r * 2 >= s && !marks[idx]) {
            vect.push_back({l, idx});
        }
    }
    sort(all(vect));
    int j = sz(vect) - 1;
    for (int i = 0; i < sz(vect); i++) {
        while (j > i && vect[i][0] + vect[j][0] > s)
            j--;
        if (j <= i)
            break;
        matches.push_back({vect[i][1], vect[j][1]});
        j--;
    }
    cout << sz(matches) << "\n";
    for (auto &[x, y] : matches)
        cout << x << " " << y << "\n";
}