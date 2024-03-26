
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 200005;
// Treap by Aeren
// T: data type, U: lazy type.
// TT: usual addition
// UU: combination of lazy (new, old)
// UT: lazy to the data (new, old)

template <bool HAS_QUERY, bool HAS_UPDATE, bool HAS_FLIP, bool IS_COMMUTATIVE, class T, class U, class F1, class F2, class F3, class F4> struct treap_base {
#define ifQ if constexpr (HAS_QUERY)
#define ifU if constexpr (HAS_UPDATE)
#define ifF if constexpr (HAS_FLIP)
#define ifNC if constexpr (!IS_COMMUTATIVE)
	vector<unsigned int> priority;
	vector<int> pv, left, right, internal_size, lazy_flip;
	vector<T> data, subtr_data;
	vector<U> lazy;
	F1 TT;	// monoid operation (always adjacent)
	T T_id; // monoid identity
	F2 UU;	// monoid operation (superset, subset)
	U U_id; // monoid identity
	F3 UT;	// action of U on T (superset, subset)
	F4 FlipT;
	treap_base(F1 TT, T T_id, F2 UU, U U_id, F3 UT, F4 FlipT = plus<>()) : TT(TT), T_id(T_id), UU(UU), U_id(U_id), UT(UT), FlipT(FlipT) {}
	void push(int u) {
		ifU if (lazy[u] != U_id) {
			if (auto v = left[u]; ~v) {
				data[v] = UT(lazy[u], data[v]);
				lazy[v] = UU(lazy[u], lazy[v]);
				ifQ subtr_data[v] = UT(lazy[u], subtr_data[v]);
			}
			if (auto w = right[u]; ~w) {
				data[w] = UT(lazy[u], data[w]);
				lazy[w] = UU(lazy[u], lazy[w]);
				ifQ subtr_data[w] = UT(lazy[u], subtr_data[w]);
			}
			lazy[u] = U_id;
		}
		ifF if (lazy_flip[u]) {
			if (auto v = left[u]; ~v) {
				swap(left[v], right[v]);
				lazy_flip[v] ^= 1;
				ifQ ifNC subtr_data[v] = FlipT(subtr_data[v]);
			}
			if (auto w = right[u]; ~w) {
				swap(left[w], right[w]);
				lazy_flip[w] ^= 1;
				ifQ ifNC subtr_data[w] = FlipT(subtr_data[w]);
			}
			lazy_flip[u] = false;
		}
	}
	template <bool UPDATE_STRUCTURE = true> void refresh(int u) {
		internal_size[u] = 1;

		if (auto v = left[u]; ~v) {
			if constexpr (UPDATE_STRUCTURE) {
				pv[v] = u;
				internal_size[u] += internal_size[v];
			}
		}
		if (auto w = right[u]; ~w) {
			if constexpr (UPDATE_STRUCTURE) {
				pv[w] = u;
				internal_size[u] += internal_size[w];
			}
		}
	}
	void heapify(int u) {
		if (~u) {
			int v = u;
			if (~left[u] && priority[left[u]] > priority[v])
				v = left[u];
			if (~right[u] && priority[right[u]] > priority[v])
				v = right[u];
			if (u != v)
				swap(priority[u], priority[v]), heapify(v);
		}
	}
	template <class output_stream> output_stream &print(output_stream &out, int root) {
#ifdef LOCAL
		out << "[";
		traverse(root, [&](int root) { out << data[root] << ", "; });
		out << "\b\b]\n";
#endif
		return out;
	}
	vector<int> dead_node;
	int new_node(const T &x, int v = -1, int w = -1) {
		// Among all seeds in range [0, 1769666],
		// 72718 has the longest sequence of unique numbers, which is of length 362129.
		static mt19937 rng(72718);
		int u;
		if (dead_node.empty()) {
			u = (int)data.size();
			pv.push_back(-1);
			left.push_back(v);
			right.push_back(w);
			priority.push_back(rng());
			internal_size.push_back(1);
			data.push_back(x);
			ifQ subtr_data.push_back(x);
			ifU lazy.push_back(U_id);
			ifF lazy_flip.push_back(0);
		} else {
			u = dead_node.back();
			dead_node.pop_back();
			pv[u] = -1;
			left[u] = v;
			right[u] = w;
			priority[u] = rng();
			internal_size[u] = 1;
			data[u] = x;
			ifQ subtr_data[u] = x;
			ifU lazy[u] = U_id;
			ifF lazy_flip[u] = 0;
		}
		heapify(u);
		refresh(u);
		return u;
	}
	// O(1)
	int size(int root) const { return ~root ? internal_size[root] : 0; }
	// Split to [-inf, x), [x, inf)
	// Data must be sorted <
	// O(log(n))
	pair<int, int> split_by_key(int root, const T &x) {
		if (!~root)
			return {-1, -1};
		push(root);
		if (data[root] < x) {
			auto [a, b] = split_by_key(right[root], x);
			right[root] = a, refresh(root);
			return {root, b};
		} else {
			auto [a, b] = split_by_key(left[root], x);
			left[root] = b, refresh(root);
			return {a, root};
		}
	}
	// Split to [-inf, x), [x, inf)
	// Data must be sorted cmp
	// O(log(n))
	template <class Compare> pair<int, int> split_by_key(int root, const T &x, Compare cmp) {
		if (!~root)
			return {-1, -1};
		push(root);
		if (cmp(data[root], x)) {
			auto [a, b] = split_by_key(right[root], x, cmp);
			right[root] = a, refresh(root);
			return {root, b};
		} else {
			auto [a, b] = split_by_key(left[root], x, cmp);
			left[root] = b, refresh(root);
			return {a, root};
		}
	}
	// Split into [0, pos), [pos, size(root))
	// O(log(n))
	pair<int, int> split_by_order(int root, int pos) {
		if (!~root) {
			assert(pos == 0);
			return {-1, -1};
		}
		push(root);
		if (size(left[root]) < pos) {
			auto [a, b] = split_by_order(right[root], pos - size(left[root]) - 1);
			right[root] = a, refresh(root);
			return {root, b};
		} else {
			auto [a, b] = split_by_order(left[root], pos);
			left[root] = b, refresh(root);
			return {a, root};
		}
	}
	// Split to [true Segment], [false Segment]
	// Data must be sorted by pred
	// O(log(n))
	pair<int, int> split_by_pred(int root, auto pred) {
		if (!~root)
			return {-1, -1};
		push(root);
		if (pred(root)) {
			auto [a, b] = split_by_pred(right[root], pred);
			right[root] = a, refresh(root);
			return {root, b};
		} else {
			auto [a, b] = split_by_pred(left[root], pred);
			left[root] = b, refresh(root);
			return {a, root};
		}
	}
	// Split into [0, l), [l, r), [r, size(root))
	// O(log(n))
	array<int, 3> split_to_three(int u, int l, int r) {
		assert(0 <= l && l <= r && r <= size(u));
		if (!~u)
			return {-1, -1, -1};
		int a, b, c;
		tie(a, b) = split_by_order(u, l);
		tie(b, c) = split_by_order(b, r - l);
		return {a, b, c};
	}
	// Split into [0, pos[0]), [pos[0], pos[1]), ..., [pos[size(pos) - 1], size(root))
	// O(k * log(n))
	vector<int> split(int root, const vector<int> &pos) {
		assert(is_sorted(pos.begin(), pos.end()));
		if (pos.empty())
			return {root};
		assert(0 <= pos.front() && pos.back() <= size(root));
		if (!~root)
			return vector<int>((int)pos.size() + 1, -1);
		vector<int> res((int)pos.size() + 1);
		res[0] = root;
		for (auto i = 0, last = 0; i < (int)pos.size(); ++i) {
			tie(res[i], res[i + 1]) = split_by_order(res[i], pos[i] - last);
			last = pos[i];
		}
		return res;
	}
	// Append u and v
	// O(log(n))
	int append(int u, int v) {
		if (!~u || !~v)
			return ~u ? u : v;
		push(u);
		push(v);
		if (priority[v] < priority[u]) {
			right[u] = append(right[u], v), refresh(u);
			return u;
		} else {
			left[v] = append(u, left[v]), refresh(v);
			return v;
		}
	}
	// Append treaps in order
	// O((list length) * log(n))
	int append(const vector<int> &list) {
		return accumulate(list.begin(), list.end(), -1, [&](int u, int v) { return append(u, v); });
	}
	// Data must be sorted by <
	// O(log(n))
	int insert_node_by_key(int root, int u) {
		if (!~root)
			return u;
		push(root);
		if (priority[root] > priority[u]) {
			if (data[root] < data[u])
				right[root] = insert_node_by_key(right[root], u);
			else
				left[root] = insert_node_by_key(left[root], u);
			refresh(root);
			return root;
		}
		auto [a, b] = split_by_key(root, data[u]);
		left[u] = a, right[u] = b;
		refresh(u);
		return u;
	}
	// Data must be sorted by <
	// O(log(n))
	int insert_by_key(int root, const T &x) { return insert_node_by_key(root, new_node(x)); }
	// Data must be sorted by cmp
	// O(log(n))
	template <class Compare> int insert_node_by_key(int root, int u, Compare cmp) {
		if (!~root)
			return u;
		push(root);
		if (priority[root] > priority[u]) {
			if (cmp(data[root], data[u]))
				right[root] = insert_node_by_key(right[root], u, cmp);
			else
				left[root] = insert_node_by_key(left[root], u, cmp);
			refresh(root);
			return root;
		}
		auto [a, b] = split_by_key(root, data[u], cmp);
		left[u] = a, right[u] = b;
		refresh(u);
		return u;
	}
	// Data must be sorted by cmp
	// O(log(n))
	template <class Compare> int insert_by_key(int root, const T &x, Compare cmp) { return insert_node_by_key(root, new_node(x), cmp); }
	// O(log(n))
	int insert_node_by_order(int root, int pos, int u) {
		if (!~root) {
			assert(pos == 0);
			return u;
		}
		push(root);
		if (priority[root] > priority[u]) {
			if (size(left[root]) < pos)
				right[root] = insert_node_by_order(right[root], pos - size(left[root]) - 1, u);
			else
				left[root] = insert_node_by_order(left[root], pos, u);
			refresh(root);
			return root;
		}
		auto [a, b] = split_by_order(root, pos);
		left[u] = a, right[u] = b;
		refresh(u);
		return u;
	}
	// O(log(n))
	int insert_by_order(int root, int pos, const T &x) { return insert_node_by_order(root, pos, new_node(x)); }
	// Data must be sorted by pred
	// O(log(n))
	int insert_node_by_pred(int root, auto pred, int u) {
		if (!~root)
			return u;
		push(root);
		if (priority[root] > priority[u]) {
			if (pred(data[root]))
				right[root] = insert_node_by_pred(right[root], pred, u);
			else
				left[root] = insert_node_by_pred(left[root], pred, u);
			refresh(root);
			return root;
		}
		auto [a, b] = split_by_pred(root, pred);
		left[u] = a, right[u] = b;
		refresh(u);
		return u;
	}
	// O(log(n))
	int insert_by_pred(int root, auto pred, const T &x) { return insert_node_by_pred(root, pred, new_node(x)); }
	// Erase the smallest element >= x.
	// Return -2 when no such element exists
	// Data must be sorted by <
	// O(log(n))
	int erase_by_key(int root, const T &x) {
		if (!~root)
			return -2;
		push(root);
		if (data[root] < x) {
			int u = erase_by_key(right[root], x);
			if (u == -2)
				return -2;
			right[root] = u;
		} else {
			int u = erase_by_key(left[root], x);
			if (u == -2) {
				dead_node.push_back(root);
				return append(left[root], right[root]);
			}
			left[root] = u;
		}
		refresh(root);
		return root;
	}
	// Erase the smallest element >= x.
	// Return -2 when no such element exists
	// Data must be sorted by cmp
	// O(log(n))
	template <class Compare> int erase_by_key(int root, const T &x, Compare cmp) {
		if (!~root)
			return -2;
		push(root);
		if (cmp(data[root], x)) {
			int u = erase_by_key(right[root], x, cmp);
			if (u == -2)
				return -2;
			right[root] = u;
		} else {
			int u = erase_by_key(left[root], x, cmp);
			if (u == -2) {
				dead_node.push_back(root);
				return append(left[root], right[root]);
			}
			left[root] = u;
		}
		refresh(root);
		return root;
	}
	// O(log(n))
	int erase_by_order(int root, int pos, int *ans) {
		assert(~root);
		push(root);
		if (size(left[root]) == pos) {
			ans[data[root][1]] = data[root][0];
			dead_node.push_back(root);
			return append(left[root], right[root]);
		}
		if (size(left[root]) < pos)
			right[root] = erase_by_order(right[root], pos - size(left[root]) - 1, ans);
		else
			left[root] = erase_by_order(left[root], pos, ans);
		refresh(root);
		return root;
	}
	// Erase the smallest element x with !pred(x)
	// Return -2 when no such element exists
	// Data must be sorted by pred
	// O(log(n))
	int erase_by_pred(int root, auto pred) {
		if (!~root)
			return -2;
		push(root);
		if (pred(data[root])) {
			int u = erase_by_pred(right[root], pred);
			if (u == -2)
				return -2;
			right[root] = u;
		} else {
			int u = erase_by_pred(left[root], pred);
			if (u == -2) {
				dead_node.push_back(root);
				return append(left[root], right[root]);
			}
			left[root] = u;
		}
		refresh(root);
		return root;
	}
	// Data must be sorted by <
	// O(min(size(u), size(v)) * log(size ratio))
	int unite_by_key(int u, int v) {
		if (!~u || !~v)
			return ~u ? u : v;
		if (priority[u] < priority[v])
			swap(u, v);
		auto [a, b] = split_by_key(v, data[u]);
		push(u);
		left[u] = unite_by_key(left[u], a);
		right[u] = unite_by_key(right[u], b);
		refresh(u);
		return u;
	}
	// Data must be sorted by cmp
	// O(min(size(u), size(v)) * log(size ratio))
	template <class Compare> int unite_by_key(int u, int v, Compare cmp) {
		if (!~u || !~v)
			return ~u ? u : v;
		if (priority[u] < priority[v])
			swap(u, v);
		auto [a, b] = split_by_key(v, data[u], cmp);
		push(u);
		left[u] = unite_by_key(left[u], a, cmp);
		right[u] = unite_by_key(right[u], b, cmp);
		refresh(u);
		return u;
	}
	void traverse(int root, auto f) {
		if (~root) {
			push(root);
			traverse(left[root], f);
			f(root);
			traverse(right[root], f);
			refresh(root);
		}
	}
	int build(int n) { return build(vector<T>(n, T_id)); }
	int build(int n, T init) { return build(vector<T>(n, init)); }
	int build(const vector<T> &a) {
		auto recurse = [&](auto self, int l, int r) -> int {
			if (l == r)
				return -1;
			int m = l + ((r - l) >> 1);
			return new_node(a[m], self(self, l, m), self(self, m + 1, r));
		};
		return recurse(recurse, 0, (int)a.size());
	}
	// Data must be sorted by <
	// O(log(n))
	int order_of_key(int root, const T &x) {
		int res = 0;
		while (~root) {
			push(root);
			if (data[root] < x) {
				res += size(left[root]) + 1;
				root = right[root];
			} else
				root = left[root];
		}
		return res;
	}
	// Data must be sorted by cmp
	// O(log(n))
	template <class Compare> int order_of_key(int root, const T &x, Compare cmp) {
		int res = 0;
		while (~root) {
			push(root);
			if (cmp(data[root], x)) {
				res += size(left[root]) + 1;
				root = right[root];
			} else
				root = left[root];
		}
		return res;
	}
	// O(log(n))
	int node_order(int root, int u) {
		assert(~root && ~u);
		int res = size(left[u]);
		while (root != u) {
			push(pv[u]);
			if (right[pv[u]] == u)
				res += size(left[pv[u]]) + 1;
			u = pv[u];
		}
		return res;
	}
	// pred must be T, T, ..., T, F, F, ..., F
	// O(log(n))
	int partition_point(int root, auto pred) {
		int res = 0;
		while (~root) {
			push(root);
			if (pred(data[root])) {
				res += size(left[root]) + 1;
				root = right[root];
			} else
				root = left[root];
		}
		return res;
	}
	// O(log(n))
	void set(int root, int p, const T &x) {
		assert(0 <= p && p < size(root));
		int u = root;
		while (true) {
			push(u);
			if (size(left[u]) == p) {
				data[u] = x;
				refresh<false>(u);
				break;
			}
			if (size(left[u]) > p)
				u = left[u];
			else {
				p -= size(left[u]) + 1;
				u = right[u];
			}
		}
		while (u != root) {
			u = pv[u];
			refresh<false>(u);
		}
	}
	// O(log(n))
	T query(int root, int p) {
		static_assert(HAS_QUERY);
		assert(0 <= p && p < size(root));
		while (true) {
			push(root);
			if (size(left[root]) == p)
				return data[root];
			if (size(left[root]) > p)
				root = left[root];
			else {
				p -= size(left[root]) + 1;
				root = right[root];
			}
		}
	}
	T _query(int root, int ql, int qr) {
		static_assert(HAS_QUERY);
		if (!~root || qr <= 0 || size(root) <= ql)
			return T_id;
		if (ql <= 0 && size(root) <= qr)
			return subtr_data[root];
		push(root);
		T res = T_id;
		if (ql < size(left[root]))
			res = _query(left[root], ql, qr);
		if (ql <= size(left[root]) && size(left[root]) + 1 <= qr)
			res = TT(res, data[root]);
		if (size(left[root]) + 1 < qr)
			res = TT(res, _query(right[root], ql - size(left[root]) - 1, qr - size(left[root]) - 1));
		return res;
	}
	// O(log(n))
	T query(int root, int ql, int qr) {
		static_assert(HAS_QUERY);
		assert(0 <= ql && ql <= qr && qr <= size(root));
		return ql == qr ? T_id : _query(root, ql, qr);
	}
	// O(log(n))
	void update(int root, int p, const U &f) {
		static_assert(HAS_UPDATE);
		assert(0 <= p && p < size(root));
		int u = root;
		while (true) {
			push(u);
			if (size(left[u]) == p) {
				data[u] = UT(f, data[u]);
				refresh<false>(u);
				break;
			}
			if (size(left[u]) > p)
				u = left[u];
			else {
				p -= size(left[u]) + 1;
				u = right[u];
			}
		}
		while (u != root) {
			u = pv[u];
			refresh<false>(u);
		}
	}
	// O(log(n))
	void _update(int root, int ql, int qr, const U &f) {
		static_assert(HAS_UPDATE);
		if (!~root || qr <= 0 || size(root) <= ql)
			return;
		if (ql <= 0 && size(root) <= qr) {
			data[root] = UT(f, data[root]);
			lazy[root] = UU(f, lazy[root]);
			refresh<false>(root);
			return;
		}
		push(root);
		if (ql < size(left[root]))
			_update(left[root], ql, qr, f);
		if (ql <= size(left[root]) && size(left[root]) + 1 <= qr)
			data[root] = UT(f, data[root]);
		if (size(left[root]) + 1 < qr)
			_update(right[root], ql - size(left[root]) - 1, qr - size(left[root]) - 1, f);
		refresh<false>(root);
	}
	// O(log(n))
	void update(int root, int ql, int qr, const U &f) {
		static_assert(HAS_UPDATE);
		assert(0 <= ql && ql <= qr && qr <= size(root));
		if (ql == qr)
			return;
		_update(root, ql, qr, f);
	}
	// O(log(n))
	void _flip(int root, int ql, int qr) {
		static_assert(HAS_FLIP);
		push(root);
		if (qr <= size(left[root])) {
			_flip(left[root], ql, qr);
			refresh<false>(root);
		} else if (size(left[root]) + 1 <= ql) {
			_flip(right[root], ql - size(left[root]) - 1, qr - size(left[root]) - 1);
			refresh<false>(root);
		} else {
			auto [ar, br] = split_by_order(right[root], qr - size(left[root]) - 1);
			auto [al, bl] = split_by_order(left[root], ql);
			if (~bl) {
				push(bl);
				swap(left[bl], right[bl]);
				lazy_flip[bl] ^= 1;
				refresh<false>(bl);
			}
			if (~ar) {
				push(ar);
				swap(left[ar], right[ar]);
				lazy_flip[ar] ^= 1;
				refresh<false>(ar);
			}
			left[root] = append(al, ar);
			right[root] = append(bl, br);
			refresh(root);
		}
	}
	// O(log(n))
	void flip(int root, int ql, int qr) {
		static_assert(HAS_FLIP);
		assert(0 <= ql && ql <= qr && qr <= size(root));
		if (!~root || qr - ql <= 1)
			return;
		_flip(root, ql, qr);
	}
	// pred(sum[ql, r)) is T, T, ..., T, F, F, ..., F
	// Returns max r with T
	// O(log(n))
	int max_pref(int u, int ql, auto pred) {
		static_assert(HAS_QUERY);
		int n = size(u);
		assert(0 <= ql && ql <= n && pred(T_id));
		if (ql == n)
			return n;
		T sum = T_id;
		auto recurse = [&](auto self, int u, int l) -> int {
			int r = l + size(u);
			if (!~u || r <= ql)
				return n;
			if (ql <= l && pred(TT(sum, subtr_data[u]))) {
				sum = TT(sum, subtr_data[u]);
				return n;
			}
			push(u);
			if (auto p = self(self, left[u], l); p < n)
				return p;
			l += size(left[u]);
			return ql <= l && !pred(sum = TT(sum, data[u])) ? l : self(self, right[u], l + 1);
		};
		return recurse(recurse, u, 0);
	}
	// pred(sum[l, qr)) is F, F, ..., F, T, T, ..., T
	// Returns min l with T
	// O(log(n))
	int max_suff(int u, int qr, auto pred) {
		static_assert(HAS_QUERY);
		int n = size(u);
		assert(0 <= qr && qr <= n && pred(T_id));
		if (qr == 0)
			return 0;
		T sum = T_id;
		auto recurse = [&](auto self, int u, int r) -> int {
			int l = r - size(u);
			if (!~u || qr <= l)
				return 0;
			if (r <= qr && pred(TT(subtr_data[u], sum))) {
				sum = TT(subtr_data[u], sum);
				return 0;
			}
			push(u);
			if (auto p = self(self, right[u], r); p > 0)
				return p;
			r -= size(right[u]);
			return r <= qr && !pred(sum = TT(data[u], sum)) ? r : self(self, left[u], r - 1);
		};
		return recurse(recurse, u, n);
	}
#undef ifQ
#undef ifU
#undef ifF
#undef ifNC
};

