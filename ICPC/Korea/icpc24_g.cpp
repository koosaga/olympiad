#include <bits/stdc++.h>
using namespace std;
using lint = long long;
// using pi = array<lint, 2>;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

const int MAXN = 200005;

int nxt[MAXN][26];
int par[MAXN], len[MAXN], slink[MAXN], ptr[MAXN], diff[MAXN], series[MAXN], piv;
void clear(int n = MAXN) {
    memset(par, 0, sizeof(int) * n);
    memset(len, 0, sizeof(int) * n);
    memset(slink, 0, sizeof(int) * n);
    memset(nxt, 0, sizeof(int) * 26 * n);
    piv = 0;
}
void init(int n, char *a) {
    par[0] = 0;
    par[1] = 1;
    a[0] = -1;
    len[0] = -1;
    piv = 1;
    int cur = 1;
    for (int i = 1; i <= n; i++) {
        while (a[i] != a[i - len[cur] - 1])
            cur = slink[cur];
        if (!nxt[cur][a[i]]) {
            nxt[cur][a[i]] = ++piv;
            par[piv] = cur;
            len[piv] = len[cur] + 2;
            int lnk = slink[cur];
            while (a[i] != a[i - len[lnk] - 1]) {
                lnk = slink[lnk];
            }
            if (nxt[lnk][a[i]])
                lnk = nxt[lnk][a[i]];
            if (len[piv] == 1 || lnk == 0)
                lnk = 1;
            slink[piv] = lnk;
            diff[piv] = len[piv] - len[lnk];
            if (diff[piv] == diff[lnk])
                series[piv] = series[lnk];
            else
                series[piv] = piv;
        }
        cur = nxt[cur][a[i]];
        ptr[i] = cur;
    }
}
int query(int s, int e) {
    int pos = ptr[e];
    while (len[pos] >= e - s + 1) {
        if (len[pos] % diff[pos] == (e - s + 1) % diff[pos] && len[series[pos]] <= e - s + 1)
            return true;
        pos = series[pos];
        pos = slink[pos];
    }
    return false;
}
vector<pi> minimum_partition(int n) { // (odd min, even min)
    vector<pi> dp(n + 1);
    vector<pi> series_ans(n + 10);
    dp[0] = pi(1e9 + 1, 0);
    for (int i = 1; i <= n; i++) {
        dp[i] = pi(1e9 + 1, 1e9);
        for (int j = ptr[i]; len[j] > 0;) {
            int slv = slink[series[j]];
            series_ans[j] = dp[i - (len[slv] + diff[j])];
            if (diff[j] == diff[slink[j]]) {
                series_ans[j].first = min(series_ans[j].first, series_ans[slink[j]].first);
                series_ans[j].second = min(series_ans[j].second, series_ans[slink[j]].second);
            }
            auto val = series_ans[j];
            dp[i].first = min(dp[i].first, val.second + 1);
            dp[i].second = min(dp[i].second, val.first + 1);
            j = slv;
        }
    }
    return dp;
}

char s[MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    string tmp;
    cin >> tmp;
    for (int i = 1; i <= n; i++)
        s[i] = tmp[i - 1];
    init(n, s);
    auto v = minimum_partition(n).back();
    cout << min(v.first, v.second) << "\n";
}
