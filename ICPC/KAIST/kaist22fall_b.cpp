#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int mod = 998244353;

int solve(vector<pi> a)
{
    int n = sz(a);
    vector<pi> crd;
    for (int i = 0; i < n; i++)
    {
        crd.emplace_back(a[i].first, +1);
        crd.emplace_back(a[i].second, -1);
    }
    sort(all(crd));
    int procStart = 0;
    int procEnd = 0;
    lint ret = 0;
    for (int i = 0; i + 1 < sz(crd); i++)
    {
        if (crd[i].second == +1)
            procStart++;
        if (crd[i].second == -1)
            procEnd++;
        ret += (1ll * procEnd * (n - procStart) % mod) * (crd[i + 1].first - crd[i].first) % mod;
    }
    return ret % mod;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<pi> i1(n);
    vector<pi> i2(n);
    for (int i = 0; i < n; i++)
    {
        cin >> i1[i].first >> i2[i].first;
        cin >> i1[i].second >> i2[i].second;
    }
    cout << (solve(i1) + solve(i2)) % mod << "\n";
}