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
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    vector<int> di, dj;
    for (int i = 0; i < n; i++) {
        set<int> s;
        for (int j = 0; j < n; j++) {
            s.insert(a[i][j]);
        }
        if (sz(s) == n)
            di.push_back(i);
    }
    for (int i = 0; i < n; i++) {
        set<int> s;
        for (int j = 0; j < n; j++) {
            s.insert(a[j][i]);
        }
        if (sz(s) == n)
            dj.push_back(i);
    }
    cout << max(sz(di), sz(dj)) << "\n";
    auto inc = [&](int x, int y) {
        a[x][y]++;
        if (a[x][y] == n + 1)
            a[x][y] = 1;
    };
    while (sz(di) && sz(dj)) {
        int x = di.back();
        int y = dj.back();
        di.pop_back();
        dj.pop_back();
        inc(x, y);
        cout << x + 1 << " " << y + 1 << " " << a[x][y] << "\n";
    }
    bool flag = false;
    auto output = [&](int x, int y) {
        if (flag) {
            cout << y + 1 << " " << x + 1 << " " << a[x][y] << "\n";
        } else {
            cout << x + 1 << " " << y + 1 << " " << a[x][y] << "\n";
        }
    };
    if (sz(dj)) {
        flag = true;
        swap(di, dj);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++)
                swap(a[i][j], a[j][i]);
        }
    }
    if (sz(di) == 0)
        return;
    if (sz(di) == 1) {
        set<int> s;
        int x = di[0];
        for (int i = 0; i < n; i++) {
            if (i == x)
                continue;
            if (a[x][0] == a[i][0])
                continue;
            s.insert(a[i][0]);
        }
        if (sz(s) == 0) {
            inc(x, 0);
            output(x, 0);
        } else {
            a[x][0] = *s.begin();
            output(x, 0);
        }
        return;
    }
    if (sz(di) < n) {
        vector<int> mark(n + 2);
        for (int i = 0; i < sz(di); i++)
            mark[a[di[i]][0]] = 1;
        int val = 1;
        while (mark[val])
            val++;
        for (auto &x : di) {
            a[x][0] = val;
            output(x, 0);
        }
        return;
    }
    assert(sz(di) == n);
    for (auto &x : di) {
        inc(x, 0);
        output(x, 0);
    }
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