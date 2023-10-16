#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int mod = 998244353;

set<pi> s;
lint ans;

lint f(lint u, lint v)
{
    lint S = v - u + 1;
    return S * (S + 1) / 2;
}

void INSERT(int x)
{
    int gs = x, ge = x;
    auto it = s.lower_bound(pi(x + 1, -1));
    if (it != s.end() && it->first == x + 1)
    {
        ge = it->second;
        ans -= f(it->first, it->second);
        s.erase(it);
    }
    it = s.lower_bound(pi(x, -1));
    if (it != s.begin() && prev(it)->second == x - 1)
    {
        it--;
        gs = it->first;
        ans -= f(it->first, it->second);
        s.erase(it);
    }
    ans += f(gs, ge);
    s.emplace(gs, ge);
}

void ERASE(int x)
{
    int gs = x, ge = x;
    auto it = --s.lower_bound(pi(x + 1, -1));
    ans -= f(it->first, it->second);
    gs = it->first;
    ge = it->second;
    s.erase(it);
    if (gs < x)
    {
        ans += f(gs, x - 1);
        s.emplace(gs, x - 1);
    }
    if (x < ge)
    {
        ans += f(x + 1, ge);
        s.emplace(x + 1, ge);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int q;
    cin >> q;
    while (q--)
    {
        int t, x;
        cin >> t >> x;
        if (t == 1)
            INSERT(x);
        else
            ERASE(x);
        cout << ans << "\n";
    }
}