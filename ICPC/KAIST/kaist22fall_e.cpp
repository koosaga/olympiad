#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int mod = 998244353;
const int MAXN = 100005;

struct bit
{
    int tree[MAXN], hap;
    void add(int x, int v)
    {
        hap += v;
        for (int i = x + 3; i < MAXN; i += i & -i)
            tree[i] += v;
    }
    int query(int x)
    {
        int ret = 0;
        for (int i = x + 3; i; i -= i & -i)
            ret += tree[i];
        return ret;
    }
    int kth(int x)
    {
        int pos = 0;
        for (int i = 16; i >= 0; i--)
        {
            if (pos + (1 << i) < MAXN && tree[pos + (1 << i)] < x)
            {
                pos += (1 << i);
                x -= tree[pos];
            }
        }
        return pos + 1 - 3;
    }
} bit[10];

string X, Y;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> X >> Y;
    int cnt[10] = {};
    for (int i = 0; i < 10; i++)
    {
        cnt[i] = count(all(X), '0' + i);
    }
    set<int> s;
    auto go = [&](int x)
    {
        if (x >= sz(Y))
            return 0;
        if (x > 0 && Y[x - 1] < Y[x])
            return 1;
        return 0;
    };
    for (int i = 0; i < sz(Y); i++)
    {
        bit[Y[i] - '0'].add(i, +1);
        if (go(i))
            s.insert(i);
    }
    int q;
    cin >> q;
    while (q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int k, v;
            cin >> k >> v;
            k--;
            if (go(k))
                s.erase(k);
            if (go(k + 1))
                s.erase(k + 1);
            bit[Y[k] - '0'].add(k, -1);
            Y[k] = '0' + v;
            if (go(k))
                s.insert(k);
            if (go(k + 1))
                s.insert(k + 1);

            bit[Y[k] - '0'].add(k, +1);
            continue;
        }
        int pos = sz(Y);
        for (int i = 0; i < 10; i++)
        {
            if (cnt[i] < bit[i].hap)
                pos = min(pos, bit[i].kth(cnt[i] + 1));
        }
        int rem[10] = {};
        auto fit = [&](int pos)
        {
            for (int j = 0; j < 10; j++)
            {
                rem[j] = cnt[j] - bit[j].query(pos - 1);
            }
            for (int z = (Y[pos] - '0') + 1; z < 10; z++)
            {
                if (rem[z] > 0)
                    return z;
            }
            return -1;
        };
        if (pos < sz(Y) && fit(pos) == -1)
        {
            if (pos > 0 && fit(pos - 1) != -1)
            {
                pos--;
            }
            else
            {
                int le = pos;
                auto newpos = s.lower_bound(pos);
                if (newpos == s.begin())
                    pos = -1;
                else
                    pos = *--newpos - 1;
                int dap = -1;
                for (int x = pos - 2; x <= pos + 2 && x < le; x++)
                {
                    if (x >= 0 && fit(x) >= 0)
                        dap = x;
                }
                pos = dap;
            }
        }
        int idx;
        cin >> idx;
        if (pos == -1)
        {
            cout << "-1\n";
            continue;
        }
        idx--;
        if (idx < pos)
        {
            cout << Y[idx] << "\n";
            continue;
        }
        int w = fit(pos);
        if (idx == pos)
            cout << w << "\n";
        else
        {
            rem[w]--;
            int needy = idx - pos;
            for (int i = 0; i < 10; i++)
            {
                needy -= rem[i];
                if (needy <= 0)
                {
                    cout << i << "\n";
                    break;
                }
            }
        }
    }
}