#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Macros for convenience.
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

// FINAL_MOD = 10^9 - 401 = 999,999,599.
// We need to compute m^X mod FINAL_MOD, where X is computed modulo L = FINAL_MOD - 1 = 999,999,598.

const int FINAL_MOD = 999999599;
const int L = 999999598;

// Factorization of L:
const int MOD2 = 2;
const int MOD13 = 13;
const int MOD5281 = 5281;
const int MOD7283 = 7283;

// Fast modular exponentiation.
ll modexp(ll base, ll exp, ll mod) {
	ll res = 1 % mod;
	base %= mod;
	while (exp) {
		if (exp & 1)
			res = (res * base) % mod;
		base = (base * base) % mod;
		exp >>= 1;
	}
	return res;
}

// Compute the "reduced factorial" F(n, p) = ∏_{i=1}^{n} (i with all factors of p removed) mod p.
// This is computed recursively using:
//   F(0, p) = 1;
//   Write n = q * p + r with 0 <= r < p, then:
//     F(n, p) = F(q, p) * [ (p-1)^(q mod 2) * (∏_{i=1}^{r} i) ] mod p.
ll reducedFactorial(ll n, int p) {
	if (n == 0)
		return 1;
	ll res = reducedFactorial(n / p, p);
	if ((n / p) & 1LL) { // if (n/p) is odd
		res = (res * (p - 1)) % p;
	}
	int r = n % p;
	for (int i = 1; i <= r; i++) {
		res = (res * i) % p;
	}
	return res % p;
}

// Compute v_p(n!) = ∑_{k>=1} floor(n / p^k)
ll vp(ll n, int p) {
	ll cnt = 0;
	while (n) {
		n /= p;
		cnt += n;
	}
	return cnt;
}

// Standard iterative CRT.
// Given vectors "rems" and "mods" (with pairwise coprime moduli),
// returns the unique x modulo (product of mods) satisfying x ≡ rems[i] (mod mods[i]) for all i.
ll crt(const vector<ll> &rems, const vector<ll> &mods) {
	ll curMod = 1, curRem = 0;
	for (int i = 0; i < sz(rems); i++) {
		ll m = mods[i], r = rems[i];
		ll diff = (r - curRem) % m;
		if (diff < 0)
			diff += m;
		ll inv = modexp(curMod, m - 2, m); // since m is prime
		ll t = (diff * inv) % m;
		curRem += curMod * t;
		curMod *= m;
		curRem %= curMod;
	}
	return curRem;
}

// Main.
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll n, m;
	cin >> n >> m; // now n, m <= 2*10^9

	// Compute all divisors of n.
	vector<ll> divs;
	for (ll i = 1; i * i <= n; i++) {
		if (n % i == 0) {
			divs.push_back(i);
			if (i * i != n)
				divs.push_back(n / i);
		}
	}
	sort(all(divs));

	// We want to compute:
	//   X = ∑_{d|n} f(d)   (mod L),
	// where f(d)= n! / [ (n/d)! * (d!)^(n/d) ].
	// For each divisor d (with r = n/d) we compute f(d) modulo each prime factor of L.
	ll sumX = 0;
	for (ll d : divs) {
		ll r = n / d; // number of cliques.

		// 1. Modulo 2.
		// Since v_2(n!) = n - popcount(n), we have:
		//   v_2(f(d)) = [n - popcount(n)] - [r - popcount(r)] - r*(d - popcount(d)]
		//             = r*(popcount(d) - 1) + popcount(r) - popcount(n).
		int pop_d = __builtin_popcountll(d);
		int pop_r = __builtin_popcountll(r);
		int pop_n = __builtin_popcountll(n);
		ll v2_val = r * (pop_d - 1LL) + pop_r - pop_n;
		int rem2 = (v2_val == 0 ? 1 : 0);

		// 2. Modulo 13.
		ll vp_n_13 = vp(n, MOD13);
		ll vp_r_13 = vp(r, MOD13);
		ll vp_d_13 = vp(d, MOD13);
		ll E13 = vp_n_13 - vp_r_13 - r * vp_d_13;
		int rem13;
		if (E13 > 0) {
			rem13 = 0;
		} else {
			ll R_n = reducedFactorial(n, MOD13);
			ll R_r = reducedFactorial(r, MOD13);
			ll R_d = reducedFactorial(d, MOD13);
			ll R_d_pow = modexp(R_d, r, MOD13);
			ll inv_R_r = modexp(R_r, MOD13 - 2, MOD13);
			ll inv_R_d_pow = modexp(R_d_pow, MOD13 - 2, MOD13);
			rem13 = (int)(((R_n * inv_R_r) % MOD13 * inv_R_d_pow) % MOD13);
		}

		// 3. Modulo 5281.
		ll vp_n_5281 = vp(n, MOD5281);
		ll vp_r_5281 = vp(r, MOD5281);
		ll vp_d_5281 = vp(d, MOD5281);
		ll E5281 = vp_n_5281 - vp_r_5281 - r * vp_d_5281;
		int rem5281;
		if (E5281 > 0) {
			rem5281 = 0;
		} else {
			ll R_n = reducedFactorial(n, MOD5281);
			ll R_r = reducedFactorial(r, MOD5281);
			ll R_d = reducedFactorial(d, MOD5281);
			ll R_d_pow = modexp(R_d, r, MOD5281);
			ll inv_R_r = modexp(R_r, MOD5281 - 2, MOD5281);
			ll inv_R_d_pow = modexp(R_d_pow, MOD5281 - 2, MOD5281);
			rem5281 = (int)(((R_n * inv_R_r) % MOD5281 * inv_R_d_pow) % MOD5281);
		}

		// 4. Modulo 7283.
		ll vp_n_7283 = vp(n, MOD7283);
		ll vp_r_7283 = vp(r, MOD7283);
		ll vp_d_7283 = vp(d, MOD7283);
		ll E7283 = vp_n_7283 - vp_r_7283 - r * vp_d_7283;
		int rem7283;
		if (E7283 > 0) {
			rem7283 = 0;
		} else {
			ll R_n = reducedFactorial(n, MOD7283);
			ll R_r = reducedFactorial(r, MOD7283);
			ll R_d = reducedFactorial(d, MOD7283);
			ll R_d_pow = modexp(R_d, r, MOD7283);
			ll inv_R_r = modexp(R_r, MOD7283 - 2, MOD7283);
			ll inv_R_d_pow = modexp(R_d_pow, MOD7283 - 2, MOD7283);
			rem7283 = (int)(((R_n * inv_R_r) % MOD7283 * inv_R_d_pow) % MOD7283);
		}

		vector<ll> mods = {(ll)MOD2, (ll)MOD13, (ll)MOD5281, (ll)MOD7283};
		vector<ll> rems = {(ll)rem2, (ll)rem13, (ll)rem5281, (ll)rem7283};
		ll f_d = crt(rems, mods) % L; // f(d) modulo L.

		sumX = (sumX + f_d) % L;
	}

	ll X = sumX % L;
	int ans = (int)modexp(m, X, FINAL_MOD);
	cout << ans << "\n";

	return 0;
}
