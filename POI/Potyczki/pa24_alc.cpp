#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

vector<array<int, 3>> solve(int n, vector<pi> edges) {
    vector<set<int>> gph(n);
    vector<int> par(n), dist(n, 1e9);
    for (auto &[x, y] : edges) {
        gph[x].insert(y);
        gph[y].insert(x);
    }
    vector<array<int, 3>> sol;
    auto edge = [&](int x, int y) { return gph[x].count(y) && gph[y].count(x); };
    auto op_add = [&](int x, int y, int c) {
        assert(!edge(x, y));
        assert(edge(x, c));
        assert(edge(y, c));
        assert(x != y);
        sol.push_back({+1, x, y});
        gph[x].insert(y);
        gph[y].insert(x);
    };
    auto op_del = [&](int x, int y, int c) {
        assert(edge(x, y));
        assert(edge(x, c));
        assert(edge(y, c));
        assert(x != y);
        sol.push_back({-1, x, y});
        gph[x].erase(y);
        gph[y].erase(x);
    };
    dist[0] = 0;
    queue<int> que;
    que.push(0);
    vector<int> ord;
    while (sz(que)) {
        int x = que.front();
        que.pop();
        ord.push_back(x);
        for (auto &y : gph[x]) {
            if (dist[y] > dist[x] + 1) {
                dist[y] = dist[x] + 1;
                par[y] = x;
                que.push(y);
            }
        }
    }
    for (auto &x : ord) {
        if (dist[x] >= 2 && !edge(0, x)) {
            op_add(0, x, par[x]);
        }
    }
    for (int i = 1; i < n; i++) {
        vector<int> todo;
        for (auto &j : gph[i]) {
            if (j > i)
                todo.push_back(j);
        }
        for (auto &z : todo)
            op_del(i, z, 0);
    }
    assert(sz(gph[0]) == n - 1);
    for (int i = 1; i < n; i++) {
        assert(sz(gph[i]) == 1);
        assert(gph[i].count(0));
    }
    return sol;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<pi> edges[2];
    for (int i = 0; i < 2; i++) {
        int m;
        cin >> m;
        edges[i].resize(m);
        for (auto &[x, y] : edges[i]) {
            cin >> x >> y;
            x--;
            y--;
        }
    }
    auto s1 = solve(n, edges[0]);
    auto s2 = solve(n, edges[1]);
    reverse(all(s2));
    for (auto &v : s2) {
        v[0] *= -1;
        s1.push_back(v);
    }
    cout << sz(s1) << "\n";
    for (auto &[x, y, z] : s1) {
        if (x > 0)
            cout << "+ ";
        else
            cout << "- ";
        cout << y + 1 << " " << z + 1 << "\n";
    }
}