#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

// Given a type T, addition operator (only associative), zero (identity),
// implements a deque that can compute the sum (composite).
// ref: https://judge.yosupo.jp/submission/109658
template <class F, class T, class... Args>
constexpr bool callable_with = std::is_same_v<T, decltype(std::declval<F>()(std::declval<Args>()...))>;
template <class T, class Op> struct DequeAggregate {
	static_assert(callable_with<Op, T, T, T>);
	Op op;
	T unit; // unit is never combined, just returned for an empty deque
	std::array<std::vector<T>, 2> values;
	std::array<std::vector<T>, 2> aggregates;
	DequeAggregate(Op op_, T unit_) : op{op_}, unit{unit_}, values{}, aggregates{} {}
	template <typename V>
	DequeAggregate(Op op_, T unit_, const V &initial)
		: op{op_}, unit{unit_}, values{initial.begin(), initial.end()}, aggregates{} {
		recompute();
	}
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
			std::partial_sum(values[0].begin(), values[0].end(), aggregates[0].begin(),
							 [&](const T &a, const T &b) { return op(b, a); });
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

struct node {
	lint sum, pmax;
	node() { sum = pmax = 0; }
	node(lint x) { sum = x, pmax = max(x, 0ll); }
	node(lint x, lint y) { sum = x, pmax = y; }
};

auto op = [](const node &a, const node &b) { return node(a.sum + b.sum, max(a.pmax, a.sum + b.pmax)); };

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<lint> a(n - m + 1);
	for (auto &x : a)
		cin >> x;
	int q;
	cin >> q;
	vector<array<int, 3>> queries;
	vector<pi> ans(q);
	for (int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		l--;
		if (r - l >= m)
			queries.push_back({l, r, i});
	}
	if (sz(queries) == 0) {
		for (int i = 0; i < q; i++)
			cout << "unbounded\n";
		return 0;
	}
	sort(all(queries), [&](const array<int, 3> &a, const array<int, 3> &b) {
		if ((a[0] >> 8) != (b[0] >> 8))
			return a[0] < b[0];
		if ((a[0] >> 8) & 1)
			return a[1] < b[1];
		return a[1] > b[1];
	});
	vector<DequeAggregate<node, decltype(op)>> dq;
	for (int i = 0; i < m; i++) {
		dq.push_back(DequeAggregate<node, decltype(op)>(op, node()));
	}
	for (int i = queries[0][0] + m; i < queries[0][1]; i++) {
		dq[i % m].push_back(node(a[i - m + 1] - a[i - m]));
	}
	lint summer = 0;
	for (int i = 0; i < m; i++)
		summer += dq[i].query().pmax;
	auto query = [&](lint inits) {
		inits += summer + m - 1;
		inits -= (inits % m + m) % m;
		return pi{inits / m, 1};
	};
	ans[queries[0][2]] = query(a[queries[0][0]]);
	int l = queries[0][0], r = queries[0][1];
	for (int i = 1; i < sz(queries); i++) {
		while (l > queries[i][0]) {
			l--;
			summer -= dq[l % m].query().pmax;
			dq[l % m].push_front(node(a[l + 1] - a[l]));
			summer += dq[l % m].query().pmax;
		}
		while (r < queries[i][1]) {
			summer -= dq[r % m].query().pmax;
			dq[r % m].push_back(node(a[r - m + 1] - a[r - m]));
			summer += dq[r % m].query().pmax;
			r++;
		}
		while (l < queries[i][0]) {
			summer -= dq[l % m].query().pmax;
			dq[l % m].pop_front();
			summer += dq[l % m].query().pmax;
			l++;
		}
		while (r > queries[i][1]) {
			r--;
			summer -= dq[r % m].query().pmax;
			dq[r % m].pop_back();
			summer += dq[r % m].query().pmax;
		}
		ans[queries[i][2]] = query(a[queries[i][0]]);
	}
	for (int i = 0; i < q; i++) {
		if (ans[i][1] == 0)
			cout << "unbounded\n";
		else
			cout << ans[i][0] << "\n";
	}
}