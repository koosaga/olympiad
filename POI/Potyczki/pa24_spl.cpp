#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 696969;
const int mod = 1e9 + 7;

// I don't remember the credit of modint, but it's not mine.
// I don't remember the credit of FFT, but it's probably mine.
// Polynomial library is due to adamant:
// https://github.com/cp-algorithms/cp-algorithms-aux/blob/master/src/polynomial.cpp
// To use polynomial sqrt, need to amend sqrt for modint.

struct mint {
    int val;
    mint() { val = 0; }
    mint(const lint &v) {
        val = (-mod <= v && v < mod) ? v : v % mod;
        if (val < 0)
            val += mod;
    }

    friend ostream &operator<<(ostream &os, const mint &a) { return os << a.val; }
    friend bool operator==(const mint &a, const mint &b) { return a.val == b.val; }
    friend bool operator!=(const mint &a, const mint &b) { return !(a == b); }
    friend bool operator<(const mint &a, const mint &b) { return a.val < b.val; }

    mint operator-() const { return mint(-val); }
    mint &operator+=(const mint &m) {
        if ((val += m.val) >= mod)
            val -= mod;
        return *this;
    }
    mint &operator-=(const mint &m) {
        if ((val -= m.val) < 0)
            val += mod;
        return *this;
    }
    mint &operator*=(const mint &m) {
        val = (lint)val * m.val % mod;
        return *this;
    }
    friend mint ipow(mint a, lint p) {
        mint ans = 1;
        for (; p; p /= 2, a *= a)
            if (p & 1)
                ans *= a;
        return ans;
    }
    mint inv() const { return ipow(*this, mod - 2); }
    mint &operator/=(const mint &m) { return (*this) *= m.inv(); }

    friend mint operator+(mint a, const mint &b) { return a += b; }
    friend mint operator-(mint a, const mint &b) { return a -= b; }
    friend mint operator*(mint a, const mint &b) { return a *= b; }
    friend mint operator/(mint a, const mint &b) { return a /= b; }
    operator int64_t() const { return val; }
};

mint ans[MAXN];
mint gs(lint x) {
    if (x <= 0)
        return 0;
    return x * (x + 1) / 2;
}
vector<int> divs[MAXN];
mint delta[MAXN], ddelta[MAXN];
int n, m;

// wlog |A| >= |B|, f(A, B) = min x such that |B| >= sum floor((c_i-1)/(x-1)). (c_i = decomposition of A)
// count a, b such that f(a, b) = x
// or count a, b such that f(a, b) >= x and diff.

void dnc(int s, int e, vector<int> &seq) {
    if (s == e)
        return;
    int sum = accumulate(seq.begin() + s, seq.begin() + e + 1, 0);
    int mi = s, cur = 0;
    while (mi < e && cur * 2 < sum) {
        cur += seq[mi++];
    }
    dnc(s, mi - 1, seq);
    dnc(mi, e, seq);
    vector<vector<pi>> foo1(sum + 1), foo2(sum + 1);
    {
        vector<int> tick(sum + 2), pos(sum + 2);
        int poz = 0;
        for (int i = mi - 1; i >= s; i--) {
            for (int j = 1; j <= seq[i]; j++) {
                if (j > 1) {
                    for (auto &x : divs[j - 1]) {
                        tick[x + 1]++;
                        foo1[x + 1].push_back({tick[x + 1] - 1, poz - pos[x + 1]});
                        pos[x + 1] = poz;
                    }
                }
                poz++;
            }
        }
        for (int i = 2; i <= sum; i++)
            foo1[i].push_back({tick[i], poz - pos[i]});
    }
    {
        vector<int> tick(sum + 2), pos(sum + 2);
        int poz = 0;
        for (int i = mi; i <= e; i++) {
            for (int j = 1; j <= seq[i]; j++) {
                if (j > 1) {
                    for (auto &x : divs[j - 1]) {
                        tick[x + 1]++;
                        foo2[x + 1].push_back({tick[x + 1] - 1, poz - pos[x + 1]});
                        pos[x + 1] = poz;
                    }
                }
                poz++;
            }
        }
        for (int i = 2; i <= sum; i++)
            foo2[i].push_back({tick[i], poz - pos[i]});
    }
    delta[sum + 1] += gs(m + 1) * mint(cur) * mint(sum - cur);
    for (int x = 2; x <= sum; x++) {
        mint j1sum = 0;
        mint j0j1sum = 0;
        mint j0j0j1sum = 0;
        for (auto &[j0, j1] : foo2[x]) {
            j1sum += mint(j1);
            j0j1sum += mint(j0) * mint(j1);
            j0j0j1sum += mint(j0) * mint(j0) * mint(j1);
        }
        int t = sz(foo2[x]);
        for (int i = 0; i < sz(foo1[x]); i++) {
            while (t > 0 && foo1[x][i][0] + foo2[x][t - 1][0] > m) {
                t--;
                auto [j0, j1] = foo2[x][t];
                j1sum -= mint(j1);
                j0j1sum -= mint(j0) * mint(j1);
                j0j0j1sum -= mint(j0) * mint(j0) * mint(j1);
            }
            ans[x] += mint(m + 1 - foo1[x][i][0]) * mint(m + 2 - foo1[x][i][0]) * mint(foo1[x][i][1]) * j1sum * mint((mod + 1) / 2);
            ans[x] -= mint(m + 2 - foo1[x][i][0]) * mint(foo1[x][i][1]) * j0j1sum * mint((mod + 1) / 2);
            ans[x] -= mint(m + 1 - foo1[x][i][0]) * j0j1sum * mint(foo1[x][i][1]) * mint((mod + 1) / 2);
            ans[x] += j0j0j1sum * mint(foo1[x][i][1]) * mint((mod + 1) / 2);
        }
    }
}

