#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
lint randint(lint lb, lint ub) { return uniform_int_distribution<lint>(lb, ub)(rng); }

vector<int> perm;
int qcnt = 0;
map<array<int, 3>, vector<pi>> mp;

vector<pi> query(array<int, 3> a) {
	sort(all(a));
	if (mp.count(a))
		return mp[a];
	if (sz(perm)) {
		qcnt++;
		vector<array<int, 3>> ans;
		for (int j = 0; j < 3; j++) {
			int u = a[j], v = a[(j + 1) % 3];
			if (u > v)
				swap(u, v);
			int d = abs(perm[u] - perm[v]);
			d = min(d, sz(perm) - d);
			ans.push_back({d, u, v});
		}
		sort(all(ans));
		vector<pi> ret;
		for (auto &x : ans) {
			if (x[0] == ans[0][0])
				ret.push_back({x[1], x[2]});
		}
		return mp[a] = ret;
	}
	cout << "?";
	for (int j = 0; j < 3; j++)
		cout << " " << a[j];
	cout << endl;
	int r;
	cin >> r;
	vector<pi> ans(r);
	for (auto &[x, y] : ans)
		cin >> x >> y;
	return mp[a] = ans;
}

vector<int> merge(vector<int> a, vector<int> b) {
	if (sz(a) > sz(b))
		swap(a, b);
	if (sz(a) == 0)
		return b;
	if (sz(b) == 1)
		return vector<int>{a[0], b[0]};
	if (sz(a) == 1) {
		auto g = query({a.back(), b[0], b[1]});
		pi w{a.back(), b[0]};
		sort(all(w));
		if (count(all(g), w)) {
			reverse(all(b));
		}
		b.push_back(a[0]);
		return b;
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			if (i == 1 && j == 1) {
				vector<int> c = a;
				for (auto &x : b)
					c.push_back(x);
				return c;
			}
			auto g = query({a.back(), b[0], b[1]});
			pi w{a.back(), b[0]};
			sort(all(w));
			if (count(all(g), w)) {
				vector<int> c = a;
				for (auto &x : b)
					c.push_back(x);
				return c;
			}
			reverse(all(b));
		}
		reverse(all(a));
	}
}

vector<int> sort(vector<int> a) {
	if (sz(a) <= 2)
		return a;
	if (sz(a) == 4) {
		auto g1 = query({a[0], a[1], a[2]});
		if (sz(g1) == 2) {
			return merge(sort({a[0], a[1], a[2]}), {a[3]});
		}
		int a2 = a[0] + a[1] + a[2] - (g1[0][0] + g1[0][1]);
		a[0] = g1[0][0];
		a[1] = g1[0][1];
		a[2] = a2;
		auto g2 = query({a[0], a[1], a[2]});
		if (sz(g2) == 2) {
			return merge(sort({a[0], a[1], a[2]}), {a[3]});
		}
		return merge(sort({a[0], a[1], a[3]}), {a[2]});
	}
	int u = 0, v = 0;
	while (true) {
		shuffle(all(a), mt19937(0x1557));
		while (u == v) {
			u = randint(0, sz(a) - 1);
			v = randint(0, sz(a) - 1);
			u = a[u];
			v = a[v];
		}
		if (u > v)
			swap(u, v);
		vector<int> L = {u}, R = {v};
		bool badcase = false;
		for (auto &w : a) {
			if (u == w || v == w)
				continue;
			auto q = query({u, v, w});
			if (count(all(q), pi{u, v})) {
				q.erase(find(all(q), pi{u, v}));
			}
			if (sz(q) == 0) {
				v = w;
				badcase = true;
				break;
			}
			int is = -1;
			for (int j = 0; j < 2; j++) {
				if (q[0][j] == u)
					is = u;
				if (q[0][j] == v)
					is = v;
			}
			if (is == u)
				L.push_back(w);
			else
				R.push_back(w);
		}
		if (badcase)
			continue;
		L = sort(L);
		R = sort(R);
		return merge(L, R);
	}
}

void solve() {
	mp.clear();
	int n;
	cin >> n;
	vector<int> inv(n);
	if (0) {
		cr(perm, n);
		iota(all(perm), 0);
		shuffle(all(perm), mt19937(0x1557));
		for (int i = 0; i < n; i++)
			inv[perm[i]] = i;
	}
	vector<int> orders(n);
	iota(all(orders), 0);
	int u = 0;
	int v = randint(1, n - 1);
	while (true) {
		shuffle(all(orders), mt19937(0x1557));
		vector<int> L = {u}, R = {v}, M;
		bool badcase = false;
		for (auto &j : orders) {
			if (u != j && v != j) {
				auto q = query({u, v, j});
				if (count(all(q), pi{u, v})) {
					q.erase(find(all(q), pi{u, v}));
				}
				if (sz(q) == 0) {
					M.push_back(j);
					if (sz(M) * 3 > 2 * n) {
						v = M[randint(0, sz(M) - 1)];
						badcase = true;
						break;
					}
					continue;
				}
				int is = -1;
				for (int j = 0; j < 2; j++) {
					if (q[0][j] == u)
						is = u;
					if (q[0][j] == v)
						is = v;
				}
				assert(is != -1);
				if (is == u)
					L.push_back(j);
				else
					R.push_back(j);
			}
		}
		if (badcase)
			continue;
		L = sort(L);
		R = sort(R);
		M = sort(M);
		vector<int> ans = merge(L, merge(R, M));
		if (sz(perm) == 0) {
			cout << "!";
			for (auto &x : ans)
				cout << " " << x;
			cout << endl;
		} else {
			cout << "query count " << qcnt << endl;
			qcnt = 0;
			bool ok = 0;
			for (int i = 0; i < 2; i++) {
				reverse(all(ans));
				rotate(ans.begin(), find(all(ans), inv[0]), ans.end());
				if (ans == inv)
					ok = true;
			}
			if (!ok)
				cout << "incorrect" << endl;
			else
				cout << "correct" << endl;
		}
		return;
	}
}

int main() {
	/*	ios::sync_with_stdio(false);
		cin.tie(0);
		cout.tie(0);
	*/
	int t, k;
	cin >> t >> k;
	while (t--)
		solve();
}