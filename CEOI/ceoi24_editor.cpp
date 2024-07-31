#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 1000005;

struct node {
    lint dist;
    int pos, type;
    bool operator<(const node &nd) const { return dist > nd.dist; }
    bool operator>(const node &nd) const { return dist < nd.dist; }
};

lint dist[MAXN][2];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    pi s, e;
    cin >> s[0] >> s[1] >> e[0] >> e[1];
    s[0]--;
    s[1]--;
    e[0]--;
    e[1]--;
    vector<int> l(n), r(n), a(n);
    for (auto &x : a)
        cin >> x;
    {
        vector<int> stk;
        for (int i = 0; i < n; i++) {
            while (sz(stk) && a[stk.back()] > a[i])
                stk.pop_back();
            l[i] = (sz(stk) ? stk.back() : -1);
            stk.push_back(i);
        }
        stk.clear();
        for (int i = n - 1; i >= 0; i--) {
            while (sz(stk) && a[stk.back()] > a[i])
                stk.pop_back();
            r[i] = (sz(stk) ? stk.back() : n);
            stk.push_back(i);
        }
    }
    lint ans = 1e18;
    if (s[0] == e[0])
        ans = min(ans, abs(e[1] - s[1]));
    else {
        int l = min(s[0], e[0]);
        int r = max(s[0], e[0]);
        if (*min_element(a.begin() + l, a.begin() + r + 1) >= min(s[1], e[1])) {
            ans = min(ans, abs(s[0] - e[0]) + abs(s[1] - e[1]));
        }
    }
    priority_queue<node> pq;
    auto enq = [&](int x, int p, lint d) {
        if (dist[x][p] > d) {
            dist[x][p] = d;
            pq.push({d, x, p});
        }
    };
    memset(dist, 0x3f, sizeof(dist));
    {
        enq(s[0], 0, s[1]);
        int cur = 2e9;
        for (int i = s[0]; i >= 0; i--) {
            cur = min(cur, a[i]);
            enq(i, 1, abs(i - s[0]) + max(0ll, a[i] - s[1]));
            if (cur < s[1])
                break;
        }
        cur = 2e9;
        for (int i = s[0]; i < n; i++) {
            cur = min(cur, a[i]);
            enq(i, 1, abs(i - s[0]) + max(0ll, a[i] - s[1]));
            if (cur < s[1])
                break;
        }
    }
    while (sz(pq)) {
        auto nd = pq.top();
        pq.pop();
        if (dist[nd.pos][nd.type] != nd.dist)
            continue;
        if (nd.type == 0) {
            if (nd.pos > 0) {
                enq(nd.pos - 1, 0, nd.dist + 1);
                enq(nd.pos - 1, 1, nd.dist + 1);
            }
            if (nd.pos + 1 < n)
                enq(nd.pos + 1, 0, nd.dist + 1);
            enq(nd.pos, 1, nd.dist + a[nd.pos]);
        }
        if (nd.type == 1) {
            enq(nd.pos, 0, nd.dist + a[nd.pos]);
            if (nd.pos + 1 < n)
                enq(nd.pos + 1, 0, nd.dist + 1);
            for (int x = nd.pos - 1; x >= 0; x = l[x]) {
                enq(x, 1, nd.dist + nd.pos - x + max(0, a[x] - a[nd.pos]));
                if (a[x] <= a[nd.pos])
                    break;
            }
            for (int x = nd.pos + 1; x < n; x = r[x]) {
                enq(x, 1, nd.dist + x - nd.pos + max(0, a[x] - a[nd.pos]));
                if (a[x] <= a[nd.pos])
                    break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        //  cout << dist[i][0] << " " << dist[i][1] << endl;
        ans = min(ans, dist[i][0] + e[1] + abs(e[0] - i));
    }
    {
        int cur = 2e9;
        for (int i = e[0]; i >= 0; i--) {
            cur = min(cur, a[i]);
            ans = min(ans, dist[i][1] + abs(a[i] - e[1]) + abs(e[0] - i));
            if (cur < e[1])
                break;
        }
        cur = 2e9;
        for (int i = e[0]; i < n; i++) {
            cur = min(cur, a[i]);
            ans = min(ans, dist[i][1] + abs(a[i] - e[1]) + abs(e[0] - i));
            if (cur < e[1])
                break;
        }
    }

    cout << ans << "\n";
}