void solve(vector<int> a, int _m, bool sames) {
    m = _m;
    n = sz(a);
    if (sames) {
        for (int i = 2; i <= n + m; i++)
            ans[i] += mint(1ll * n * m);
    }
    if (sz(a) == 1)
        return;
    vector<int> seq = {0};
    for (int i = 1; i < sz(a); i++) {
        if (i >= 2 && (max(a[i - 2], a[i]) < a[i - 1] || min(a[i - 2], a[i]) > a[i - 1])) {
            seq.push_back(1);
        } else {
            seq.back()++;
        }
    }
    for (int i = 0; i < sz(seq); i++) {
        for (int j = 1; j <= seq[i]; j++) {
            delta[j + 1] -= mint(m + 1) * mint(seq[i] + 1 - j);
        }
    }
    {
        vector<array<int, 3>> stk;
        int sum = 0; /*
         for (auto &z : seq)
             cout << z;
         cout << endl;*/
        for (int i = 0; i < sz(seq); i++) {
            sum += seq[i];
            array<int, 3> tp = {seq[i], 1, sum};
            while (sz(stk) && stk.back()[0] <= tp[0]) {
                mint z = mint(m + 1) * mint(stk.back()[1]);
                if (seq[i] <= stk.back()[0]) {
                    delta[stk.back()[0] + 1] -= mint(seq[i]) * z;
                } else {
                    delta[stk.back()[0] + 1] -= mint(stk.back()[0]) * z;
                    ddelta[stk.back()[0] + 2] -= z;
                    ddelta[seq[i] + 2] += z;
                }
                delta[stk.back()[0] + 1] -= mint(m + 1) * mint(stk.back()[1]) * mint(sum - seq[i] - stk.back()[2]);
                tp[1] += stk.back()[1];
                stk.pop_back();
            }
            stk.push_back(tp);
            for (int j = seq[i] - 1; j; j--)
                stk.push_back({j, 1, sum});
        }
        for (auto &[v, c, p] : stk) {
            delta[v + 1] -= mint(m + 1) * mint(c) * mint(sum - p);
        }
    }
    {
        auto sum = [&](int x) { return mint(1ll * x * (x + 1) / 2); };
        for (int i = 0; i < sz(seq); i++) {
            for (int j = 1; j <= seq[i]; j++) {
                delta[j + 1] += mint(seq[i] + 1 - j) * gs(m + 1);
            }
            for (int x = 2; x <= seq[i]; x++) {
                for (int d = 1; d <= (seq[i] - 1) / (x - 1); d++) {
                    ans[x] += gs(m + 1 - d) * (-sum(seq[i] - min(seq[i], (d + 1) * (x - 1))) + sum(seq[i] - d * (x - 1)));
                }
            }
        }
    }
    dnc(0, sz(seq) - 1, seq);
    mint sum = 0;
    for (int y = 1; y <= n - 1; y++) {
        sum += gs(m - sames - y) * mint(n - y);
    }
    for (int i = 1; i <= n + m; i++) {
        ddelta[i] += ddelta[i - 1];
        delta[i] += ddelta[i];
    }
    for (int x = 1; x <= n + m; x++) {
        delta[x] += delta[x - 1];
        ans[x] += delta[x];
    }
    for (int x = 1; x <= n + m; x++)
        delta[x] = ddelta[x] = 0;
    for (int x = 2; x <= n + m; x++)
        ans[x] -= sum;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    for (int i = 1; i < MAXN; i++) {
        for (int j = i; j < MAXN; j += i) {
            divs[j].push_back(i);
        }
    }
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto &x : a)
        cin >> x;
    for (auto &y : b)
        cin >> y;
    solve(a, sz(b), true);
    solve(b, sz(a), false);
    for (int i = 1; i <= n + m; i++)
        cout << ans[i] - ans[i - 1] << (i == n + m ? "\n" : " ");
}