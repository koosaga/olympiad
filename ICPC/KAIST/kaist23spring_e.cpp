#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXT = 530000;

struct node {
	int l[2], r[2], opt[2], sum;
	node() { l[0] = l[1] = r[0] = r[1] = opt[0] = opt[1] = sum = 0; }
	node(int x) {
		l[0] = l[1] = r[0] = r[1] = opt[0] = opt[1] = 0;
		sum = 1;
		l[x] = r[x] = opt[x] = 1;
	}
	node operator+(const node &nd) const {
		node ret;
		ret.sum = sum + nd.sum;
		for (int i = 0; i < 2; i++) {
			ret.l[i] = (l[i] == sum ? (sum + nd.l[i]) : l[i]);
			ret.r[i] = (nd.r[i] == nd.sum ? (nd.sum + r[i]) : nd.r[i]);
			ret.opt[i] = max({opt[i], nd.opt[i], r[i] + nd.l[i]});
		}
		return ret;
	}
} tree[MAXT];

int lim;
void init(string &str) {
	int n = sz(str);
	for (lim = 1; lim <= n; lim <<= 1)
		;
	for (int i = 0; i < n; i++) {
		tree[i + lim] = node(str[i] - '0');
	}
	for (int i = lim - 1; i; i--)
		tree[i] = tree[2 * i] + tree[2 * i + 1];
}

void update(int pos, int v) {
	pos += lim;
	tree[pos] = node(v);
	while (pos > 1) {
		pos >>= 1;
		tree[pos] = tree[2 * pos] + tree[2 * pos + 1];
	}
}

node query(int s, int e) {
	s += lim;
	e += lim;
	node L, R;
	while (s < e) {
		if (s % 2 == 1)
			L = L + tree[s++];
		if (e % 2 == 0)
			R = tree[e--] + R;
		s >>= 1;
		e >>= 1;
	}
	if (s == e)
		L = L + tree[s];
	return L + R;
}

int find_first(int s, int e, int ps, int pe, int p, int t, int v) {
	int l = s, r = e;
	while (l != r) {
		int m = (l + r) / 2;
		if (query(s, m).opt[t] < v)
			l = m + 1;
		else
			r = m;
	}
	return (l + 1) - v;
}

int find_last(int s, int e, int ps, int pe, int p, int t, int v) {
	int l = s, r = e;
	while (l != r) {
		int m = (l + r) / 2;
		if (query(m + 1, e).opt[t] < v)
			r = m;
		else
			l = m + 1;
	}
	return l;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	string str;
	cin >> str;
	init(str);
	bool debug = 0;
	auto printHalfOpen = [&](int x, int y, int t1, int t2) {
		if (debug) {
			int c0 = 0, c1 = 0, a0 = 0, a1 = 0;
			for (int i = x; i < y; i++) {
				if (str[i] == '0')
					c0++, c1 = 0;
				else
					c1++, c0 = 0;
				a0 = max(a0, c0);
				a1 = max(a1, c1);
			}
			if (!(t1 == a0 && t2 == a1)) {
				cout << t1 << " " << a0 << " " << t2 << " " << a1 << endl;
				assert(0);
			}
		}
		cout << x + 1 << " " << y << "\n";
	};
	while (q--) {
		int t;
		cin >> t;
		if (t == 1) {
			int p, v;
			cin >> p >> v;
			update(p - 1, v);
			str[p - 1] = v + '0';
		} else {
			int l, r, x, y;
			cin >> l >> r >> x >> y;
			l--;
			r--;
			auto quer = query(l, r);
			if (quer.opt[0] < x || quer.opt[1] < y || (x + y == 0)) {
				cout << "-1\n";
				continue;
			}
			if (x == 0) {
				auto i1 = find_first(l, r, 0, n - 1, 1, 1, y);
				printHalfOpen(i1, i1 + y, x, y);
				continue;
			}
			if (y == 0) {
				auto i1 = find_first(l, r, 0, n - 1, 1, 0, x);
				printHalfOpen(i1, i1 + x, x, y);
				continue;
			}
			while (l != r) {
				int m = (l + r) / 2;
				auto i1 = query(l, m);
				auto i2 = query(m + 1, r);
				if (i1.opt[0] >= x && i1.opt[1] >= y) {
					r = m;
				} else if (i2.opt[0] >= x && i2.opt[1] >= y) {
					l = m + 1;
				} else {
					if (i1.opt[0] < x) {
						if (i1.opt[1] >= y) {
							// there is some large y in left.
							// you never have obstacles, any case.
							// match leftward.
							int i1 = find_first(l, r, 0, n - 1, 1, 0, x); // first block
							int i2 = find_last(l, i1, 0, n - 1, 1, 1, y); // last block
							if (debug)
								cout << "Case 1\n";
							printHalfOpen(i2, i1 + x, x, y);
						} else if (i2.opt[1] >= y) {
							// means, no >= x rightward
							// take leftmost y from i2 and collapse leftward
							int i2 = find_last(l, r, 0, n - 1, 1, 0, x);   // last block
							int i1 = find_first(i2, r, 0, n - 1, 1, 1, y); // first block
							if (debug)
								cout << "Case 2\n";
							printHalfOpen(i2, i1 + y, x, y);

						} else {
							// the key is in middle.
							int i1 = find_last(l, r, 0, n - 1, 1, 1, y);  // last block
							int i2 = find_first(l, r, 0, n - 1, 1, 0, x); // first block
							if (debug)
								cout << "Case 3\n";
							printHalfOpen(i1, i2 + x, x, y);
						}
						break;
					} else if (i1.opt[1] < y) {
						// same thing...
						if (i1.opt[0] >= x) {
							// there is some large y in left.
							// you never have obstacles, any case.
							// match leftward.
							int i1 = find_first(l, r, 0, n - 1, 1, 1, y); // first block
							int i2 = find_last(l, i1, 0, n - 1, 1, 0, x); // last block
							if (debug)
								cout << "Case 1b\n";
							printHalfOpen(i2, i1 + y, x, y);
						} else if (i2.opt[0] >= x) {
							// means, no >= x rightward
							// take leftmost y from i2 and collapse leftward
							int i2 = find_last(l, r, 0, n - 1, 1, 1, y);   // last block
							int i1 = find_first(i2, r, 0, n - 1, 1, 0, x); // first block
							if (debug)
								cout << "Case 2b\n";
							printHalfOpen(i2, i1 + x, x, y);
						} else {
							// the key is in middle.
							int i1 = find_last(l, r, 0, n - 1, 1, 0, x);  // last block
							int i2 = find_first(l, r, 0, n - 1, 1, 1, y); // first block
							if (debug)
								cout << "Case 3b\n";
							printHalfOpen(i1, i2 + y, x, y);
						}
						break;
					} else
						assert(0);
				}
			}
		}
	}
}