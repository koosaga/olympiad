#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 150005;

// Treap by Aeren
// T: data type, U: lazy type.
// TT: usual addition
// UU: combination of lazy (new, old)
// UT: lazy to the data (new, old)

template <bool HAS_QUERY, bool HAS_UPDATE, bool HAS_FLIP, bool IS_COMMUTATIVE, class T, class U, class F1, class F2,
		  class F3, class F4>
struct treap_base {
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
	treap_base(F1 TT, T T_id, F2 UU, U U_id, F3 UT, F4 FlipT = plus<>())
		: TT(TT), T_id(T_id), UU(UU), U_id(U_id), UT(UT), FlipT(FlipT) {}
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
		if constexpr (UPDATE_STRUCTURE)
			internal_size[u] = 1;
		ifQ subtr_data[u] = T_id;
		if (auto v = left[u]; ~v) {
			if constexpr (UPDATE_STRUCTURE) {
				pv[v] = u;
				internal_size[u] += internal_size[v];
			}
			ifQ {
				auto x = subtr_data[v];
				ifU if (lazy[u] != U_id) x = UT(lazy[u], x);
				ifF ifNC if (lazy_flip[u]) x = FlipT(x);
				subtr_data[u] = x;
			}
		}
		ifQ subtr_data[u] = TT(subtr_data[u], data[u]);
		if (auto w = right[u]; ~w) {
			if constexpr (UPDATE_STRUCTURE) {
				pv[w] = u;
				internal_size[u] += internal_size[w];
			}
			ifQ {
				auto x = subtr_data[w];
				ifU if (lazy[u] != U_id) x = UT(lazy[u], x);
				ifF ifNC if (lazy_flip[u]) x = FlipT(x);
				subtr_data[u] = TT(subtr_data[u], x);
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
	template <class Compare> int insert_by_key(int root, const T &x, Compare cmp) {
		return insert_node_by_key(root, new_node(x), cmp);
	}
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
	int erase_by_order(int root, int pos) {
		assert(~root);
		push(root);
		if (size(left[root]) == pos) {
			dead_node.push_back(root);
			return append(left[root], right[root]);
		}
		if (size(left[root]) < pos)
			right[root] = erase_by_order(right[root], pos - size(left[root]) - 1);
		else
			left[root] = erase_by_order(left[root], pos);
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
	// O(# of elements erased)
	void erase(int root) {
		if (!~root)
			return;
		dead_node.push_back(root);
		for (auto beg = (int)dead_node.size() - 1; beg < (int)dead_node.size(); ++beg) {
			int u = dead_node[beg];
			if (~left[u])
				dead_node.push_back(left[u]);
			if (~right[u])
				dead_node.push_back(right[u]);
		}
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
	template <class V> int build(const vector<V> &a) {
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

vector<vector<pi>> gph;
vector<int> C;
vector<array<int, 3>> edges;

lint solve(int x, int p) {
	vector<lint> subs;
	for (auto &[w, y] : gph[x]) {
		if (y != p)
			subs.push_back(solve(y, x) + edges[w][2]);
	}
	sort(all(subs));
	if (sz(subs) < C[x])
		return 1e18;
	if (C[x] == 0)
		return 0;
	return subs[C[x] - 1];
}

int par[MAXN], pae[MAXN], dep[MAXN], sub[MAXN];

void dfs(int x, int p) {
	sub[x] = 1;
	for (auto &[i, y] : gph[x]) {
		par[y] = x;
		pae[y] = edges[i][2];
		dep[y] = dep[x] + 1;
		gph[y].erase(find(all(gph[y]), pi{i, x}));
		dfs(y, x);
		sub[x] += sub[y];
	}
	sort(all(gph[x]), [&](pi a, pi b) { return sub[a[1]] > sub[b[1]]; });
}

int din[MAXN], dout[MAXN], chn[MAXN], csz[MAXN], piv;
vector<int> ord;

void hld(int x) {
	din[x] = piv++;
	csz[chn[x]]++;
	ord.push_back(x);
	if (sz(gph[x])) {
		chn[gph[x][0][1]] = chn[x];
		hld(gph[x][0][1]);
		for (int i = 1; i < sz(gph[x]); i++) {
			chn[gph[x][i][1]] = gph[x][i][1];
			hld(gph[x][i][1]);
		}
	}
	dout[x] = piv;
}

auto _TT = [](lint a, lint b) -> lint { return a + b; };
auto _UU = [](bool a, bool b) -> lint { return b; };
auto _UT = [](bool a, lint b) -> lint { return b; };
auto _FlipT = [](lint a) -> lint { return a; };

struct func {
	lint x1, y1, x2, y2;
	func() {
		x1 = y1 = -1e18;
		x2 = y2 = 1e18;
	}
	func(lint x) {
		x1 = x2 = 0;
		y1 = y2 = x;
	}
	lint f(lint x) {
		if (x <= x1)
			return y1;
		if (x >= x2)
			return y2;
		return y1 + (x - x1);
	}
	func operator+(func g) {
		lint s = max(y1, g.x1);
		lint e = min(y2, g.x2);
		if (s >= e) {
			return func(g.f(y1));
		}
		func ret;
		ret.x1 = x1 + (s - y1);
		ret.x2 = x2 - (y2 - e);
		assert(f(ret.x1) == s);
		assert(f(ret.x2) == e);
		ret.y1 = g.f(s);
		ret.y2 = g.f(e);
		assert(ret.y2 - ret.y1 == ret.x2 - ret.x1);
		return ret;
	}
};

func maxF(lint x) {
	func ret;
	ret.x1 = ret.y1 = x;
	ret.x2 = ret.y2 = 1e18;
	return ret;
}

func minF(lint x) {
	func ret;
	ret.x1 = ret.y1 = -1e18;
	ret.x2 = ret.y2 = x;
	return ret;
}

func add(lint x) {
	func ret;
	ret.y1 += x;
	ret.y2 += x;
	return ret;
}

namespace atcoder {

// @return same with std::bit::bit_ceil
unsigned int bit_ceil(unsigned int n) {
	unsigned int x = 1;
	while (x < (unsigned int)(n))
		x *= 2;
	return x;
}

// @param n `1 <= n`
// @return same with std::bit::countr_zero
int countr_zero(unsigned int n) {
#ifdef _MSC_VER
	unsigned long index;
	_BitScanForward(&index, n);
	return index;
#else
	return __builtin_ctz(n);
#endif
}

// @param n `1 <= n`
// @return same with std::bit::countr_zero
constexpr int countr_zero_constexpr(unsigned int n) {
	int x = 0;
	while (!(n & (1 << x)))
		x++;
	return x;
}
template <class S, auto op, auto e, class F, auto mapping, auto composition, auto id> struct lazy_segtree {
	static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>, "op must work as S(S, S)");
	static_assert(std::is_convertible_v<decltype(e), std::function<S()>>, "e must work as S()");
	static_assert(std::is_convertible_v<decltype(mapping), std::function<S(F, S)>>, "mapping must work as S(F, S)");
	static_assert(std::is_convertible_v<decltype(composition), std::function<F(F, F)>>,
				  "composition must work as F(F, F)");
	static_assert(std::is_convertible_v<decltype(id), std::function<F()>>, "id must work as F()");

  public:
	lazy_segtree() : lazy_segtree(0) {}
	explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
	explicit lazy_segtree(const std::vector<S> &v) : _n(int(v.size())) {
		size = (int)bit_ceil((unsigned int)(_n));
		log = countr_zero((unsigned int)size);
		d = std::vector<S>(2 * size, e());
		lz = std::vector<F>(size, id());
		for (int i = 0; i < _n; i++)
			d[size + i] = v[i];
		for (int i = size - 1; i >= 1; i--) {
			update(i);
		}
	}

	void set(int p, S x) {
		assert(0 <= p && p < _n);
		p += size;
		for (int i = log; i >= 1; i--)
			push(p >> i);
		d[p] = x;
		for (int i = 1; i <= log; i++)
			update(p >> i);
	}

	S get(int p) {
		assert(0 <= p && p < _n);
		p += size;
		for (int i = log; i >= 1; i--)
			push(p >> i);
		return d[p];
	}

	S prod(int l, int r) {
		assert(0 <= l && l <= r && r <= _n);
		if (l == r)
			return e();

		l += size;
		r += size;

		for (int i = log; i >= 1; i--) {
			if (((l >> i) << i) != l)
				push(l >> i);
			if (((r >> i) << i) != r)
				push((r - 1) >> i);
		}

		S sml = e(), smr = e();
		while (l < r) {
			if (l & 1)
				sml = op(sml, d[l++]);
			if (r & 1)
				smr = op(d[--r], smr);
			l >>= 1;
			r >>= 1;
		}

		return op(sml, smr);
	}

	S all_prod() { return d[1]; }

	void apply(int p, F f) {
		assert(0 <= p && p < _n);
		p += size;
		for (int i = log; i >= 1; i--)
			push(p >> i);
		d[p] = mapping(f, d[p]);
		for (int i = 1; i <= log; i++)
			update(p >> i);
	}
	void apply(int l, int r, F f) {
		assert(0 <= l && l <= r && r <= _n);
		if (l == r)
			return;

		l += size;
		r += size;

		for (int i = log; i >= 1; i--) {
			if (((l >> i) << i) != l)
				push(l >> i);
			if (((r >> i) << i) != r)
				push((r - 1) >> i);
		}

		{
			int l2 = l, r2 = r;
			while (l < r) {
				if (l & 1)
					all_apply(l++, f);
				if (r & 1)
					all_apply(--r, f);
				l >>= 1;
				r >>= 1;
			}
			l = l2;
			r = r2;
		}

		for (int i = 1; i <= log; i++) {
			if (((l >> i) << i) != l)
				update(l >> i);
			if (((r >> i) << i) != r)
				update((r - 1) >> i);
		}
	}

	template <bool (*g)(S)> int max_right(int l) {
		return max_right(l, [](S x) { return g(x); });
	}
	template <class G> int max_right(int l, G g) {
		assert(0 <= l && l <= _n);
		assert(g(e()));
		if (l == _n)
			return _n;
		l += size;
		for (int i = log; i >= 1; i--)
			push(l >> i);
		S sm = e();
		do {
			while (l % 2 == 0)
				l >>= 1;
			if (!g(op(sm, d[l]))) {
				while (l < size) {
					push(l);
					l = (2 * l);
					if (g(op(sm, d[l]))) {
						sm = op(sm, d[l]);
						l++;
					}
				}
				return l - size;
			}
			sm = op(sm, d[l]);
			l++;
		} while ((l & -l) != l);
		return _n;
	}

	template <bool (*g)(S)> int min_left(int r) {
		return min_left(r, [](S x) { return g(x); });
	}
	template <class G> int min_left(int r, G g) {
		assert(0 <= r && r <= _n);
		assert(g(e()));
		if (r == 0)
			return 0;
		r += size;
		for (int i = log; i >= 1; i--)
			push((r - 1) >> i);
		S sm = e();
		do {
			r--;
			while (r > 1 && (r % 2))
				r >>= 1;
			if (!g(op(d[r], sm))) {
				while (r < size) {
					push(r);
					r = (2 * r + 1);
					if (g(op(d[r], sm))) {
						sm = op(d[r], sm);
						r--;
					}
				}
				return r + 1 - size;
			}
			sm = op(d[r], sm);
		} while ((r & -r) != r);
		return 0;
	}

  private:
	int _n, size, log;
	std::vector<S> d;
	std::vector<F> lz;

	void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
	void all_apply(int k, F f) {
		d[k] = mapping(f, d[k]);
		if (k < size)
			lz[k] = composition(f, lz[k]);
	}
	void push(int k) {
		all_apply(2 * k, lz[k]);
		all_apply(2 * k + 1, lz[k]);
		lz[k] = id();
	}
};
} // namespace atcoder
func TT(func a, func b) { return a + b; }
func UT(int a, func b) { return b; }
int UU(int a, int b) { return a + b; }
func ET() { return func(); }
int EU() { return 0; }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	auto treap =
		treap_base<true, false, false, true, lint, lint, decltype(_TT), decltype(_UU), decltype(_UT), decltype(_FlipT)>(
			_TT, 0, _UU, 0, _UT, _FlipT);
	int n;
	cin >> n;
	cr(gph, n);
	for (int i = 0; i < n - 1; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--;
		v--;
		gph[u].push_back({i, v});
		gph[v].push_back({i, u});
		edges.push_back({u, v, w});
	}
	cr(C, n);
	for (auto &x : C)
		cin >> x;
	dfs(0, -1);
	hld(0);
	for (auto &[u, v, w] : edges) {
		if (par[u] == v)
			swap(u, v);
	}
	vector<int> rt(n);
	vector<pi> rng(n);
	vector<lint> dp(n);
	vector<func> values(n), rvalues(n);
	atcoder::lazy_segtree<func, TT, ET, int, UT, UU, EU> seg1(n), seg2(n);
	auto pass_chain_fwd = [&](lint x, int l, int r) {
		func fn = seg2.prod(l, r);
		return fn.f(x);
	};
	auto pass_chain_bwd = [&](lint x, int l, int r) {
		func fn = seg1.prod(n - r, n - l);
		return fn.f(x);
	};
	auto recalc = [&](int i) {
		values[din[i]] = maxF(rng[i][0]) + minF(rng[i][1]) + add(pae[i]);
		seg1.set(n - 1 - din[i], values[din[i]]);
		if (din[i] < n - 1) {
			rvalues[din[i]] = maxF(rng[i][0]) + minF(rng[i][1]) + add(pae[ord[din[i] + 1]]);
			seg2.set(din[i], rvalues[din[i]]);
		}
		if (din[i] > 0) {
			rvalues[din[i] - 1] = maxF(rng[ord[din[i] - 1]][0]) + minF(rng[ord[din[i] - 1]][1]) + add(pae[i]);
			seg2.set(din[i] - 1, rvalues[din[i] - 1]);
		}
	};
	auto compute_range = [&](int v) {
		if (C[v] == 0)
			return pi{0, 0};
		int tsz = treap.size(rt[v]);
		pi ret;
		if (C[v] == 1)
			ret[0] = 0;
		else if (C[v] <= tsz + 1)
			ret[0] = treap.query(rt[v], C[v] - 2);
		else
			ret[0] = 1e18;
		if (C[v] <= tsz)
			ret[1] = treap.query(rt[v], C[v] - 1);
		else
			ret[1] = 1e18;
		return ret;
	};
	for (int i = n - 1; i >= 0; i--) {
		vector<lint> elems;
		for (auto &[idx, j] : gph[ord[i]]) {
			if (chn[j] == j) {
				elems.push_back(dp[j]);
			}
		}
		sort(all(elems));
		rt[ord[i]] = treap.build(elems);
		rng[ord[i]] = compute_range(ord[i]);
		recalc(ord[i]);
		if (chn[ord[i]] == ord[i]) {
			int v = ord[i];
			dp[v] = pass_chain_bwd(1e18, din[v], din[v] + csz[v]);
		}
	}
	//	for (int i = 0; i < n; i++)
	//	cout << rng[i][0] << " " << rng[i][1] << " " << dp[i] << endl;
	int q;
	cin >> q;
	while (q--) {
		int t;
		cin >> t;
		if (t == 1) {
			int v, x;
			cin >> v >> x;
			v--;
			C[v] = x;
			while (true) {
				lint pcomp = dp[chn[v]];
				rng[v] = compute_range(v);
				recalc(v);
				dp[chn[v]] = pass_chain_bwd(1e18, din[chn[v]], din[chn[v]] + csz[chn[v]]);
				if (chn[v] == 0)
					break;
				rt[par[chn[v]]] = treap.erase_by_key(rt[par[chn[v]]], pcomp);
				rt[par[chn[v]]] = treap.insert_by_key(rt[par[chn[v]]], dp[chn[v]]);
				v = par[chn[v]];
			}
		}
		if (t == 2) {
			int e, k;
			cin >> e >> k;
			e--;
			int v = edges[e][1];
			pae[v] = k;
			while (true) {
				lint pcomp = dp[chn[v]];
				rng[v] = compute_range(v);
				recalc(v);
				dp[chn[v]] = pass_chain_bwd(1e18, din[chn[v]], din[chn[v]] + csz[chn[v]]);
				if (chn[v] == 0)
					break;
				rt[par[chn[v]]] = treap.erase_by_key(rt[par[chn[v]]], pcomp);
				rt[par[chn[v]]] = treap.insert_by_key(rt[par[chn[v]]], dp[chn[v]]);
				v = par[chn[v]];
			}
		}
		if (t == 3) {
			int v;
			cin >> v;
			v--;
			vector<pi> path;
			while (true) {
				path.push_back({chn[v], v});
				if (chn[v] != 0)
					v = par[chn[v]];
				else
					break;
			}
			reverse(all(path));
			lint ans = 1e18;
			for (int i = 0; i < sz(path); i++) {
				//	cout << "1" << endl;
				auto [u, v] = path[i];
				//	cout << "2" << endl;
				ans = pass_chain_fwd(ans, din[u], din[v]);
				//	cout << "3" << endl;
				lint pcomp;
				//	cout << "4" << endl;
				if (i + 1 < sz(path)) {
					//		cout << "5" << endl;
					int ch = path[i + 1][0];
					//		cout << "6" << endl;
					rt[v] = treap.erase_by_key(rt[v], dp[ch]);
					//	cout << "7" << endl;
				}
				//	cout << "8" << endl;
				if (din[v] - din[u] != csz[u] - 1) {
					//		cout << "9" << endl;
					pcomp = pass_chain_bwd(1e18, din[v] + 1, din[u] + csz[u]);
					//		cout << "10" << endl;
					rt[v] = treap.insert_by_key(rt[v], pcomp);
					//		cout << "11" << endl;
				}
				//		cout << "12" << endl;
				pi gr = compute_range(v);
				//		cout << "13" << endl;
				ans = clamp(ans, gr[0], gr[1]);
				//		cout << "14" << endl;
				if (din[v] - din[u] != csz[u] - 1) {
					//		cout << "15" << endl;
					rt[v] = treap.erase_by_key(rt[v], pcomp);
					//		cout << "16" << endl;
				}
				//	cout << "17" << endl;
				if (i + 1 < sz(path)) {
					//	cout << "18" << endl;
					int ch = path[i + 1][0];
					//	cout << "19" << endl;
					rt[v] = treap.insert_by_key(rt[v], dp[ch]);
					//	cout << "20" << endl;
					ans += pae[ch];
					//	cout << "21" << endl;
				}
				//	cout << "22" << endl;
			}
			//		cout << "23" << endl;
			if (ans > 1e17)
				ans = -1;
			//	cout << "24" << endl;

			cout << ans << "\n";
		}
	}
}