#include <bits/stdc++.h>
using namespace std;

namespace fastio {
static constexpr uint32_t SZ = 1 << 17;
char ibuf[SZ];
char obuf[SZ];
uint32_t pil = 0, pir = 0, por = 0;

struct Pre {
	char num[40000];
	constexpr Pre() : num() {
		for (int i = 0; i < 10000; i++) {
			int n = i;
			for (int j = 3; j >= 0; j--) {
				num[i * 4 + j] = n % 10 + '0';
				n /= 10;
			}
		}
	}
} constexpr pre;

__attribute__((target("avx2"), optimize("O3"))) inline void load() {
	memcpy(ibuf, ibuf + pil, pir - pil);
	pir = pir - pil + fread(ibuf + pir - pil, 1, SZ - pir + pil, stdin);
	pil = 0;
}

__attribute__((target("avx2"), optimize("O3"))) inline void flush() {
	fwrite(obuf, 1, por, stdout);
	por = 0;
}

inline void rd(char &c) { c = ibuf[pil++]; }

template <typename T> __attribute__((target("avx2"), optimize("O3"))) inline void rd(T &x) {
	if (pil + 32 > pir)
		load();
	char c;
	do
		rd(c);
	while (c < '-');
	bool minus = 0;
	if constexpr (is_signed<T>::value) {
		if (c == '-') {
			minus = 1;
			rd(c);
		}
	}
	x = 0;
	while (c >= '0') {
		x = x * 10 + (c & 15);
		rd(c);
	}
	if constexpr (is_signed<T>::value) {
		if (minus)
			x = -x;
	}
}

inline void wt(char c) { obuf[por++] = c; }
template <typename T> __attribute__((target("avx2"), optimize("O3"))) inline void wt(T x) {
	if (por + 32 > SZ)
		flush();
	if (!x) {
		wt('0');
		return;
	}
	if constexpr (is_signed<T>::value) {
		if (x < 0) {
			wt('-');
			x = -x;
		}
	}
	if (x >= 10000000000000000) {
		uint32_t r1 = x % 100000000;
		uint64_t q1 = x / 100000000;
		if (x >= 1000000000000000000) {
			uint32_t n1 = r1 % 10000;
			uint32_t n2 = r1 / 10000;
			uint32_t n3 = q1 % 10000;
			uint32_t r2 = q1 / 10000;
			uint32_t n4 = r2 % 10000;
			uint32_t q2 = r2 / 10000;
			memcpy(obuf + por + 15, pre.num + (n1 << 2), 4);
			memcpy(obuf + por + 11, pre.num + (n2 << 2), 4);
			memcpy(obuf + por + 7, pre.num + (n3 << 2), 4);
			memcpy(obuf + por + 3, pre.num + (n4 << 2), 4);
			memcpy(obuf + por, pre.num + (q2 << 2) + 1, 3);
			por += 19;
		} else if (x >= 100000000000000000) {
			uint32_t n1 = r1 % 10000;
			uint32_t n2 = r1 / 10000;
			uint32_t n3 = q1 % 10000;
			uint32_t r2 = q1 / 10000;
			uint32_t n4 = r2 % 10000;
			uint32_t q2 = r2 / 10000;
			uint32_t q3 = (q2 * 205) >> 11;
			uint32_t r3 = q2 - q3 * 10;
			memcpy(obuf + por + 14, pre.num + (n1 << 2), 4);
			memcpy(obuf + por + 10, pre.num + (n2 << 2), 4);
			memcpy(obuf + por + 6, pre.num + (n3 << 2), 4);
			memcpy(obuf + por + 2, pre.num + (n4 << 2), 4);
			obuf[por + 1] = '0' + r3;
			obuf[por + 0] = '0' + q3;
			por += 18;
		} else {
			uint32_t n1 = r1 % 10000;
			uint32_t n2 = r1 / 10000;
			uint32_t n3 = static_cast<uint32_t>(q1) % 10000;
			uint32_t r2 = static_cast<uint32_t>(q1) / 10000;
			uint32_t n4 = r2 % 10000;
			uint32_t q2 = r2 / 10000;
			memcpy(obuf + por + 13, pre.num + (n1 << 2), 4);
			memcpy(obuf + por + 9, pre.num + (n2 << 2), 4);
			memcpy(obuf + por + 5, pre.num + (n3 << 2), 4);
			memcpy(obuf + por + 1, pre.num + (n4 << 2), 4);
			obuf[por + 0] = '0' + q2;
			por += 17;
		}
	} else {
		int i = 8;
		char buf[12];
		while (x >= 10000) {
			memcpy(buf + i, pre.num + (x % 10000) * 4, 4);
			x /= 10000;
			i -= 4;
		}
		if (x < 100) {
			if (x < 10) {
				wt(char('0' + x));
			} else {
				obuf[por + 0] = '0' + x / 10;
				obuf[por + 1] = '0' + x % 10;
				por += 2;
			}
		} else {
			if (x < 1000) {
				memcpy(obuf + por, pre.num + (x << 2) + 1, 3);
				por += 3;
			} else {
				memcpy(obuf + por, pre.num + (x << 2), 4);
				por += 4;
			}
		}
		memcpy(obuf + por, buf + i + 4, 8 - i);
		por += 8 - i;
	}
}

struct Dummy {
	Dummy() { atexit(flush); }
} dummy;

} // namespace fastio
using fastio::rd;
using fastio::wt;
int ans[MAXN];

