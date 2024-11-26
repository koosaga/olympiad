#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
#define cr(v, n) (v).clear(), (v).resize(n);
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
struct disj {
    vector<int> pa, sz, cnt;
    void init(int n) {
        pa.clear();
        pa.resize(n);
        iota(all(pa), 0);
        cr(sz, n);
        cr(cnt, n);
        fill(all(sz), 1);
    }
    void set(int x, int v) { cnt[find(x)] += v; }
    int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
    bool uni(int p, int q) {
        p = find(p);
        q = find(q);
        if (p == q)
            return 0;
        pa[q] = p;
        sz[p] += sz[q];
        cnt[p] += cnt[q];
        return 1;
    }
    mint query(int p) {
        p = find(p);
        return mint(1ll * cnt[p] * (sz[p] - cnt[p])) / mint(sz[p]);
    }
} disj;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<vector<int>> p(k, vector<int>(n));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            cin >> p[i][j];
            p[i][j]--;
        }
    }
    disj.init(n * (n - 1));
    auto get = [&](int x, int y) { return x * (n - 1) + (y - (y > x)); };
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            disj.set(get(i, j), +1);
        }
    }
    for (int it = 0; it < 42; it++) {
        vector<int> gen(n);
        iota(all(gen), 0);
        for (int j = 0; j < k; j++) {
            if (rand() % 2) {
                for (int x = 0; x < n; x++)
                    gen[x] = p[j][gen[x]];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    disj.uni(get(i, j), get(gen[i], gen[j]));
                }
            }
        }
    }
    mint ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && disj.find(get(i, j)) == get(i, j)) {
                ans += disj.query(get(i, j));
            }
        }
    }
    cout << ans << "\n";
}