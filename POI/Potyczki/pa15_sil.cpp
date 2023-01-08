#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

struct segtree {
	vector<pi> tree;
	int lim;
	void init(vector<array<int, 3>> a) {
		for (lim = 1; lim <= sz(a); lim <<= 1)
			;
		tree.resize(2 * lim);
		fill(all(tree), pi{int(2e9), -1});
		for (int i = 0; i < sz(a); i++) {
			tree[i + lim] = {a[i][0], i};
		}
		for (int i = lim - 1; i; i--)
			tree[i] = min(tree[2 * i], tree[2 * i + 1]);
	}
	void upd(int x, pi val) {
		x += lim;
		tree[x] = val;
		while (x > 1) {
			x >>= 1;
			tree[x] = min(tree[2 * x], tree[2 * x + 1]);
		}
	}
	int globalMin() { return tree[1][0]; }
	int lowerThan(int thres) {
		int p = 1;
		while (p < lim) {
			if (tree[2 * p][0] <= thres)
				p = 2 * p;
			else
				p = 2 * p + 1;
		}
		return p - lim;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.precision(69);
	int n, k;
	cin >> n >> k;
	vector<vector<array<int, 3>>> v;
	{
		vector<array<int, 4>> a(n);
		int idx = 0;
		for (auto &[p, l, r, i] : a) {
			cin >> l >> r >> p;
			i = idx++;
		}
		sort(all(a));
		for (int i = 0; i < n;) {
			int j = i;
			vector<array<int, 3>> grp;
			while (j < n && a[i][0] == a[j][0]) {
				grp.push_back({a[j][1], a[j][2], a[j][3]});
				j++;
			}
			sort(all(grp), [&](const array<int, 3> &a, const array<int, 3> &b) { return pi{a[1], a[0]} > pi{b[1], b[0]}; });
			int z = 2e9;
			priority_queue<pi> pq; // max heap
			for (int i = 0; i < sz(grp); i++) {
				while (sz(pq) && grp[i][1] < z) {
					auto x = pq.top();
					pq.pop();
					if (x[0] > z) {
						cout << "NIE\n";
						return 0;
					}
					grp[x[1]][1] = z--;
				}
				z = min(z, grp[i][1]);
				pq.push({grp[i][0], i});
			}
			while (sz(pq)) {
				auto x = pq.top();
				pq.pop();
				if (x[0] > z) {
					cout << "NIE\n";
					return 0;
				}
				grp[x[1]][1] = z--;
			}
			sort(all(grp), [&](const array<int, 3> &a, const array<int, 3> &b) { return pi{a[1], a[0]} < pi{b[1], b[0]}; });
			v.push_back(grp);
			i = j;
		}
		k = sz(v);
	}
	vector<int> ans(n);
	vector<vector<int>> vis(k);
	set<int> st;
	vector<array<int, 3>> que;
	vector<segtree> seg(k);
	priority_queue<pi, vector<pi>, greater<pi>> pq;
	for (int i = 0; i < k; i++) {
		vis[i].resize(sz(v[i]));
		for (int j = 0; j < sz(v[i]); j++) {
			que.push_back({v[i][j][1], i, j});
		}
		seg[i].init(v[i]);
		//	cout << "push" << seg[i].globalMin() << " " << i << endl;
		pq.push({seg[i].globalMin(), i});
	}
	sort(all(que));
	int ptr = 0;
	for (int cnt = 0;; cnt++) {
		while (ptr < sz(que) && vis[que[ptr][1]][que[ptr][2]])
			ptr++;
		if (ptr == sz(que)) {
			cout << cnt << "\n";
			for (auto &x : ans)
				cout << x << "\n";
			return 0;
		}
		int thres = que[ptr][0];
		vector<pi> to_add;
		while (sz(pq) && pq.top()[0] <= thres) {
			auto [val, i] = pq.top();
			pq.pop();
			//	cout << "pop " << i << " " << val << endl;
			if (seg[i].globalMin() != val)
				continue;
			int j = seg[i].lowerThan(thres);
			to_add.push_back({i, j});
		}
		// cout << sz(pq) << endl;
		if (!sz(to_add)) {
			cout << "NIE\n";
			return 0;
		}
		for (auto &[i, j] : to_add) {
			ans[v[i][j][2]] = thres;
			vis[i][j] = 1;
			seg[i].upd(j, pi{int(2e9), -1});
			pq.push({seg[i].globalMin(), i});
		}
	}
}
