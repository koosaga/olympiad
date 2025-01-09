#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 500005;
vector<pi> gph[MAXN];

vector<lint> dijkstra(int s, int n) {
    priority_queue<pi, vector<pi>, greater<pi>> pq;
    vector<lint> dist(n, 1e18);
    auto enq = [&](int x, lint v) {
        if (dist[x] > v) {
            dist[x] = v;
            pq.push({v, x});
        }
    };
    enq(s, 0);
    while (sz(pq)) {
        auto x = pq.top();
        pq.pop();
        if (dist[x[1]] != x[0])
            continue;
        for (auto &[w, y] : gph[x[1]])
            enq(y, w + x[0]);
    }
    return dist;
}

void add_edge(int s, int e, lint x) { gph[s].push_back({x, e}); }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<lint> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < m; i++) {
        int s, e, x;
        cin >> s >> e >> x;
        add_edge(s - 1, e - 1, x);
        add_edge(e - 1, s - 1, x);
    }
    auto d = dijkstra(0, n);
    lint ans = 0;
    for (int i = 0; i < n; i++)
        ans += d[i] * a[i];
    cout << ans << "\n";
}
