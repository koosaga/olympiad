#include <bits/stdc++.h>
using namespace std;
using lint = long long;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 998244353;


// Given a type T, addition operator (only associative), zero (identity),
// implements a deque that can compute the sum (composite).
// ref: https://judge.yosupo.jp/submission/109658
template <class F, class T, class... Args> constexpr bool callable_with = std::is_same_v<T, decltype(std::declval<F>()(std::declval<Args>()...))>;
template <class T, class Op> struct DequeAggregate {
	static_assert(callable_with<Op, T, T, T>);
	Op op;
	T unit; // unit is never combined, just returned for an empty deque
	std::array<std::vector<T>, 2> values;
	std::array<std::vector<T>, 2> aggregates;
	DequeAggregate(Op op_, T unit_) : op{op_}, unit{unit_}, values{}, aggregates{} {}
	template <typename V> DequeAggregate(Op op_, T unit_, const V &initial) : op{op_}, unit{unit_}, values{initial.begin(), initial.end()}, aggregates{} { recompute(); }
	// a[0] -> front
	// a[1] -> back
	bool empty() { return values[0].empty() and values[1].empty(); }
	void push_back(T v) {
		values[1].push_back(std::move(v));
		aggregates[1].push_back(aggregates[1].empty() ? values[1].back() : op(aggregates[1].back(), values[1].back()));
	}
	void push_front(T v) {
		values[0].push_back(std::move(v));
		aggregates[0].push_back(aggregates[0].empty() ? values[0].back() : op(values[0].back(), aggregates[0].back()));
	}
	T back() {
		if (values[1].empty()) {
			std::ptrdiff_t smaller = values[0].size() / 2;
			values[1] = std::vector<T>(values[0].rbegin() + smaller, values[0].rend());
			values[0] = std::vector<T>(values[0].end() - smaller, values[0].end());
			recompute();
		}
		T ret = values[1].back();
		return ret;
	}
	T front() {
		if (values[0].empty()) {
			std::ptrdiff_t smaller = values[1].size() / 2;
			values[0] = std::vector<T>(values[1].rbegin() + smaller, values[1].rend());
			values[1] = std::vector<T>(values[1].end() - smaller, values[1].end());
			recompute();
		}
		T ret = values[0].back();
		return ret;
	}
	void pop_back() {
		if (values[1].empty()) {
			std::ptrdiff_t smaller = values[0].size() / 2;
			values[1] = std::vector<T>(values[0].rbegin() + smaller, values[0].rend());
			values[0] = std::vector<T>(values[0].end() - smaller, values[0].end());
			recompute();
		}
		values[1].pop_back();
		aggregates[1].pop_back();
	}
	void pop_front() {
		if (values[0].empty()) {
			std::ptrdiff_t smaller = values[1].size() / 2;
			values[0] = std::vector<T>(values[1].rbegin() + smaller, values[1].rend());
			values[1] = std::vector<T>(values[1].end() - smaller, values[1].end());
			recompute();
		}
		values[0].pop_back();
		aggregates[0].pop_back();
	}
	T query() {
		if (aggregates[0].empty())
			return aggregates[1].empty() ? unit : aggregates[1].back();
		if (aggregates[1].empty())
			return aggregates[0].back();
		return op(aggregates[0].back(), aggregates[1].back());
	}
	T at(int x) {
		assert(x >= 0);
		assert(x < (int)values[0].size() + (int)values[1].size());
		if (x < (int)values[0].size()) {
			return values[0][values[0].size() - 1 - x];
		}
		return values[1][x - values[0].size()];
	}
	void recompute() {
		if (not values[0].empty()) {
			aggregates[0].assign(values[0].size(), values[0].front());
			std::partial_sum(values[0].begin(), values[0].end(), aggregates[0].begin(), [&](const T &a, const T &b) { return op(b, a); });
		} else {
			aggregates[0].clear();
		}
		if (not values[1].empty()) {
			aggregates[1].assign(values[1].size(), values[1].front());
			std::partial_sum(values[1].begin(), values[1].end(), aggregates[1].begin(), op);
		} else {
			aggregates[1].clear();
		}
	}
};

//***********************************//
//***********************************//
//             Interface             //
//***********************************//
//***********************************//

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
	friend mint inv(const mint &a) {
		assert(a.val);
		return ipow(a, mod - 2);
	}
	mint &operator/=(const mint &m) { return (*this) *= inv(m); }

	friend mint operator+(mint a, const mint &b) { return a += b; }
	friend mint operator-(mint a, const mint &b) { return a -= b; }
	friend mint operator*(mint a, const mint &b) { return a *= b; }
	friend mint operator/(mint a, const mint &b) { return a /= b; }
	operator int64_t() const { return val; }
};

using pi = array<mint, 2>;

auto op = [](const pi &a, const pi &b) { return pi{a[0] * b[0], a[1] * b[0] + b[1]}; };

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	DequeAggregate dq(op, pi{mint(1), mint(0)});
	int q;
	cin >> q;
	while (q--) {
		int t;
		cin >> t;
		if (t == 0) {
			mint a, b;
			cin >> a.val >> b.val;
			dq.push_front({a, b});
		}
		if (t == 1) {
			mint a, b;
			cin >> a.val >> b.val;
			dq.push_back({a, b});
		}
		if (t == 2) {
			dq.pop_front();
		}
		if (t == 3) {
			dq.pop_back();
		}
		if (t == 4) {
			mint x;
			cin >> x.val;
			auto ans = dq.query();
			cout << ans[0] * x + ans[1] << "\n";
		}
	}
}