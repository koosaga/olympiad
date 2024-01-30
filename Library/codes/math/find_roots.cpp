// For the given polynomial, find all a such that P(a) = 0.
// credit: adamant @ https://judge.yosupo.jp/submission/185271
using polyn = poly<mint>;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void find_roots_impl(polyn const &p, vector<mint> &res) {
	if (p.deg() == 1) {
		res.push_back(-p[0] / p[1]);
	} else if (p.deg() > 1) {
		auto A = polyn::gcd(polyn({rng(), 1}).powmod((mod - 1) / 2, p) - mint(1), p);
		find_roots_impl(A, res);
		find_roots_impl(p / A, res);
	}
}

auto find_roots(polyn const &p) {
	vector<mint> res;
	if (p[0] == mint(0)) {
		res.push_back(0);
	}
	auto g = polyn::xk(1).powmod(mod - 1, p);
	find_roots_impl(polyn::gcd((g - mint(1)), p), res);
	return res;
}

