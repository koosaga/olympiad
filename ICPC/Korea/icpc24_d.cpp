#include <bits/stdc++.h>
using namespace std;
mt19937_64 mt_treap(48);
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

template <typename K, typename V> struct treap_node {
	int siz;
	K k;
	V val;
	uint64_t p;

	treap_node *l, *r, *parent;
	treap_node(K _k, V _val) : siz(1), k(_k), val(_val), p(mt_treap()), l(nullptr), r(nullptr), parent(nullptr) {}

	friend int get_sz(treap_node *t) { return (t == nullptr ? 0 : t->siz); }
	friend void upd(treap_node *t) {
		if (t == nullptr)
			return;
		t->siz = 1 + get_sz(t->l) + get_sz(t->r);
	}
	friend void split_key(treap_node *t, treap_node *&l, treap_node *&r, K k) {
		if (t == nullptr) {
			l = nullptr;
			r = nullptr;
		} else if (t->k < k) {
			split_key(t->r, t->r, r, k);
			if (t->r)
				t->r->parent = t;
			l = t;
		} else {
			split_key(t->l, l, t->l, k);
			if (t->l)
				t->l->parent = t;
			r = t;
		}
		if (l)
			l->parent = nullptr;
		if (r)
			r->parent = nullptr;
		upd(t);
	}
	friend void merge(treap_node *&t, treap_node *l, treap_node *r) {
		if (l == nullptr) {
			t = r;
		} else if (r == nullptr) {
			t = l;
		} else if (l->p < r->p) {
			merge(l->r, l->r, r);
			if (l->r)
				l->r->parent = l;
			t = l;
		} else {
			merge(r->l, l, r->l);
			if (r->l)
				r->l->parent = r;
			t = r;
		}
		if (t)
			t->parent = nullptr;
		upd(t);
	}
	friend void pt_helper(treap_node *r) {
		if (r == nullptr)
			return;
		pt_helper(r->l);
		cerr << r->k << ' ';
		pt_helper(r->r);
	}
	friend void pt(treap_node *r) {
		pt_helper(r);
		cerr << '\n';
	}
	friend treap_node *get_left(treap_node *x) {
		while (x && x->l)
			x = x->l;
		return x;
	}
	friend treap_node *get_right(treap_node *x) {
		while (x && x->r)
			x = x->r;
		return x;
	}
	friend treap_node *get_root(treap_node *x) {
		while (x && x->parent)
			x = x->parent;
		return x;
	}
};

const int MAXN = 100005;

struct seg {
	vector<int> tree[MAXN];
	vector<int> fenw[MAXN];
	void init(vector<vector<int>> &v) {
		for (int i = 0; i < sz(v); i++) {
			for (auto &x : v[i]) {
				for (int j = i + 2; j < MAXN; j += j & -j) {
					tree[j].push_back(x);
				}
			}
		}
		for (int i = 1; i < MAXN; i++) {
			sort(all(tree[i]));
			tree[i].resize(unique(all(tree[i])) - tree[i].begin());
			fenw[i].resize(sz(tree[i]) + 2);
		}
	}
	void add(int x, int y, int v) {
		for (int i = x + 2; i < MAXN; i += i & -i) {
			int ypos = lower_bound(all(tree[i]), y) - tree[i].begin() + 1;
			for (int j = ypos; j < sz(fenw[i]); j += j & -j)
				fenw[i][j] += v;
		}
	}
	int query(int x, int l, int r) { // [l + 1, r - 1]
		int ans = 0;
		for (int i = x + 2; i > 0; i -= i & -i) {
			int p1 = lower_bound(all(tree[i]), r) - tree[i].begin();
			int p2 = lower_bound(all(tree[i]), l + 1) - tree[i].begin();
			if (p1 == p2)
				continue;
			for (int j = p1; j > 0; j -= j & -j)
				ans += fenw[i][j];
			for (int j = p2; j > 0; j -= j & -j)
				ans -= fenw[i][j];
		}
		return ans;
	}
} seg;

