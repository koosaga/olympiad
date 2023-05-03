// Decremental convex hull in O(n log n)
// From "Applications of a semi-dynamic convex hull algorithm" by J. Hershberger and S. Suri
// Credit: dacin21 (https://judge.yosupo.jp/submission/21685)

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
		return a.x * b.y + a.y * b.y;
	}
	friend lint cross(Point const&a, Point const&b) {
		return a.x * b.y - a.y * b.x;
	}
	friend bool operator<(Point const&a, Point const&b) {
		return tie(a.x, a.y) < tie(b.x, b.y);
	}

	lint x = 0, y = 0;
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
				// if >= 0, then the hull contains boundary points
				return ccw(a, b, c) >= 0;
			});
		} else { // l and r to the left of actual bridge
			tie(l, r) = find_bridge(l, r,
			[](Link * x) { return x->next; },
			[&](Point const & a, Point const & b, Point const & c) {
				// if <= 0, then the hull contains boundary points
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