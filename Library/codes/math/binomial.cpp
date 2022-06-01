#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 500005;

//https://judge.yosupo.jp/submission/65139
// Require: 1 <= b
// return: (g, x) s.t. g = gcd(a, b), xa = g MOD b, 0 <= x < b/g
template <typename Int> /* constexpr */ std::pair<Int, Int> inv_gcd(Int a, Int b) {
    a %= b;
    if (a < 0) a += b;
    if (a == 0) return {b, 0};
    Int s = b, t = a, m0 = 0, m1 = 1;
    while (t) {
        Int u = s / t;
        s -= t * u, m0 -= m1 * u;
        auto tmp = s;
        s = t, t = tmp, tmp = m0, m0 = m1, m1 = tmp;
    }
    if (m0 < 0) m0 += b / s;
    return {s, m0};
}

struct combination_prime_pow {
    int p, q, m;
    std::vector<int> fac, invfac;

    int _pow(int x, long long n) const {
        long long ans = 1;
        while (n) {
            if (n & 1) ans = ans * x % m;
            x = (long long)x * x % m;
            n >>= 1;
        }
        return ans;
    }

    long long _ej(long long n, int j) const {
        for (int t = 0; t < j + 1 and n; ++t) n /= p;
        long long ret = 0;
        while (n) ret += n, n /= p;
        return ret;
    }

    combination_prime_pow(int p_, int q_) : p(p_), q(q_), m(1) {
        for (int t = 0; t < q; ++t) m *= p;
        fac.assign(m, 1);
        invfac.assign(m, 1);
        for (int i = 1; i < m; ++i) fac[i] = (long long)fac[i - 1] * (i % p ? i : 1) % m;
        invfac[m - 1] = _pow(fac[m - 1], m / p * (p - 1) - 1);
        for (int i = m - 1; i; --i) invfac[i - 1] = (long long)invfac[i] * (i % p ? i : 1) % m;
    }

    int nCr(long long n, long long r) const {
        if (r < 0 or n < r) return 0;
        long long k = n - r;
        long long e0 = _ej(n, 0) - _ej(r, 0) - _ej(k, 0);
        if (e0 >= q) return 0;
        long long ret = _pow(p, e0);
        if ((p > 2 or q < 3) and (_ej(n, q - 1) - _ej(r, q - 1) - _ej(k, q - 1)) & 1) {
            ret = ret ? m - ret : 0;
        }
        while (n) {
            ret = __int128(ret) * fac[n % m] * ((long long)invfac[r % m] * invfac[k % m]) % m;
            n /= p, r /= p, k /= p;
        }
        return (int)ret;
    }
};

// nCr mod m
// Complexity: O(m) space worst (construction), O(polylog(n)) (per query)
// https://judge.yosupo.jp/problem/binomial_coefficient
struct combination {
    std::vector<combination_prime_pow> cpps;
    std::vector<int> ms, ims;

    template <class Map> combination(const Map &p2deg) {
        int m0 = 1;
        for (auto f : p2deg) {
            cpps.push_back(combination_prime_pow(f.first, f.second));
            int m1 = cpps.back().m;
            ms.push_back(m1);
            if (m0 < m1) std::swap(m0, m1);
            int im = inv_gcd<int>(m0, m1).second;
            ims.push_back(im);
            m0 *= m1;
        }
    }

    int operator()(long long n, long long r) const {
        if (r < 0 or n < r) return 0;
        int r0 = 0, m0 = 1;
        for (int i = 0; i < int(cpps.size()); ++i) {
            int r1 = cpps[i].nCr(n, r) % ms[i], m1 = ms[i];
            if (m0 < m1) {
                std::swap(r0, r1);
                std::swap(m0, m1);
            }
            int im = ims[i];
            int x = (r1 - r0) % m1 * im % m1;
            r0 += x * m0;
            m0 *= m1;
            if (r0 < 0) r0 += m0;
        }
        return r0;
        // std::vector<int> rs;
        // for (const auto &cpp : cpps) rs.push_back(cpp.nCr(n, r));
        // return crt(rs, ms).first;
    }
};


int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int q; cin >> q;
	int m; cin >> m;
	map<int, int> mp;
	for(int i = 2; i * i <= m; i++){
		int cnt = 0;
		while(m % i == 0){
			m /= i;
			cnt++;
		}
		if(cnt) mp[i] = cnt;
	}
	if(m > 1) mp[m] = 1;
	combination solver(mp);
	while(q--){
	lint n, k; cin >> n >> k;
	cout << solver(n, k) << "\n";
	}
}