int main() {
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int N, M, Q;
	cin >> N >> M >> Q;
	vector<pair<int, int>> init_state;
	vector<tuple<char, int, int>> ops;
	vector<pair<int, int>> all_bars;
	for (int l = 0; l < M + Q; l++) {
		int h, a;
		char c;
		if (l < M)
			c = 'A';
		else
			cin >> c;
		assert(c == 'A' || c == 'D');
		cin >> h >> a;
		a--;
		all_bars.push_back({h, a});
		ops.push_back({c, h, a});
	}
	sort(all_bars.begin(), all_bars.end());
	all_bars.erase(unique(all_bars.begin(), all_bars.end()), all_bars.end());
	vector<pair<int, int>> updates;
	vector<tuple<char, int>> queries;
	for (auto [h, a] : all_bars) {
		updates.push_back({a, a + 1});
	}
	for (auto [c, h, a] : ops) {
		int x = lower_bound(all_bars.begin(), all_bars.end(), make_pair(h, a)) - all_bars.begin();
		if (c == 'A') {
			queries.push_back({'r', x});
		} else if (c == 'D') {
			queries.push_back({'f', x});
		} else
			assert(false);
	}

	using node = treap_node<int, int>;

	vector<node *> treaps(N);
	for (int i = 0; i < N; i++) {
		treaps[i] = new node(i, i);
	}
	vector<pair<node *, node *>> swap_nodes;

	int cur = 10 * N;
	for (auto [a, b] : updates) {
		node *x = new node(cur, a);
		cur++;
		node *y = new node(cur, b);
		cur++;
		swap_nodes.push_back({x, y});
		merge(treaps[a], treaps[a], x);
		merge(treaps[b], treaps[b], y);
	}

	vector<int> perm(N);
	for (int i = 0; i < N; i++) {
		perm[i] = i;
	}

	vector<int> init_perm;
	vector<pi> queries_fuck;
	vector<vector<int>> rels(N);

	auto inversion = [&](vector<int> v) {
		vector<int> tree(N + 5);
		lint ans = 0;
		for (int i = 0; i < N; i++) {
			v[i]++;
			for (int j = v[i] + 1; j < N + 5; j += j & -j)
				ans += tree[j];
			for (int j = v[i]; j > 0; j -= j & -j) {
				tree[j]++;
			}
		}
		return ans;
	};
	auto solve = [&]() {
		int n = sz(rels);
		seg.init(rels);
		vector<int> p = init_perm;
		vector<lint> ans;
		for (int i = 0; i < n; i++)
			seg.add(i, p[i], +1);
		lint invs = inversion(init_perm);
		for (auto &[x, y] : queries_fuck) {
			seg.add(x, p[x], -1);
			seg.add(y, p[y], -1);
			lint rec_sum = seg.query(y - 1, min(p[x], p[y]), max(p[x], p[y])) - seg.query(x, min(p[x], p[y]), max(p[x], p[y]));
			if (p[x] < p[y]) {
				invs += 1 + 2 * rec_sum;
			} else {
				invs -= 1 + 2 * rec_sum;
			}
			swap(p[x], p[y]);
			seg.add(x, p[x], +1);
			seg.add(y, p[y], +1);
			ans.push_back(invs);
		}
		return ans;
	};
	int n = sz(perm);
	for (int it = 0; it < sz(queries); it++) {
		if (it == sz(queries) - Q) {
			init_perm = perm;
			for (int i = 0; i < n; i++) {
				rels[i].push_back(perm[i]);
			}
		}
		auto [c, val] = queries[it];
		// assert(val < (int)swap_nodes.size());
		auto [v1, v2] = swap_nodes[val];
		auto root1 = get_root(v1);
		auto root2 = get_root(v2);
		// assert(root1 && root2);
		// assert(root1 != root2);
		int u = get_left(root1)->val;
		int v = get_left(root2)->val;
		if (u > v)
			swap(u, v);
		swap(perm[u], perm[v]);
		if (it >= sz(queries) - Q) {
			rels[u].push_back(perm[u]);
			rels[v].push_back(perm[v]);
			queries_fuck.push_back({u, v});
		}
		node *l1, *r1, *l2, *r2;
		split_key(root1, l1, r1, v1->k);
		split_key(root2, l2, r2, v2->k);
		// assert(get_left(r1) == v1);
		// assert(get_left(r2) == v2);
		merge(root1, l1, r2);
		merge(root2, l2, r1);
		treaps[get_right(root1)->val] = root1;
		treaps[get_right(root2)->val] = root2;
	}
	auto invs = solve();
	for (int x = invs.size() - Q; x < (int)invs.size(); x++) {
		cout << invs[x] << '\n';
	}
}
