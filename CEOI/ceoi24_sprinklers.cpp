#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<lint> a(n), b(m);
    for (auto &x : a)
        cin >> x;
    a.insert(a.begin(), -2e9);
    a.insert(a.end(), 3e9);
    n = sz(a);
    for (auto &x : b)
        cin >> x;
    auto trial = [&](lint x) {
        vector<vector<pi>> attach(n + 1);
        vector<int> Lmax(n + 1, -1), Rmax(n + 1, n + 1);
        for (int i = 0; i < m; i++) {
            if (binary_search(all(a), b[i]))
                continue;
            int p0 = lower_bound(all(a), b[i] - x) - a.begin();
            int p1 = lower_bound(all(a), b[i]) - a.begin();
            int p2 = upper_bound(all(a), b[i] + x) - a.begin();
            if (p0 == p1 && p1 == p2)
                return string();
            if (p0 < p1 && p1 < p2)
                attach[p1].push_back({p0, p2});
            else if (p0 < p1) {
                //  cout << p0 << " " << p1 << endl;
                // [p0 .. p1) is not all L
                Lmax[p1] = max(Lmax[p1], p0);
            } else if (p1 < p2) {
                // [p1 .. p2) is not all R
                Rmax[p1] = min(Rmax[p1], p2);
            }
        }
        for (int i = 1; i <= n; i++) {
            Lmax[i] = max(Lmax[i], Lmax[i - 1]);
        }
        for (int i = n - 1; i >= 0; i--)
            Rmax[i] = min(Rmax[i], Rmax[i + 1]);
        vector<int> dp(n + 1);
        dp[0] = 1;
        vector<pi> trace(n + 1);
        int from = -1;
        set<int> toProp;
        for (int i = 1; i <= n; i++)
            toProp.insert(i);
        for (int i = 1; i < n; i++) {
            sort(all(attach[i]));
            if (dp[i - 1])
                from = i - 1;
            if (from <= Lmax[i])
                continue;
            int curBound = Rmax[i];
            for (int j = sz(attach[i]) - 1; j >= 0; j--) {
                if (attach[i][j][0] >= from)
                    curBound = min(curBound, (int)attach[i][j][1]);
            }
            auto it = toProp.lower_bound(i + 1);
            while (it != toProp.end() && *it < curBound) {
                int k = *it;
                if (!dp[k]) {
                    dp[k] = 1;
                    trace[k] = pi{from, i};
                }
                it = toProp.erase(it);
            }
        }
        if (!dp[n])
            return string();
        string ans(n, '0');
        for (int i = n; i; i = trace[i][0]) {
            for (int j = trace[i][0]; j < trace[i][1]; j++)
                ans[j] = 'L';
            for (int j = trace[i][1]; j < i; j++)
                ans[j] = 'R';
        }
        ans = ans.substr(1, n - 2);
        return ans;
    };
    int s = 0, e = 1e9 + 69;
    // int s = 1000, e = 1000;
    while (s != e) {
        int m = (s + e) / 2;
        if (sz(trial(m)))
            e = m;
        else
            s = m + 1;
    }
    if (s > int(1e9))
        cout << "-1\n";
    else {
        cout << s << "\n";
        cout << trial(s) << "\n";
    }
}