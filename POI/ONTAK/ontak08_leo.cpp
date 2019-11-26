#include<bits/stdc++.h>
using namespace std;
using lint = long long;

struct LinearRecurrence {
	using ll = long long;
    using vec = vector<ll>;

    static void extand(vec &a, ll d, ll value = 0) {
        if (d <= a.size()) return;
        a.resize(d, value);
    }

  static vec BerlekampMassey(const vec &s, ll mod) {
    std::function<ll(ll)> inverse = [&](ll a) {
      return a == 1 ? 1 : (ll)(mod - mod / a) * inverse(mod % a) % mod;
    };
    vec A = {1}, B = {1};
    ll b = s[0];
    for (size_t i = 1, m = 1; i < s.size(); ++i, m++) {
      ll d = 0;
      for (size_t j = 0; j < A.size(); ++j) {
        d += A[j] * s[i - j] % mod;
      }
      if (!(d %= mod)) continue;
      if (2 * (A.size() - 1) <= i) {
        auto temp = A;
        extand(A, B.size() + m);
        ll coef = d * inverse(b) % mod;
        for (size_t j = 0; j < B.size(); ++j) {
          A[j + m] -= coef * B[j] % mod;
          if (A[j + m] < 0) A[j + m] += mod;
        }
        B = temp, b = d, m = 0;
      } else {
        extand(A, B.size() + m);
        ll coef = d * inverse(b) % mod;
        for (size_t j = 0; j < B.size(); ++j) {
          A[j + m] -= coef * B[j] % mod;
          if (A[j + m] < 0) A[j + m] += mod;
        }
      }
    }
    return A;
  }

