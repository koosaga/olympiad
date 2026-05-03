#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005, MAXM = 100005;

struct bpm {
    vector<int> gph[MAXN];
    int dis[MAXN], l[MAXN], r[MAXM], vis[MAXN];
    void clear(int n) {
        for (int i = 0; i < n; i++)
            gph[i].clear();
    }
    void add_edge(int l, int r) { gph[l].push_back(r); }
    bool bfs(int n) {
        queue<int> que;
        bool ok = 0;
        memset(dis, 0, sizeof(int) * n);
        for (int i = 0; i < n; i++) {
            if (l[i] == -1 && !dis[i]) {
                que.push(i);
                dis[i] = 1;
            }
        }
        while (!que.empty()) {
            int x = que.front();
            que.pop();
            for (auto &i : gph[x]) {
                if (r[i] == -1)
                    ok = 1;
                else if (!dis[r[i]]) {
                    dis[r[i]] = dis[x] + 1;
                    que.push(r[i]);
                }
            }
        }
        return ok;
    }
    bool dfs(int x) {
        if (vis[x])
            return 0;
        vis[x] = 1;
        for (auto &i : gph[x]) {
            if (r[i] == -1 || (!vis[r[i]] && dis[r[i]] == dis[x] + 1 && dfs(r[i]))) {
                l[x] = i;
                r[i] = x;
                return 1;
            }
        }
        return 0;
    }
    int match(int n) {
        memset(l, -1, sizeof(int) * n);
        memset(r, -1, sizeof(int) * n);
        int ret = 0;
        while (bfs(n)) {
            memset(vis, 0, sizeof(int) * n);
            for (int i = 0; i < n; i++)
                if (l[i] == -1 && dfs(i))
                    ret++;
        }
        return ret;
    }
} bpm;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.precision(69);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        bpm.clear(n);
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            a[x - 1] = i;
        }
        if (n == 1) {
            cout << "Impossible\n";
            continue;
        }
        vector<pi> diff(n);
        for (int i = 0; i < n; i++) {
            diff[(a[i] - i + n) % n][0]++;
            diff[i][1] = i;
        }
        sort(all(diff));
        for (int i = 0; i < 6 && i < n; i++) {
            int D = diff[i][1];
            if (D == 0)
                continue;
            for (int j = 0; j < n; j++) {
                if ((j + D) % n == a[j])
                    continue;
                bpm.add_edge(j, (j + D) % n);
            }
        }
        for (int i = 0; i < 2 && i < n; i++) {
            int D = diff[i][1];
            if (D == 0)
                continue;
            for (int j = 0; j < n; j++) {
                if ((j + D) % n == a[j]) {
                    for (int k = 0; k < n; k++) {
                        if (a[k] != a[j] && k != a[j])
                            bpm.add_edge(k, a[j]);
                    }
                }
            }
        }
        if (bpm.match(n) != n) {
            cout << "Impossible\n";
            continue;
        }
        cout << "Possible\n";
        vector<int> p(n), q(n);
        for (int i = 0; i < n; i++) {
            q[i] = bpm.l[i];
            p[q[i]] = a[i];
        }
        for (int i = 0; i < n; i++)
            cout << p[i] + 1 << " ";
        cout << "\n";
        for (int i = 0; i < n; i++)
            cout << q[i] + 1 << " ";
        cout << "\n";
    }
}