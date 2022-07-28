#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 200005;

struct Point {
	Point& operator+=(Point const&o) {
		x += o.x;
		y += o.y;
		return *this;
	}
	Point& operator-=(Point const&o) {
		x -= o.x;
		y -= o.y;
		return *this;
	}
	Point operator-() const {
		return Point{ -x, -y};
	}
	friend Point operator+(Point a, Point const&b) {
		a += b;
		return a;
	}
	friend Point operator-(Point a, Point const&b) {
		a -= b;
		return a;
	}
	friend lint dot(Point const&a, Point const&b) {
		return 1ll * a.x * b.y + 1ll * a.y * b.y;
	}
	friend lint cross(Point const&a, Point const&b) {
		return 1ll * a.x * b.y - 1ll * a.y * b.x;
	}
	friend bool operator<(Point const&a, Point const&b) {
		return tie(a.x, a.y) < tie(b.x, b.y);
	}

	int x = 0, y = 0;
	int idx = 0;
};

int ccw(Point const&a, Point const&b) {
	lint x = cross(a, b);
	return (x > 0) - (x < 0);
}
int ccw(Point const&a, Point const&b, Point const&c) {
	return ccw(b - a, c - a);
}

struct DecrementalUpperHull {
	struct Link {
		Point p;
		Link *prev = nullptr, *next = nullptr;
		int id;
	};
	struct Node {
		Link *chain, *chain_back;
		Link *tangent;
	};
	template<typename S, typename T>
	pair<Link*, Link*> find_bridge(Link*l, Link*r, S next, T convex) {
		while (next(l) || next(r)) {
			if (!next(r) || (next(l) && convex(Point{0, 0}, next(l)->p - l->p, next(r)->p - r->p))) {
				if (convex(l->p, next(l)->p, r->p)) {
					l = next(l);
				} else {
					break;
				}
			} else {
				if (!convex(l->p, r->p, next(r)->p)) {
					r = next(r);
				} else {
					break;
				}
			}
		}
		return {l, r};
	}

	template<bool rev = false>
	void fix_chain(int u, Link*l, Link*r) {
		if (rev) { // l and r to the right of actual bridge
			tie(r, l) = find_bridge(r, l,
			[](Link * x) { return x->prev; },
			[&](Point const & a, Point const & b, Point const & c) {
				return ccw(a, b, c) >= 0;
			});
		} else { // l and r to the left of actual bridge
			tie(l, r) = find_bridge(l, r,
			[](Link * x) { return x->next; },
			[&](Point const & a, Point const & b, Point const & c) {
				return ccw(a, b, c) <= 0;
			});
		}
		tree[u].tangent = l;
		tree[u].chain = tree[2 * u].chain;
		tree[u].chain_back = tree[2 * u + 1].chain_back;
		tree[2 * u].chain = l->next;
		tree[2 * u + 1].chain_back = r->prev;
		if (l->next) {
			l->next->prev = nullptr;
		} else {
			tree[2 * u].chain_back = nullptr;
		}
		if (r->prev) {
			r->prev->next = nullptr;
		} else {
			tree[2 * u + 1].chain = nullptr;
		}
		l->next = r;
		r->prev = l;
	}


	void build(int u, int a, int b) {
		if (b - a == 1) {
			tree[u].chain = tree[u].chain_back = &lists[a];
			tree[u].tangent = nullptr;
			return;
		}
		const int m = a + (b - a) / 2;
		build(2 * u, a, m);
		build(2 * u + 1, m, b);
		auto l = tree[2 * u].chain, r = tree[2 * u + 1].chain;
		fix_chain(u, l, r);
	}

	void rob(int u, int v) {
		tree[u].chain = tree[v].chain;
		tree[v].chain = nullptr;
		tree[u].chain_back = tree[v].chain_back;
		tree[v].chain_back = nullptr;
	}

