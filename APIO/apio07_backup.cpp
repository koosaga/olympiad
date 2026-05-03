#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

vector<lint> backup(vector<lint> a) {
    sort(all(a));
    set<pi> s;
    priority_queue<pi, vector<pi>, greater<pi>> pq;
    for (int i = 1; i < sz(a); i++) {
        s.insert({i, a[i] - a[i - 1]});
        pq.push({a[i] - a[i - 1], i});
    }
    vector<lint> dap = {0};
    while (sz(pq)) {
        auto [d, p] = pq.top();
        pq.pop();
        if (s.count({p, d}) == 0)
            continue;
        lint cost = dap.back() + d;
        dap.push_back(cost);
        s.erase({p, d});
        auto it = s.lower_bound(pi{p, -1});
        d = -d;
        int merged = 0;
        if (it != s.end()) {
            d += (*it)[1];
            s.erase(it);
            merged++;
        }
        it = s.lower_bound(pi{p, -1});
        if (it != s.begin()) {
            it--;
            d += (*it)[1];
            p = (*it)[0];
            s.erase(it);
            merged++;
        }
        if (merged == 2) {
            s.insert({p, d});
            pq.push({d, p});
        }
    }
    return dap;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<lint> pos(n);
    for (auto &x : pos)
        cin >> x;
    cout << backup(pos)[k] << "\n";
}