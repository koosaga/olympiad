#include <bits/stdc++.h>
using namespace std;


template <typename T> T mod_inv_in_range(T a, T m) {
    // assert(0 <= a && a < m);
    T x = a, y = m;
    // coeff of a in x and y
    T vx = 1, vy = 0;
    while (x) {
        T k = y / x;
        y %= x;
        vy -= k * vx;
        std::swap(x, y);
        std::swap(vx, vy);
    }
    assert(y == 1);
    return vy < 0 ? m + vy : vy;
}

template <typename T> struct extended_gcd_result {
    T gcd;
    T coeff_a, coeff_b;
};
template <typename T> extended_gcd_result<T> extended_gcd(T a, T b) {
    T x = a, y = b;
    // coeff of a and b in x and y
    T ax = 1, ay = 0;
    T bx = 0, by = 1;
    while (x) {
        T k = y / x;
        y %= x;
        ay -= k * ax;
        by -= k * bx;
        std::swap(x, y);
        std::swap(ax, ay);
        std::swap(bx, by);
    }
    return {y, ay, by};
}

template <typename T> T mod_inv(T a, T m) {
    a %= m;
    a = a < 0 ? a + m : a;
    return mod_inv_in_range(a, m);
}

template <int MOD_> struct modnum {
    static constexpr int MOD = MOD_;
    static_assert(MOD_ > 0, "MOD must be positive");

private:
    int v;

public:

    modnum() : v(0) {}
    modnum(int64_t v_) : v(int(v_ % MOD)) { if (v < 0) v += MOD; }
    explicit operator int() const { return v; }
    friend std::ostream& operator << (std::ostream& out, const modnum& n) { return out << int(n); }
    friend std::istream& operator >> (std::istream& in, modnum& n) { int64_t v_; in >> v_; n = modnum(v_); return in; }

    friend bool operator == (const modnum& a, const modnum& b) { return a.v == b.v; }
    friend bool operator != (const modnum& a, const modnum& b) { return a.v != b.v; }

    modnum inv() const {
        modnum res;
        res.v = mod_inv_in_range(v, MOD);
        return res;
    }
    friend modnum inv(const modnum& m) { return m.inv(); }
    modnum neg() const {
        modnum res;
        res.v = v ? MOD-v : 0;
        return res;
    }
    friend modnum neg(const modnum& m) { return m.neg(); }

    modnum operator- () const {
        return neg();
    }
    modnum operator+ () const {
        return modnum(*this);
    }

    modnum& operator ++ () {
        v ++;
        if (v == MOD) v = 0;
        return *this;
    }
    modnum& operator -- () {
        if (v == 0) v = MOD;
        v --;
        return *this;
    }
    modnum& operator += (const modnum& o) {
        v -= MOD-o.v;
        v = (v < 0) ? v + MOD : v;
        return *this;
    }
    modnum& operator -= (const modnum& o) {
        v -= o.v;
        v = (v < 0) ? v + MOD : v;
        return *this;
    }
    modnum& operator *= (const modnum& o) {
        v = int(int64_t(v) * int64_t(o.v) % MOD);
        return *this;
    }
    modnum& operator /= (const modnum& o) {
        return *this *= o.inv();
    }

    friend modnum operator ++ (modnum& a, int) { modnum r = a; ++a; return r; }
    friend modnum operator -- (modnum& a, int) { modnum r = a; --a; return r; }
    friend modnum operator + (const modnum& a, const modnum& b) { return modnum(a) += b; }
    friend modnum operator - (const modnum& a, const modnum& b) { return modnum(a) -= b; }
    friend modnum operator * (const modnum& a, const modnum& b) { return modnum(a) *= b; }
    friend modnum operator / (const modnum& a, const modnum& b) { return modnum(a) /= b; }
};

template <typename T> T pow(T a, long long b) {
    assert(b >= 0);
    T r = 1; while (b) { if (b & 1) r *= a; b >>= 1; a *= a; } return r;
}

using num = modnum<998244353>;

vector<num> fact, ifact;

void init(){
    int N = 11000;
    fact.resize(N);
    fact[0] = 1;
    for(int i = 1; i < N; i++) fact[i] = i * fact[i-1];
    ifact.resize(N);
    ifact.back() = 1 / fact.back();
    for(int i = N - 1; i > 0; i--) ifact[i-1] = i * ifact[i];
}

num ncr(int n, int k){
    if(k < 0 || k > n) return 0;
    return fact[n] * ifact[k] * ifact[n-k];
}
int main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    init();
    int N6, N7;
    cin >> N6 >> N7;
    N6 /= 6;
    N7 /= 7;
    int S = 1 << (3 * 6);
    vector<num> dp(S * 7);
    vector<num> pf(7);
    for(int c = 0; c <= 6; c++){
        for(int l = 0; l <= 6; l++){
            pf[c] += pow(ncr(c, l), N7);
        }
    }
    vector<num> f(7);
    for(int c = 0; c <= 6; c++){
        for(int pie = 0; pie <= c; pie++){
            f[c] += ncr(c, pie) * ((pie & 1) ? -1 : 1) * pow(num(2), pie) * pf[c-pie];
        }
    }
    vector<num> pg(8);
    for(int c = 0; c <= 7; c++){
        for(int l = 0; l <= 7; l++){
            pg[c] += pow(ncr(c, l), N6);
        }
    }
    vector<num> g(8);
    for(int c = 0; c <= 7; c++){
        for(int pie = 0; pie <= c; pie++){
            g[c] += ncr(c, pie) * ((pie & 1) ? -1 : 1) * pow(num(2), pie) * pg[c-pie];
        }
    }

    dp[0] = 1;
    for(int r = 0; r < 7; r++){
        for(int c = 0; c < 6; c++){
            vector<num> ndp(S * 7, 0);
            for(int msk = 0; msk < S * 7; msk++){
                ndp[msk] += dp[msk] * 2;
                if(msk + S < S * 7) ndp[msk + S] += dp[msk];
                if(((msk >> (3*c)) & 7) < 7){
                    ndp[msk + (1 << (3*c))] += dp[msk];
                }
            }
            dp = ndp;
        }
        vector<num> ndp(S*7, 0);
        for(int msk = 0; msk < S * 7; msk++){
            ndp[msk % S] += dp[msk] * f[msk / S];
        }
        dp = ndp;
    }
    num ans = 0;
    for(int msk = 0; msk < S; msk++){
        num cur = dp[msk];
        for(int c = 0; c < 6; c++){
            int b = (msk >> (c * 3)) & 7;
            cur *= g[b];
        }
        ans += cur;
    }
    cout << ans << '\n';
}