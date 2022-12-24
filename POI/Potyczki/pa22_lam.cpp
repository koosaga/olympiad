#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int nxt[20][250005];

vector<pi> gen(vector<vector<int>> s, int k, string q) {
    auto pos = s;
    int m = sz(s[0]);
    int n = sz(s);
    auto up = [&]() {
        for (int i = 0; i < m; i++) {
            int p = 0;
            for (int j = 0; j < n; j++) {
                if (s[j][i] != -1) {
                    int cur = s[j][i];
                    s[p++][i] = cur;
                }
            }
            while (p < n)
                s[p++][i] = -1;
        }
    };
    auto left = [&]() {
        for (int i = 0; i < n; i++) {
            int p = 0;
            for (int j = 0; j < m; j++) {
                if (s[i][j] != -1) {
                    int cur = s[i][j];
                    s[i][p++] = cur;
                }
            }
            while (p < m)
                s[i][p++] = -1;
        }
    };
    for (int i = 0; i < sz(q); i++) {
        char x = q[i];
        if (x == 'G') {
            up();
        }
        if (x == 'D') {
            reverse(all(s));
            up();
            reverse(all(s));
        }
        if (x == 'L') {
            left();
        }
        if (x == 'P') {
            for (auto &x : s)
                reverse(all(x));
            left();
            for (auto &x : s)
                reverse(all(x));
        }
    }
    int cnt = 0;
    for (int i = 0; i < sz(s); i++) {
        for (int j = 0; j < sz(s[0]); j++) {
            if (s[i][j] != -1) {
                cnt++;
                nxt[0][s[i][j]] = pos[i][j];
            }
        }
    }
    for (int i = 1; i < 20; i++) {
        for (int j = 0; j < cnt; j++) {
            nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
        }
    }
    vector<pi> ans;
    for (int i = 0; i < cnt; i++) {
        int v = i;
        for (int j = 0; j < 20; j++) {
            if ((k >> j) & 1)
                v = nxt[j][v];
        }
        ans.push_back({i, v});
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.precision(69);
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    for (auto &x : s) {
        cin >> x;
    }
    string q;
    {
        auto dir = [&](char c) { return c == 'G' || c == 'D'; };
        int k;
        cin >> k;
        string tq;
        cin >> tq;
        for (int i = 0; i < sz(tq); i++) {
            while (sz(q) && dir(q.back()) == dir(tq[i])) {
                q.pop_back();
            }
            if (sz(q) >= 2 && q[sz(q) - 2] == tq[i])
                continue;
            q.push_back(tq[i]);
        }
        for (int i = 4; i < sz(q); i++)
            assert(q[i - 4] == q[i]);
    }
    auto up = [&]() {
        for (int i = 0; i < m; i++) {
            int p = 0;
            for (int j = 0; j < n; j++) {
                if (s[j][i] != '.') {
                    char cur = s[j][i];
                    s[p++][i] = cur;
                }
            }
            while (p < n)
                s[p++][i] = '.';
        }
    };
    auto left = [&]() {
        for (int i = 0; i < n; i++) {
            int p = 0;
            for (int j = 0; j < m; j++) {
                if (s[i][j] != '.') {
                    char cur = s[i][j];
                    s[i][p++] = cur;
                }
            }
            while (p < m)
                s[i][p++] = '.';
        }
    };
    int g = sz(q) % 4 + 4;
    for (int i = 0; i < g && i < sz(q); i++) {
        char x = q[i];
        if (x == 'G') {
            up();
        }
        if (x == 'D') {
            reverse(all(s));
            up();
            reverse(all(s));
        }
        if (x == 'L') {
            left();
        }
        if (x == 'P') {
            for (auto &x : s)
                reverse(all(x));
            left();
            for (auto &x : s)
                reverse(all(x));
        }
    }
    if (g < sz(q)) {
        int d = (sz(q) - g) / 4;
        string flag = q.substr(sz(q) - 4);
        vector<vector<int>> pos(n, vector<int>(m, -1));
        vector<char> cur;
        vector<pi> plist;
        int idx = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (s[i][j] != '.') {
                    cur.push_back(s[i][j]);
                    plist.push_back({i, j});
                    pos[i][j] = idx++;
                }
            }
        }
        auto nxt = gen(pos, d, flag);
        for (auto &[i, j] : nxt) {
            s[plist[j][0]][plist[j][1]] = cur[i];
        }
    }
    for (auto &x : s)
        cout << x << "\n";
}