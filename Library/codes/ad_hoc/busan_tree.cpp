#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXT = 1050000;
struct BusanTree {
	struct seg {
		vector<int> tree, lazy;
		void init(int n) {
			tree.resize(MAXT);
			lazy.resize(MAXT);
		}
		void lazydown(int p) {
			if (!lazy[p])
				return;
			for (int i = 2 * p; i < 2 * p + 2; i++) {
				tree[i] += lazy[p];
				lazy[i] += lazy[p];
			}
			lazy[p] = 0;
		}
		void add(int s, int e, int ps, int pe, int p, int v) {
			if (e < ps || pe < s)
				return;
			if (s <= ps && pe <= e) {
				tree[p] += v;
				lazy[p] += v;
				return;
			}
			int pm = (ps + pe) / 2;
			lazydown(p);
			add(s, e, ps, pm, 2 * p, v);
			add(s, e, pm + 1, pe, 2 * p + 1, v);
			tree[p] = min(tree[2 * p], tree[2 * p + 1]);
		}
		int query(int s, int e, int ps, int pe, int p) {
			if (e < ps || pe < s)
				return 1e9;
			if (s <= ps && pe <= e)
				return tree[p];
			int pm = (ps + pe) / 2;
			lazydown(p);
			return min(query(s, e, ps, pm, 2 * p), query(s, e, pm + 1, pe, 2 * p + 1));
		}
	} seg;
	struct node {
		int l, r;
		int vl, vr;
		bool linear; // true if the node is linear (leaf is linear)
		vector<node *> ch;
		node(int ll, int rr, int vll, int vrr, bool llinear) {
			l = ll;
			r = rr;
			vl = vll;
			vr = vrr;
			linear = llinear;
		}
		bool increasing() {
			assert(linear);
			return vl == ch[0]->vl;
		}
	};
	int n, cnt;
	node *root;
	void init(vector<int> a) {
		n = sz(a);
		vector<node *> stk;
		seg.init(n); // max A - min A - (r - l) >= 0
		vector<int> stkMax, stkMin;
		for (int i = 0; i < n; i++) {
			while (sz(stkMax) && a[stkMax.back()] < a[i]) {
				int r = stkMax.back();
				stkMax.pop_back();
				int l = (sz(stkMax) ? stkMax.back() : -1) + 1;
				seg.add(l, r, 0, n - 1, 1, a[i] - a[r]);
			}
			while (sz(stkMin) && a[stkMin.back()] > a[i]) {
				int r = stkMin.back();
				stkMin.pop_back();
				int l = (sz(stkMin) ? stkMin.back() : -1) + 1;
				seg.add(l, r, 0, n - 1, 1, a[r] - a[i]);
			}
			stkMax.push_back(i);
			stkMin.push_back(i);
			if (i > 0)
				seg.add(0, i - 1, 0, n - 1, 1, -1);
			node *nd = new node(i, i, a[i], a[i], true);
			cnt++;
			while (true) {
				if (sz(stk)) {
					node *r = stk.back();
					auto can_merge = [&](node *r, node *u) {
						if (r->vr + 1 == u->vl)
							return r->increasing();
						if (r->vl - 1 == u->vr)
							return !r->increasing();
						return false;
					};
					if (r->linear && sz(r->ch) >= 2 && can_merge(r, nd)) {
						r->ch.push_back(nd);
						r->r = nd->r;
						r->vl = min(r->vl, nd->vl);
						r->vr = max(r->vr, nd->vr);
						nd = r;
						stk.pop_back();
						continue;
					}
					if (r->vr + 1 == nd->vl || r->vl - 1 == nd->vr) {
						stk.pop_back();
						node *nv = new node(r->l, nd->r, min(r->vl, nd->vl), max(r->vr, nd->vr), true);
						nv->ch.push_back(r);
						nv->ch.push_back(nd);
						cnt++;
						nd = nv;
						continue;
					}
				}
				if (seg.query(0, nd->l - 1, 0, n - 1, 1) != 0) {
					stk.push_back(nd);
					break;
				}
				node *prime = new node(nd->l, nd->r, nd->vl, nd->vr, false);
				prime->ch.push_back(nd);
				cnt++;
				while (true) {
					auto bk = stk.back();
					stk.pop_back();
					prime->l = bk->l;
					prime->vl = min(prime->vl, bk->vl);
					prime->vr = max(prime->vr, bk->vr);
					prime->ch.push_back(bk);
					if (prime->vr - prime->vl == prime->r - prime->l)
						break;
				}
				reverse(all(prime->ch));
				nd = prime;
			}
		}
		if (sz(stk) > 1) {
			cnt++;
			node *root = new node(0, n - 1, 0, n - 1, false);
			root->ch = stk;
			stk.clear();
			stk.push_back(root);
		}
		assert(sz(stk));
		root = stk[0];
	}
	int piv = 0;
	void dfs(node *p, int par) {
		cout << par << " " << p->l << " " << p->r << (p->linear ? " linear\n" : " prime\n");
		int cur = piv++;
		for (auto &x : p->ch) {
			dfs(x, cur);
		}
	}
} bst;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &x : a)
		cin >> x;
	bst.init(a);
	cout << bst.cnt << "\n";
	bst.dfs(bst.root, -1);
}