    static void exgcd(ll a, ll b, ll &g, ll &x, ll &y) {
        if (!b) x = 1, y = 0, g = a;
        else {
            exgcd(b, a % b, g, y, x);
            y -= x * (a / b);
        }
    }
    static ll crt(const vec &c, const vec &m) {
        ll n = c.size();
        ll M = 1, ans = 0;
        for (ll i = 0; i < n; ++i) M *= m[i];
        for (ll i = 0; i < n; ++i) {
            ll x, y, g, tm = M / m[i];
            exgcd(tm, m[i], g, x, y);
            ans = (ans + tm * x * c[i] % M) % M;
        }
        return (ans + M) % M;
    }
    static vec ReedsSloane(const vec &s, ll mod) {
        auto inverse = [] (ll a, ll m) {
            ll d, x, y;
            exgcd(a, m, d, x, y);
            return d == 1 ? (x % m + m) % m : -1;
        };
        auto L = [] (const vec &a, const vec &b) {
            ll da = (a.size() > 1 || (a.size() == 1 && a[0])) ? (ll)a.size() - 1 : -1000;
            ll db = (b.size() > 1 || (b.size() == 1 && b[0])) ? (ll)b.size() - 1 : -1000;
            return max(da, db + 1);
        };
        auto prime_power = [&] (const vec &s, ll mod, ll p, ll e) {
            // linear feedback shift register mod p^e, p is prime
            vector<vec> a(e), b(e), an(e), bn(e), ao(e), bo(e);
            vec t(e), u(e), r(e), to(e, 1), uo(e), pw(e + 1);;

            pw[0] = 1;
            for (ll i = pw[0] = 1; i <= e; ++i) pw[i] = pw[i - 1] * p;
            for (ll i = 0; i < e; ++i) {
                a[i] = {pw[i]}, an[i] = {pw[i]};
                b[i] = {0}, bn[i] = {s[0] * pw[i] % mod};
                t[i] = s[0] * pw[i] % mod;
                if (t[i] == 0) {
                    t[i] = 1, u[i] = e;
                } else {
                    for (u[i] = 0; t[i] % p == 0; t[i] /= p, ++u[i]);
                }
            }
            for (ll k = 1; k < s.size(); ++k) {
                for (ll g = 0; g < e; ++g) {
                    if (L(an[g], bn[g]) > L(a[g], b[g])) {
                        ao[g] = a[e - 1 - u[g]];
                        bo[g] = b[e - 1 - u[g]];
                        to[g] = t[e - 1 - u[g]];
                        uo[g] = u[e - 1 - u[g]];
                        r[g] = k - 1;
                    }
                }
                a = an, b = bn;
                for (ll o = 0; o < e; ++o) {
                    ll d = 0;
                    for (ll i = 0; i < a[o].size() && i <= k; ++i) {
                        d = (d + a[o][i] * s[k - i]) % mod;
                    }
                    if (d == 0) {
                        t[o] = 1, u[o] = e;
                    } else {
                        for (u[o] = 0, t[o] = d; t[o] % p == 0; t[o] /= p, ++u[o]);
                        ll g = e - 1 - u[o];
                        if (L(a[g], b[g]) == 0) {
                            extand(bn[o], k + 1);
                            bn[o][k] = (bn[o][k] + d) % mod;
                        } else {
                            ll coef = t[o] * inverse(to[g], mod) % mod * pw[u[o] - uo[g]] % mod;
                            ll m = k - r[g];
                            extand(an[o], ao[g].size() + m);
                            extand(bn[o], bo[g].size() + m);
                            for (ll i = 0; i < ao[g].size(); ++i) {
                                an[o][i + m] -= coef * ao[g][i] % mod;
                                if (an[o][i + m] < 0) an[o][i + m] += mod;
                            }
                            while (an[o].size() && an[o].back() == 0) an[o].pop_back();
                            for (ll i = 0; i < bo[g].size(); ++i) {
                                bn[o][i + m] -= coef * bo[g][i] % mod;
                                if (bn[o][i + m] < 0) bn[o][i + m] -= mod;
                            }
                            while (bn[o].size() && bn[o].back() == 0) bn[o].pop_back();
                        }
                    }
                }
            }
            return make_pair(an[0], bn[0]);
        };

        vector<tuple<ll, ll, ll>> fac;
        for (ll i = 2; i * i <= mod; ++i) if (mod % i == 0) {
                ll cnt = 0, pw = 1;
                while (mod % i == 0) mod /= i, ++cnt, pw *= i;
                fac.emplace_back(pw, i, cnt);
            }
        if (mod > 1) fac.emplace_back(mod, mod, 1);
        vector<vec> as;
        ll n = 0;
        for (auto &&x: fac) {
            ll mod, p, e;
            vec a, b;
            tie(mod, p, e) = x;
            auto ss = s;
            for (auto &&x: ss) x %= mod;
            tie(a, b) = prime_power(ss, mod, p, e);
            as.emplace_back(a);
            n = max(n, (ll) a.size());
        }
        vec a(n), c(as.size()), m(as.size());

        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < as.size(); ++j) {
                m[j] = get<0>(fac[j]);
                c[j] = i < as[j].size() ? as[j][i] : 0;
            }
            a[i] = crt(c, m);
        }
        return a;
    }

    LinearRecurrence(const vec &s, const vec &c, ll mod):
        init(s), trans(c), mod(mod), m(s.size()) {}

    LinearRecurrence(const vec &s, ll mod, bool is_prime = true): mod(mod) {
        vec A;
        if(is_prime) A = BerlekampMassey(s,mod);
        else A = ReedsSloane(s, mod);
        if (A.empty()) A = {0};
        m = A.size() - 1;

        trans.resize(m);
        for (ll i = 0; i < m; ++i) {
            trans[i] = (mod - A[i + 1]) % mod;
        }
        reverse(trans.begin(), trans.end());
        for (ll i = 0; i < m; ++i) {
        //	printf("%d = %lld\n", i, trans[i]);
        }
        init = {s.begin(), s.begin() + m};
    }


    ll calc(ll n) {
        if (mod == 1) return 0;
        if (n < m) return init[n];
        vec v(m), u(m << 1);

        ll msk = !!n;
        for (ll m = n; m > 1; m >>= 1LL) msk <<= 1LL;
        v[0] = 1 % mod;
        for (ll x = 0; msk; msk >>= 1LL, x <<= 1LL) {
            fill_n(u.begin(), m * 2, 0);
            x |= !!(n & msk);
            if (x < m) u[x] = 1 % mod;
            else { // can be optimized by fft/ntt
                for (ll i = 0; i < m; ++i) {
                    for (ll j = 0, t = i + (x & 1); j < m; ++j, ++t) {
                        u[t] = (u[t] + v[i] * v[j]) % mod;
                    }
                }
                for (ll i = m * 2 - 1; i >= m; --i) {
                    for (ll j = 0, t = i - m; j < m; ++j, ++t) {
                        u[t] = (u[t] + trans[j] * u[i]) % mod;
                    }
                }
            }
            v = {u.begin(), u.begin() + m};
        }
        ll ret = 0;
        for (ll i = 0; i < m; ++i) {
            ret = (ret + v[i] * init[i]) % mod;
        }
        return ret;
    }

    ll calc(unsigned long long n) {
        if (mod == 1) return 0;
        if (n < m) return init[n];
        vec v(m), u(m << 1);

        unsigned long long msk = !!n;
        for (auto m = n; m > 1; m >>= 1ULL) msk <<= 1ULL;
        v[0] = 1 % mod;
        for (auto x = 0ULL; msk; msk >>= 1ULL, x <<= 1ULL) {
            fill_n(u.begin(), m * 2, 0);
            x |= !!(n & msk);
            if (x < m) u[x] = 1 % mod;
            else { // can be optimized by fft/ntt
                for (ll i = 0; i < m; ++i) {
                    for (ll j = 0, t = i + (x & 1); j < m; ++j, ++t) {
                        u[t] = (u[t] + v[i] * v[j]) % mod;
                    }
                }
                for (ll i = m * 2 - 1; i >= m; --i) {
                    for (ll j = 0, t = i - m; j < m; ++j, ++t) {
                        u[t] = (u[t] + trans[j] * u[i]) % mod;
                    }
                }
            }
            v = {u.begin(), u.begin() + m};
        }
        ll ret = 0;
        for (ll i = 0; i < m; ++i) {
            ret = (ret + v[i] * init[i]) % mod;
        }
        return ret;
    }
    vec init, trans;
    ll mod;
    ll m;
};

const int MAXN = 400;
const int mod = 1e9;

int L[MAXN];
unsigned long long n;
int k;

int main(){
	L[0] = L[1] = 1;
	for(int i=2; i<MAXN; i++) L[i] = (L[i-1] + L[i-2] + 1) % mod;
	cin >> n >> k;
	for(int i=0; i<MAXN; i++){
		lint m = 1;
		for(int j=0; j<k; j++) m = m * L[i] % mod;
		if(i > 0) L[i] = (m + L[i - 1]) % mod;
		else L[i] = m;
	}
//	cout << L[n] << endl;
//	return 0;
	vector<lint> v(L, L + MAXN);
	LinearRecurrence reeds_sloane(v, mod, 0);
	lint ans = reeds_sloane.calc(n);
	printf("%09lld", ans);
}
