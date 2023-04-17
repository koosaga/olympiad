#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

// Convolution mod 2^64
// Source: https://judge.yosupo.jp/submission/75233
// MAXN = max size of polynomials whose convolution will be found
const int MAXN = 1050000;
namespace Conv64 {
using u64 = uint64_t;
struct u64_omega {
	using T = u64_omega;
	u64 a, b;
	constexpr u64_omega() : a(0), b(0) {}
	constexpr u64_omega(u64 x) : a(x), b(0) {}
	constexpr u64_omega(u64 a, u64 b) : a(a), b(b) {}
	constexpr T &to_conj() {
		b = -b, a += b;
		return *this;
	}
	constexpr T &operator+=(const T &other) {
		a += other.a, b += other.b;
		return *this;
	}
	constexpr T &operator-=(const T &other) {
		a -= other.a, b -= other.b;
		return *this;
	}
	constexpr T &operator*=(const T &other) {
		u64 tmp_a = a;
		a = a * other.a - b * other.b;
		b = b * other.a + tmp_a * other.b - b * other.b;
		return *this;
	}
	[[nodiscard]] constexpr T conj() const { return T{a - b, -b}; }
	[[nodiscard]] constexpr T operator-() const { return T{-a, -b}; }
	[[nodiscard]] constexpr friend T operator+(const T &u, const T &v) { return {u.a + v.a, u.b + v.b}; }
	[[nodiscard]] constexpr friend T operator-(const T &u, const T &v) { return {u.a - v.a, u.b - v.b}; }
	[[nodiscard]] constexpr friend T operator*(const T &u, const T &v) { return {u.a * v.a - u.b * v.b, u.b * v.a + u.a * v.b - u.b * v.b}; }
};
static constexpr u64_omega omega{0, 1};
static constexpr u64_omega omega2{-1ull, -1ull};
static constexpr u64_omega one_minus_omega{1 - omega};
static constexpr u64_omega one_minus_omega2{1 - omega2};
static constexpr u64_omega omega2_minus_omega{omega2 - omega};
static constexpr u64_omega inv_3{12297829382473034411ull, 0};
template <size_t maxn> class Conv64 {

  public:
	Conv64() = delete;
	static vector<u64> multiply(const vector<u64> &p, const vector<u64> &q) {
		if (q.empty() || p.empty())
			return {};
		u64 s = 1;
		while (s < p.size() + q.size() - 1)
			s *= 3;
		vector<u64> pp(s), qq(s), res(s);
		copy(begin(p), end(p), begin(pp));
		copy(begin(q), end(q), begin(qq));
		mul_n_1(pp.data(), qq.data(), pp.size(), res.data());
		res.resize(p.size() + q.size() - 1);
		return res;
	}

	static vector<u64> very_unsafe_multiply(vector<u64> &p, vector<u64> &q) {
		if (q.empty() || p.empty())
			return {};
		u64 s = p.size();
		vector<u64> res(s);
		mul_n_1(p.data(), q.data(), s, res.data());
		return res;
	}

  private:
	static constexpr size_t BUF_SIZE = [] {
		u64 n = 1;
		while (n < maxn)
			n *= 3;
		u64 m = 1;
		while (m * m <= n)
			m *= 3;
		m /= 3;
		return 3 * n + 6 * m;
	}();

	using R = u64_omega;
	static R *tmp;
	static array<R, BUF_SIZE> tmp_v;

	static void multiply_monomial(R *p, u64 m, u64 t, R *to) {
		if (t == 0 || t == 3 * m) {
			copy_n(p, m, to);
			return;
		}
		struct anon_pair {
			u64 a;
			R x;
		};
		const auto [tt, mult] = [&] {
			if (t < m)
				return anon_pair{t, R(1)};
			else if (t < 2 * m)
				return anon_pair{t - m, omega};
			else
				return anon_pair{t - 2 * m, omega2};
		}();
		R mult_omega = mult * omega;
		for (u64 j = 0; j < tt; j++)
			to[j] = p[m - tt + j] * mult_omega;
		for (u64 j = tt; j < m; j++)
			to[j] = p[j - tt] * mult;
	}

	static void dft(R *p, u64 m, u64 r) {
		if (r == 1)
			return;
		const u64 rr = r / 3;
		const u64 pos1 = m * rr, pos2 = 2 * m * rr;
		const u64 m_r = 3 * m / r;
		auto *const tmp_1 = tmp + m;
		auto *const tmp_2 = tmp + 2 * m;
		for (u64 i = 0; i < rr; ++i) {
			auto *const p_i_0 = p + i * m;
			auto *const p_i_1 = p + i * m + pos1;
			auto *const p_i_2 = p + i * m + pos2;
			for (u64 j = 0; j < m; ++j) {
				tmp[j] = p_i_0[j] + p_i_1[j] + p_i_2[j];
				tmp_1[j] = p_i_0[j] + omega * p_i_1[j] + omega2 * p_i_2[j];
				tmp_2[j] = p_i_0[j] + omega2 * p_i_1[j] + omega * p_i_2[j];
				p_i_0[j] = tmp[j];
			}
			multiply_monomial(tmp + m, m, i * m_r, p + pos1 + i * m);
			multiply_monomial(tmp + 2 * m, m, 2 * i * m_r, p + pos2 + i * m);
		}
		dft(p, m, rr);
		dft(p + pos1, m, rr);
		dft(p + pos2, m, rr);
	}

	static void idft(R *p, u64 m, u64 r) {
		if (r == 1)
			return;
		const u64 rr = r / 3;
		const u64 pos1 = m * rr, pos2 = 2 * m * rr;
		idft(p, m, rr);
		idft(p + pos1, m, rr);
		idft(p + pos2, m, rr);
		const u64 m_r = 3 * m / r;
		auto *const tmp_1 = tmp + m;
		auto *const tmp_2 = tmp + 2 * m;
		for (u64 i = 0; i < rr; ++i) {
			auto *const p_i_0 = p + i * m;
			auto *const p_i_1 = p + i * m + pos1;
			auto *const p_i_2 = p + i * m + pos2;
			multiply_monomial(p_i_1, m, 3 * m - i * m_r, tmp_1);
			multiply_monomial(p_i_2, m, 3 * m - 2 * i * m_r, tmp_2);
			for (u64 j = 0; j < m; ++j) {
				tmp[j] = p_i_0[j];
				p_i_0[j] = tmp[j] + tmp_1[j] + tmp_2[j];
				p_i_1[j] = tmp[j] + omega2 * tmp_1[j] + omega * tmp_2[j];
				p_i_2[j] = tmp[j] + omega * tmp_1[j] + omega2 * tmp_2[j];
			}
		}
	}

	static void mul_n_omega(R *p, R *q, u64 n, R *to) {
		if (n <= 27) {
			fill_n(to, n, R(0));
			for (u64 i = 0; i < n; ++i) {
				for (u64 j = 0; j < n - i; ++j)
					to[i + j] += p[i] * q[j];
				for (u64 j = n - i; j < n; ++j)
					to[i + j - n] += p[i] * q[j] * omega;
			}
			return;
		}

		u64 m = 1;
		while (m * m < n)
			m *= 3;
		const u64 r = n / m;
		const u64 m_r = m / r;

		R inv = 1;
		for (u64 i = 1; i < r; i *= 3)
			inv *= inv_3;

		for (u64 i = 0; i < r; ++i) {
			multiply_monomial(p + m * i, m, m_r * i, to + m * i);
			multiply_monomial(q + m * i, m, m_r * i, to + n + m * i);
		}

		auto *const to_n = to + n;
		auto *const to_2n = to + 2 * n;

		dft(to, m, r);
		dft(to + n, m, r);
		for (u64 i = 0; i < r; ++i)
			mul_n_omega(to + m * i, to_n + m * i, m, to_2n + m * i);
		idft(to_2n, m, r);
		for (u64 i = 0; i < n; ++i)
			to_2n[i] *= inv;

		for (u64 i = 0; i < r; ++i)
			multiply_monomial(to_2n + m * i, m, 3 * m - m_r * i, to_n + m * i);

		for (u64 i = 0; i < r; ++i) {
			auto *const p_i = p + m * i;
			auto *const q_i = q + m * i;
			for (u64 j = 0; j < m; ++j)
				p_i[j].to_conj(), q_i[j].to_conj();
			multiply_monomial(p_i, m, 2 * m_r * i, to + m * i);
			multiply_monomial(q_i, m, 2 * m_r * i, p_i);
		}

		dft(to, m, r);
		dft(p, m, r);
		for (u64 i = 0; i < r; ++i)
			mul_n_omega(to + m * i, p + m * i, m, to_2n + m * i);
		idft(to_2n, m, r);
		for (u64 i = 0; i < n; ++i)
			to_2n[i] *= inv;

		for (u64 i = 0; i < r; ++i)
			multiply_monomial(to_2n + m * i, m, 3 * m - 2 * m_r * i, q + m * i);

		fill_n(to, n, R(0));
		for (u64 i = 0; i < r; ++i) {
			const auto im = i * m;
			auto *const to_i = to + im;
			auto *const to_ni = to_n + im;
			auto *const q_i = q + im;
			for (u64 j = 0; j < m; ++j) {
				to_i[j] += one_minus_omega * to_ni[j] + one_minus_omega2 * q_i[j].conj();
				if (im + m + j < n) {
					to_i[m + j] += omega2_minus_omega * (to_ni[j] - q_i[j].conj());
				} else {
					to[im + m + j - n] += one_minus_omega2 * (to_ni[j] - q_i[j].conj());
				}
			}
		}
		for (u64 i = 0; i < n; ++i)
			to[i] *= inv_3;
	}

	static void mul_n_1(u64 *p, u64 *q, u64 n, u64 *target) {
		u64 m = 1;
		while (m * m <= n)
			m *= 3;
		m /= 3;
		const u64 r = n / m;

		R inv = 1;
		for (u64 i = 1; i < r; i *= 3)
			inv *= inv_3;

		R *buf = tmp_v.data();
		R *pp = buf;
		R *qq = buf + n;
		R *to = buf + 2 * n;
		tmp = buf + 3 * n + 3 * m;

		copy_n(p, n, pp);
		copy_n(q, n, qq);

		dft(pp, m, r);
		dft(qq, m, r);
		for (u64 i = 0; i < r; ++i)
			mul_n_omega(pp + i * m, qq + i * m, m, to + i * m);
		idft(to, m, r);
		for (u64 i = 0; i < n; ++i)
			pp[i] = to[i] * inv;

		fill_n(to, n, R(0));
		for (u64 i = 0; i < r; ++i) {
			const auto im = i * m;
			auto *const to_i = to + im;
			auto *const pp_i = pp + im;
			for (u64 j = 0; j < m; ++j) {
				to_i[j] += one_minus_omega * pp_i[j] + one_minus_omega2 * pp_i[j].conj();
				if (im + m + j < n) {
					to_i[m + j] += omega2_minus_omega * (pp_i[j] - pp_i[j].conj());
				} else {
					to[im + m + j - n] += omega2_minus_omega * (pp_i[j] - pp_i[j].conj());
				}
			}
		}
		for (u64 i = 0; i < n; ++i)
			target[i] = (to[i] * inv_3).a;
	}
};

template <size_t N> u64_omega *Conv64<N>::tmp;
template <size_t N> array<u64_omega, Conv64<N>::BUF_SIZE> Conv64<N>::tmp_v;
vector<u64> multiply(vector<u64> a, vector<u64> b) {
	int s = 1;
	while (s < sz(a) + sz(b) - 1)
		s *= 3;
	a.resize(s);
	b.resize(s);
	return Conv64<MAXN>::very_unsafe_multiply(a, b);
}
} // namespace Conv64

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<uint64_t> a(n), b(m);
	for (auto &x : a)
		cin >> x;
	for (auto &x : b)
		cin >> x;
	auto c = Conv64::multiply(a, b);
	for (int i = 0; i < n + m - 1; i++)
		cout << c[i] << " ";
}