__attribute__((target("avx2"), optimize("O3"))) int main() {
	int n;
	rd(n);
	vector<int> a(n);
	vector<lint> sum(n + 1);
	vector<vector<array<int, 3>>> ins(n);
	vector<vector<int>> del(n);
	for (auto &x : a)
		rd(x);
	for (int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + a[i - 1];
	int q;
	rd(q);
	for (int i = 0; i < q; i++) {
		int l, r, x;
		rd(l);
		rd(r);
		rd(x);
		int nr = upper_bound(all(sum), abs(x) + sum[l - 1]) - sum.begin() - 1;
		nr = min(r, nr);
		int z = sum[nr] - sum[l - 1];
		if (x <= 0)
			x += z;
		else
			x -= z;
		if (nr == r) {
			ans[i] = x;
			continue;
		} else {
			l = nr + 1;
		}
		ins[l - 1].push_back({x, r - 1, i});
	}
	auto _TT = [&](pi a, pi b) -> pi { return a; };
	auto _UT = [&](int a, pi b) -> pi { return pi{a + b[0], b[1]}; };
	auto _UU = [&](int a, int b) -> int { return a + b; };
	auto _FlipT = [&](pi a) -> pi { return a; };
	auto treap = treap_base<false, true, false, true, pi, int, decltype(_TT), decltype(_UU), decltype(_UT), decltype(_FlipT)>(_TT, pi{0, 0}, _UU, 0, _UT, _FlipT);
	int rt = -1;
	for (int i = 0; i < n; i++) {
		for (auto &[x, r, idx] : ins[i]) {
			int nd = treap.new_node(pi{x, idx});
			del[r].push_back(nd);
			rt = treap.insert_node_by_key(rt, nd);
		}
		auto [r0, r1] = treap.split_by_key(rt, pi{0, int(1e9)});
		treap.update(r0, 0, treap.size(r0), 1ll * a[i]);
		treap.update(r1, 0, treap.size(r1), -1ll * a[i]);
		rt = treap.unite_by_key(r0, r1);
		for (auto &nd : del[i]) {
			int z = treap.node_order(rt, nd);
			rt = treap.erase_by_order(rt, z, ans);
		}
	}
	for (int i = 0; i < q; i++) {
		wt(ans[i]);
		wt('\n');
	}
}
