//https://judge.yosupo.jp/submission/23481
// p need to be prime. 
// find solution to x^k == a mod p

lint mod;

struct mint {
    lint val;
    mint() { val = 0; }
    mint(const lint& v) {
        val = (-mod <= v && v < mod) ? v : v % mod;
        if (val < 0) val += mod;
    }

    friend ostream& operator<<(ostream& os, const mint& a) { return os << a.val; }
    friend bool operator==(const mint& a, const mint& b) { return a.val == b.val; }
    friend bool operator!=(const mint& a, const mint& b) { return !(a == b); }
    friend bool operator<(const mint& a, const mint& b) { return a.val < b.val; }

    mint operator-() const { return mint(-val); }
    mint& operator+=(const mint& m) { if ((val += m.val) >= mod) val -= mod; return *this; }
    mint& operator-=(const mint& m) { if ((val -= m.val) < 0) val += mod; return *this; }
    mint& operator*=(const mint& m) { val = (__int128)val*m.val%mod; return *this; }
    friend mint ipow(mint a, lint p) {
        mint ans = 1; for (; p; p /= 2, a *= a) if (p&1) ans *= a;
        return ans;
    }
    friend mint inv(const mint& a) { assert(a.val); return ipow(a, mod - 2); }
    mint& operator/=(const mint& m) { return (*this) *= inv(m); }

    friend mint operator+(mint a, const mint& b) { return a += b; }
    friend mint operator-(mint a, const mint& b) { return a -= b; }
    friend mint operator*(mint a, const mint& b) { return a *= b; }
    friend mint operator/(mint a, const mint& b) { return a /= b; }
    operator int64_t() const {return val; }
};

lint mul(lint x, lint y, lint mod){ return (__int128) x * y % mod; }

lint ipow(lint x, lint y, lint p){
    lint ret = 1, piv = x % p;
    while(y){
        if(y&1) ret = mul(ret, piv, p);
        piv = mul(piv, piv, p);
        y >>= 1;
    }
    return ret;
}

namespace kth_root_mod {
    template <typename T>
        struct Memo {
            Memo(const T &g, int s, int _period){
                size = 1;
                while(2 * size <= min(s, _period)) size *= 2;
                mask = size - 1;
                period = _period;
                vs.resize(size);
                os.resize(size + 1);
                T x(1);
                for (int i = 0; i < size; ++i, x *= g) os[((lint)x) & mask]++;
                for (int i = 1; i < size; ++i) os[i] += os[i - 1];
                x = 1;
                for (int i = 0; i < size; ++i, x *= g) vs[--os[((lint)x) & mask]] = {x, i};
                gpow = x;
                os[size] = size;
            }
            int find(T x) const {
                for (int t = 0; t < period; t += size, x *= gpow) {
                    for (int m = (((lint)x) & mask), i = os[m]; i < os[m + 1]; ++i) {
                        if (x == vs[i].first) {
                            int ret = vs[i].second - t;
                            return ret < 0 ? ret + period : ret;
                        }
                    }
                }
                assert(0);
            }
            T gpow;
            int size, mask, period;
            vector<pair<T, int> > vs;
            vector<int> os;
        };


    lint inv(lint a, lint p) {
        lint b = p, x = 1, y = 0;
        while (a) {
            lint q = b / a;
            swap(a, b %= a);
            swap(x, y -= q * x);
        }
        assert(b == 1);
        return y < 0 ? y + p : y;
    }


    mint pe_root(lint c, lint pi, lint ei, lint p) {
        lint s = p - 1, t = 0;
        while (s % pi == 0) s /= pi, ++t;
        lint pe = 1;
        for (lint _ = 0; _ < ei; ++_) pe *= pi;

        lint u = inv(pe - s % pe, pe);
        mint mc = c, one = 1;
        mint z = ipow(mc, (s * u + 1) / pe);
        mint zpe = ipow(mc, s * u);
        if (zpe == one) return z;

        mint vs;
        {
            lint ptm1 = 1;
            for (lint _ = 0; _ < t - 1; ++_) ptm1 *= pi;
            for (mint v = 2;; v += one) {
                vs = ipow(v, s);
                if(ipow(vs, ptm1) != one) break;
            }
        }

        mint vspe = ipow(vs, pe);
        lint vs_e = ei;
        mint base = vspe;
        for (lint _ = 0; _ < t - ei - 1; _++) base = ipow(base, pi);
        Memo<mint> memo(base, (lint)(sqrt(t - ei) * sqrt(pi)) + 1, pi);

        while (zpe != one) {
            mint tmp = zpe;
            lint td = 0;
            while (tmp != one) ++td, tmp = ipow(tmp, pi);
            lint e = t - td;
            while (vs_e != e) {
                vs = ipow(vs, pi);
                vspe = ipow(vspe, pi);
                ++vs_e;
            }

            // BS-GS ... find (zpe * ( vspe ^ n ) ) ^( p_i ^ (td - 1) ) = 1
            mint base_zpe = mint(1) / zpe;
            for (lint _ = 0; _ < td - 1; _++) base_zpe = ipow(base_zpe, pi);
            lint bsgs = memo.find(base_zpe);

            z *= ipow(vs, bsgs);
            zpe *= ipow(vspe, bsgs);
        }
        return z;
    }

    lint kth_root(lint a, lint k, lint p) {
        mod = p;
        a %= p;
        if (k == 0) return a == 1 ? a : -1;
        if (a <= 1 || k <= 1) return a;

        assert(p > 2);
        lint g = gcd(p - 1, k);
        if (ipow(mint(a), (p - 1) / g) != mint(1)) return -1;
        a = (lint)ipow(mint(a), inv(k / g, (p - 1) / g));
        unordered_map<lint, int> fac;
        for (auto &f : factors::factorize(g)) fac[f]++;
        for (auto pp : fac)
            a = pe_root(a, pp.first, pp.second, p);
        return a;
    }
}