	void remove(int u, int a, int b, int const&i) {
		if (i < a || i >= b) return;
		// we should never hit a leaf
		assert(b - a > 1);
		const int m = a + (b - a) / 2;
		// one child -> that child contains i
		if (!tree[u].tangent) {
			int v = i < m ? 2 * u : 2 * u + 1;
			tree[v].chain = tree[u].chain;
			tree[v].chain_back = tree[u].chain_back;
			if (i < m) {
				remove(2 * u, a, m, i);
			} else {
				remove(2 * u + 1, m, b, i);
			}
			rob(u, v);
			return;
		}
		// restore hull of children
		auto l = tree[u].tangent, r = l->next;
		l->next = tree[2 * u].chain;
		if (tree[2 * u].chain) {
			tree[2 * u].chain->prev = l;
		} else {
			tree[2 * u].chain_back = l;
		}
		tree[2 * u].chain = tree[u].chain;
		r->prev = tree[2 * u + 1].chain_back;
		if (tree[2 * u + 1].chain_back) {
			tree[2 * u + 1].chain_back->next = r;
		} else {
			tree[2 * u + 1].chain = r;
		}
		tree[2 * u + 1].chain_back = tree[u].chain_back;
		// delete i
		const int v = i < m ? 2 * u : 2 * u + 1;
		// only i
		if (tree[v].chain == tree[v].chain_back && tree[v].chain->id == i) {
			tree[v].chain = tree[v].chain_back = nullptr;
			rob(u, v ^ 1);
			tree[u].tangent = nullptr;
			return;
		}
		if (i < m) {
			if (l->id == i) {
				l = l->next;
			}
			remove(2 * u, a, m, i);
			if (!l) {
				l = tree[2 * u].chain_back;
			}
			fix_chain<true>(u, l, r);
		} else {
			if (r->id == i) {
				r = r->prev;
			}
			remove(2 * u + 1, m, b, i);
			if (!r) {
				r = tree[2 * u + 1].chain;
			}
			fix_chain<false>(u, l, r);
		}
	}

	void remove(int i) {
		// i is the only point
		if (tree[1].chain == tree[1].chain_back) {
			tree[1].chain = tree[1].chain_back = nullptr;
			return;
		}
		remove(1, 0, n, i);
	}

	DecrementalUpperHull(vector<Point> const&v) : n(v.size()), tree(4 * n), lists(n) {
		assert(is_sorted(v.begin(), v.end()));
		for (int i = 0; i < n; ++i) {
			lists[i].p = v[i];
			lists[i].id = i;
		}
		build(1, 0, n);
	}

	vector<int> get_hull() {
		vector<int> ret;
		for (Link* u = tree[1].chain; u; u = u->next) {
			ret.push_back(u->id);
		}
		return ret;
	}

	vector<Point> get_hull_points() {
		vector<Point> ret;
		for (Link* u = tree[1].chain; u; u = u->next) {
			ret.push_back(u->p);
		}
		return ret;
	}

	int n;
	vector<Node> tree;
	vector<Link> lists;
};

vector<int> gph[MAXN];
int sz[MAXN];

void dfs(int x){
	sz[x] = 1;
	for(auto &y : gph[x]){
		gph[y].erase(find(all(gph[y]), x));
		dfs(y);
		sz[x] += sz[y];
	}
	sort(all(gph[x]), [&](const int &a, const int &b){
		return sz[a] > sz[b];
	});
}

int ret[MAXN], ra[MAXN], rb[MAXN];
vector<Point> a, b, NSA, NSB;

void solve(int v, DecrementalUpperHull &dh){
	int point = dh.tree[1].chain_back->p.idx;
	ret[point] = v;
	for(int w = sz(gph[v]) - 1; w > 0; w--){
		vector<Point> npb;
		for(int z = 0; z < sz[gph[v][w]]; z++){
			int pos = dh.tree[1].chain_back->prev->p.idx;
			dh.remove(rb[pos]);
			npb.push_back(NSB[pos]);
		}
		sort(all(npb));
		DecrementalUpperHull ndh(npb);
		for(int j = 0; j < sz(npb); j++) rb[npb[j].idx] = j;
		solve(gph[v][w], ndh);
	}
	if(sz(gph[v])){
		dh.remove(rb[point]);
		solve(gph[v][0], dh);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n; cin >> n;
	for(int i = 0; i < n - 1; i++){
		int u, v; cin >> u >> v;
		u--; v--;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	a.resize(n); b.resize(n);
	for(int i = 0; i < n; i++){
		cin >> a[i].x >> a[i].y;
		b[i].x = -a[i].x;
		b[i].y = -a[i].y;
		a[i].idx = b[i].idx = i;
	}
	NSB = b;
	sort(all(b));
	DecrementalUpperHull  dh(b);
	for(int i = 0; i < n; i++) rb[b[i].idx] = i;
	dfs(0);
	solve(0, dh);
	for(int i = 0; i < n; i++) cout << ret[i]+1 << " ";
}


