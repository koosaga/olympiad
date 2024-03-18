#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 500005;

const int mod = 1e9 + 7; // 1e9 + 7;//993244853;

// I don't remember the credit of modint, but it's not mine.
// I don't remember the credit of FFT, but it's probably mine.
// Polynomial library is due to adamant:
// https://github.com/cp-algorithms/cp-algorithms-aux/blob/master/src/polynomial.cpp
// To use polynomial sqrt, need to amend sqrt for modint.

struct bit {
    int tree[MAXN];
    void add(int x, int v) {
        for (int i = x + 2; i < MAXN; i += i & -i)
            tree[i] += v;
    }
    int query(int x) {
        int ret = 0;
        for (int i = x + 2; i; i -= i & -i)
            ret += tree[i];
        return ret;
    }
} bit;
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

vector<int> gph[MAXN], rev[MAXN];
pi p[MAXN];
int vis[MAXN], piv;
int label[MAXN], reach[MAXN];

void dfs1(int x) {
    if (vis[x])
        return;
    vis[x] = 1;
    for (auto &y : gph[x]) {
        dfs1(y);
    }
    p[x][0] = --piv;
}

void dfs2(int x) {
    if (vis[x])
        return;
    vis[x] = 1;
    for (auto &y : gph[x])
        dfs2(y);
    p[x][1] = --piv;
}

lint inv[MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    inv[1] = 1;
    for (int a = 2; a < MAXN; ++a)
        inv[a] = mod - (long long)(mod / a) * inv[mod % a] % mod;
    vector<pi> a(n);
    for (auto &[l, r] : a) {
        cin >> l >> r;
        l--;
        r--;
    }
    vector<pi> mode(2 * n);
    for (int i = 0; i < n; i++) {
        mode[a[i][0]] = pi{i + 1, +1};
        mode[a[i][1]] = pi{i + 1, -1};
    }
    vector<int> pospar(n + 1, n + 1);
    set<int> s = {0};
    for (int i = 0; i < 2 * n; i++) {
        if (mode[i][1] == +1) {
            {
                auto it = s.upper_bound(mode[i][0]);
                if (it != s.end())
                    pospar[mode[i][0]] = *it;
            }
            auto it = --s.lower_bound(mode[i][0]);
            gph[*it].push_back(mode[i][0]);
            s.insert(mode[i][0]);
        } else {
            auto it = --s.lower_bound(mode[i][0]);
            gph[*it].push_back(mode[i][0]);
            s.erase(mode[i][0]);
        }
    }
    vector<int> faker(n + 5);
    for (int i = 1; i <= n; i++) {
        if (sz(gph[i]) == 0 && pospar[i]) {
            gph[i].push_back(pospar[i]);
            faker[i] = 1;
        }
    }
    for (int i = 0; i < n + 2; i++)
        reverse(all(gph[i]));
    memset(vis, 0, sizeof(vis));
    piv = n + 2;
    dfs1(0);
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n + 2; i++)
        reverse(all(gph[i]));
    piv = n + 2;
    dfs2(0);
    vector<int> ord(n + 2);
    iota(all(ord), 0);
    sort(all(ord), [&](const int &a, const int &b) { return p[a][0] > p[b][0]; });
    int cnt = 0;
    for (auto &x : ord) {
        bit.add(p[x][1], 1);
        cnt++;
        reach[x] = cnt - bit.query(p[x][1] - 1);
    }
    memset(label, -1, sizeof(label));
    for (int i = n; i >= 0; i--) {
        label[i] = i;
        if (faker[i])
            continue;
        for (auto &j : gph[i]) {
            label[i] = max(label[i], label[j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        reach[i] -= reach[pospar[label[i]]];
    }
    mint ans = 0;
    // for (int i = 1; i <= n; i++)
    // cout << reach[i] << endl;
    for (int i = 1; i <= n; i++)
        ans += mint(inv[reach[i]]);
    cout << ans << endl;
}