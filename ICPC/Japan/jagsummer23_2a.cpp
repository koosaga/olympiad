#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;

const int mod = 998244353;

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

const int maxn = 1 << 20;
const int magic = 250; // threshold for sizes to run the naive algo

template <typename T> T fact(int n) {
    static T F[maxn];
    static bool init = false;
    if (!init) {
        F[0] = T(1);
        for (int i = 1; i < maxn; i++) {
            F[i] = F[i - 1] * T(i);
        }
        init = true;
    }
    return F[n];
}

template <typename T> T rfact(int n) {
    static T F[maxn];
    static bool init = false;
    if (!init) {
        F[maxn - 1] = T(1) / fact<T>(maxn - 1);
        for (int i = maxn - 2; i >= 0; i--) {
            F[i] = F[i + 1] * T(i + 1);
        }
        init = true;
    }
    return F[n];
}

mint binom(int n, int m) { return fact<mint>(n) * rfact<mint>(n - m) * rfact<mint>(m); }

lint isqr(lint n) {
    if (n < 0)
        return -1;
    lint k = (int)sqrt(n);
    if (k * k == n)
        return k;
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        lint n, k;
        cin >> n >> k;
        mint ans = 0;
        for (int i = 2; i <= k + 1; i++)
            ans += ipow(mint(i), n);
        cout << ans << "\n";
    }
}