#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 100005;

int tree[MAXN];

void upd(int x, int v) {
    for (int i = x + 2; i; i -= i & -i)
        tree[i] = max(tree[i], v);
}

int query(int x) {
    int ret = 0;
    for (int i = x + 2; i < MAXN; i += i & -i)
        ret = max(ret, tree[i]);
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    vector<vector<int>> divs(MAXN);
    for (int i = 0; i < n; i++) {
        for (int j = 1; j * j <= a[i]; j++) {
            if (a[i] % j == 0) {
                divs[j].push_back(i);
                if (j * j != a[i])
                    divs[a[i] / j].push_back(i);
            }
        }
    }
    vector<vector<pi>> events(n), queries(n);
    for (int i = 2; i < MAXN; i++) {
        for (int j = 1; j < sz(divs[i]); j++) {
            int l = divs[i][j - 1], r = divs[i][j];
            if (gcd(a[l], a[r]) == i) {
                events[r].push_back({l, i});
            }
        }
    }
    int q;
    cin >> q;
    vector<int> ans(q, 1);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        queries[r - 1].push_back({l - 1, i});
    }
    for (int i = 0; i < n; i++) {
        for (auto &[pos, val] : events[i]) {
            upd(pos, val);
        }
        for (auto &[j, p] : queries[i]) {
            ans[p] = max(ans[p], query(j));
        }
    }
    for (int i = 0; i < q; i++)
        cout << ans[i] << "\n";
}
