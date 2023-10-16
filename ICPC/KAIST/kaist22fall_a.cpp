#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 100005;
const int MAXT = 270000;

struct seg
{
    int tree[MAXT], lazy[MAXT];
    void init()
    {
        memset(tree, 0x3f, sizeof(tree));
        memset(lazy, 0, sizeof(lazy));
    }
    void lazydown(int p)
    {
        for (int i = 2 * p; i < 2 * p + 2; i++)
        {
            tree[i] += lazy[p];
            lazy[i] += lazy[p];
        }
        lazy[p] = 0;
    }
    void add(int s, int e, int ps, int pe, int p, int v)
    {
        if (e < ps || pe < s)
            return;
        if (s <= ps && pe <= e)
        {
            tree[p] += v;
            lazy[p] += v;
            return;
        }
        int pm = (ps + pe) / 2;
        lazydown(p);
        add(s, e, ps, pm, 2 * p, v);
        add(s, e, pm + 1, pe, 2 * p + 1, v);
        tree[p] = min(tree[2 * p], tree[2 * p + 1]);
    }
    int query(int s, int e, int ps, int pe, int p)
    {
        if (e < ps || pe < s)
            return 1e9;
        if (s <= ps && pe <= e)
            return tree[p];
        int pm = (ps + pe) / 2;
        lazydown(p);
        return min(query(s, e, ps, pm, 2 * p), query(s, e, pm + 1, pe, 2 * p + 1));
    }
    void upd(int pos, int s, int e, int p, int v)
    {
        if (s == e)
        {
            tree[p] = min(tree[p], v);
            return;
        }
        int m = (s + e) / 2;
        lazydown(p);
        if (pos <= m)
            upd(pos, s, m, 2 * p, v);
        else
            upd(pos, m + 1, e, 2 * p + 1, v);
        tree[p] = min(tree[2 * p], tree[2 * p + 1]);
    }
} seg;

int dp[15][MAXN];

int solve(vector<int> a, int k)
{
    vector<int> v = a;
    sort(all(v));
    v.resize(unique(all(v)) - v.begin());
    int n = sz(a);
    for (int i = 0; i < n; i++)
    {
        a[i] = lower_bound(all(v), a[i]) - v.begin();
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= k; i++)
    {
        seg.init();
        for (int j = 0; j < n; j++)
        {
            dp[i][j] = seg.query(0, a[j] - 1, 0, MAXN, 1);
            seg.add(0, a[j] - 1, 0, MAXN, 1, 1);
            seg.upd(a[j], 0, MAXN, 1, dp[i - 1][j]);
        }
    }
    return dp[k][n - 1];
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, l, k;
    cin >> n >> l >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    int ans = 0;
    for (int i = 1; i < l; i++)
    {
        if (a[i] >= a[l])
            ans++;
    }
    vector<int> seq = {a[l]};
    for (int i = l + 1; i <= n; i++)
    {
        if (a[l] >= a[i])
            continue;
        seq.push_back(a[i]);
    }
    seq.push_back(1e9 + 1557);
    ans += solve(seq, k);
    if (ans > 1e8)
        ans = -1;
    cout << ans << "\n";
}