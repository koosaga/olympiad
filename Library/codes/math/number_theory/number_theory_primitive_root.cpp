// Given a prime p, find a primitive root.
// Time complexity is dominated by factorization of p - 1.
// Ref: https://judge.yosupo.jp/submission/109014
unsigned long long primitive_root(unsigned long long p) {
	using u64 = unsigned long long;
	using u128 = __uint128_t;
	if (p == 2)
		return 1;
	auto F = factorize(p - 1);
	u64 r = p;
	for (int t = 0; t < 6; t++)
		r *= 2 - r * p;
	u64 n2 = -(u128)p % p;
	auto red = [&](u128 t) noexcept -> u64 {
		t = (t + (u128)((u64)t * -r) * p) >> 64;
		return (t >= p) ? t - p : t;
	};
	auto mult = [&](u64 a, u64 b) noexcept { return red((u128)red((u128)a * b) * n2); };
	auto powm = [&](u64 a, u64 i) noexcept {
		u64 b = 1;
		while (i) {
			if (i & 1) {
				b = mult(a, b);
			}
			a = mult(a, a);
			i /= 2;
		}
		return b;
	};
	static u64 v = 7001;
	while (true) {
		v ^= v << 13;
		v ^= v >> 7;
		v ^= v << 17; // Xorshift https://www.jstatsoft.org/article/download/v008i14/916
		u64 vv = v % p;
		if (vv == 0)
			continue;
		bool ok = true;
		for (auto f : F) {
			u64 i = (p - 1) / f;
			if (powm(vv, i) == 1) {
				ok = false;
				break;
			}
		}
		if (ok)
			break;
	}
	return v % p;
}
