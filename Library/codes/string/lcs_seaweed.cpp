// Unit Monge Multiplication of two permutations.
// https://judge.yosupo.jp/submission/70214

namespace unitMongeMult {
using iter = typename vector<int>::iterator;
void unit_monge_dmul(const int n, iter stack, const iter a, const iter b) {
	if (n == 1) {
		stack[0] = 0;
		return;
	}

	const iter c_row = stack;
	stack += n;
	const iter c_col = stack;
	stack += n;

	const auto map = [=](const int len, const auto f, const auto g) {
		const iter a_h = stack + 0 * len;
		const iter a_m = stack + 1 * len;
		const iter b_h = stack + 2 * len;
		const iter b_m = stack + 3 * len;
		const auto split = [=](const iter v, iter v_h, iter v_m) {
			for (int i = 0; i < n; i++) {
				if (f(v[i])) {
					*v_h = g(v[i]);
					++v_h;
					*v_m = i;
					++v_m;
				}
			}
		};
		split(a, a_h, a_m);
		split(b, b_h, b_m);
		const iter c = stack + 4 * len;
		unit_monge_dmul(len, c, a_h, b_h);

		for (int i = 0; i < len; i++) {
			const int row = a_m[i];
			const int col = b_m[c[i]];
			c_row[row] = col;
			c_col[col] = row;
		}
	};
	const int mid = n / 2;
	map(
		mid, [mid](const int x) { return x < mid; }, [](const int x) { return x; });
	map(
		n - mid, [mid](const int x) { return x >= mid; }, [mid](const int x) { return x - mid; });

	class d_itr {
	  public:
		int delta;
		int col;
		d_itr() : delta(0), col(0) {}
	};
	int row = n;
	const auto right = [&](d_itr &it) {
		if (b[it.col] < mid) {
			if (c_col[it.col] >= row) {
				it.delta += 1;
			}
		} else {
			if (c_col[it.col] < row) {
				it.delta += 1;
			}
		}

		it.col += 1;
	};
	const auto up = [&](d_itr &it) {
		if (a[row] < mid) {
			if (c_row[row] >= it.col) {
				it.delta -= 1;
			}
		} else {
			if (c_row[row] < it.col) {
				it.delta -= 1;
			}
		}
	};
	d_itr neg, pos;

	while (row != 0) {
		while (pos.col != n) {
			d_itr temp = pos;
			right(temp);

			if (temp.delta == 0) {
				pos = temp;
			} else {
				break;
			}
		}

		row -= 1;
		up(neg);
		up(pos);

		while (neg.delta != 0) {
			right(neg);
		}

		if (neg.col > pos.col) {
			c_row[row] = pos.col;
		}
	}
}
vector<int> unit_monge_dmul(vector<int> a, vector<int> b) {
	const int n = a.size();
	vector<int> b_inv(n);
	for (int i = 0; i < n; i++)
		b_inv[b[i]] = i;
	std::swap(b, b_inv);

	vector<int> c([](int n) {
		int ret = 0;

		while (n > 1) {
			ret += 2 * n;
			n = (n + 1) / 2;
			ret += 4 * n;
		}

		ret += 1;
		return ret;
	}(n));
	unit_monge_dmul(n, c.begin(), a.begin(), b.begin());
	c.resize(n);

	return c;
}
} // namespace unitMongeMult

// Generate Seaweed Matrix of A and I(n).

vector<int> make_seaweed(vector<int> &a) {
	if (sz(a) == 1) {
		return vector<int>{0, 1};
	}
	int n = sz(a);
	int m = n / 2;
	vector<int> l, r, il, ir;
	for (int i = 0; i < n; i++) {
		if (a[i] < m) {
			l.push_back(a[i]);
			il.push_back(i);
		} else {
			r.push_back(a[i] - m);
			ir.push_back(i);
		}
	}
	auto rec1 = make_seaweed(l);
	auto rec2 = make_seaweed(r);
	for (auto &z : rec1) {
		if (z < sz(l))
			z = il[z];
		else
			z = n + z - sz(l);
	}
	for (auto &z : rec2) {
		if (z < sz(r))
			z = ir[z];
		else
			z = n + (z - sz(r));
	};
	vector<int> p1(2 * n), p2(2 * n);
	{
		for (int i = 0; i < sz(r); i++)
			p1[i] = i;
		for (int i = sz(r); i < n; i++)
			p1[i] = sz(r) + rec1[i - sz(r)];
		for (int i = n; i < 2 * n; i++)
			p1[i] = i - n + sz(r);
	}
	{
		for (int i = 0; i < sz(r); i++)
			p2[i] = rec2[i];
		for (int i = sz(r); i < sz(r) + n; i++)
			p2[i] = i - sz(r);
		for (int i = sz(r) + n; i < 2 * n; i++)
			p2[i] = i;
	}
	int i0 = 0, i1 = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] < m)
			p1[i + n] = rec1[i0 + sz(l)] + sz(r), i0++;
		else
			p2[i + sz(r)] = rec2[i1 + sz(r)], i1++;
	}
	return unitMongeMult::unit_monge_dmul(p1, p2);
}
