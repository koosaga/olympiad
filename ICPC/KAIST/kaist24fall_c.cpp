#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXT = 1050000;

struct seg {
	struct node {
		int active, length;
		int zerA, zerL;
		int lazy;
		void flip() {
			zerA = active - zerA;
			zerL = length - zerL;
			lazy ^= 1;
		}
		node operator+(const node &nd) const { return node{active + nd.active, length + nd.length, zerA + nd.zerA, zerL + nd.zerL, 0}; }
	} tree[MAXT];
	void init(int s, int e, int p, vector<pi> &v) {
		if (s == e) {
			if (v[s][0] == 0)
				tree[p] = {0, 1, 0, 1 - v[s][1], 0};
			else
				tree[p] = {1, 1, 1 - v[s][1], 1 - v[s][1], 0};
			return;
		}
		int m = (s + e) / 2;
		init(s, m, 2 * p, v);
		init(m + 1, e, 2 * p + 1, v);
		tree[p] = tree[2 * p] + tree[2 * p + 1];
	}
	void lazydown(int p) {
		if (tree[p].lazy) {
			tree[p].lazy = 0;
			for (int i = 2 * p; i < 2 * p + 2; i++)
				tree[i].flip();
		}
	}
	void set(int pos, int s, int e, int p) {
		if (s == e) {
			tree[p].active ^= 1;
			if (tree[p].active == 0)
				tree[p].zerA = 0;
			else
				tree[p].zerA = tree[p].zerL;
			return;
		}
		int m = (s + e) / 2;
		lazydown(p);
		if (pos <= m)
			set(pos, s, m, 2 * p);
		else
			set(pos, m + 1, e, 2 * p + 1);
		tree[p] = tree[2 * p] + tree[2 * p + 1];
	}
	void rev(int s, int e, int ps, int pe, int p) {
		if (e < ps || pe < s)
			return;
		if (s <= ps && pe <= e) {
			tree[p].flip();
			return;
		}
		int pm = (ps + pe) / 2;
		lazydown(p);
		rev(s, e, ps, pm, 2 * p);
		rev(s, e, pm + 1, pe, 2 * p + 1);
		tree[p] = tree[2 * p] + tree[2 * p + 1];
	}
} seg;
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	string s[2] = {"0", "0"};
	vector<pi> seq;
	for (int i = 0; i < 2 * n - 2; i++) {
		int d, x, c;
		cin >> d >> x >> c;
		s[d].push_back(c + '0');
		seq.push_back({d, c});
	}
	int x = n, y = n;
	int px = -1, py = -1;
	vector<array<int, 3>> v;
	auto AddContrib = [&](int cx, int cy) {
		if (~px) {
			assert(abs(px - cx) + abs(py - cy) == 1);
			if (px == cx)
				v.push_back({0, cy, px});
			else
				v.push_back({1, cx, py});
		}
		px = cx;
		py = cy;
	};
	for (int i = sz(seq) - 1; i >= 0; i--) {
		if (seq[i][0] == 1) {
			if (y < n)
				AddContrib(x - 1, y);
			x--;
		} else {
			if (x < n)
				AddContrib(x, y - 1);
			y--;
		}
	}
	AddContrib(0, 1);
	AddContrib(0, 0);
	int diffs[2] = {1, 1};
	vector<int> delta[2];
	vector<int> assoc[2];
	vector<int> pos[2];
	for (int i = 0; i < 2; i++) {
		cr(delta[i], n);
		cr(assoc[i], n);
		cr(pos[i], n + 2);
		fill(all(assoc[i]), -1);
		for (int j = 1; j < n; j++) {
			if (s[i][j - 1] != s[i][j]) {
				delta[i][j] = 1;
				diffs[i]++;
			}
		}
	}
	reverse(all(v));
	vector<pi> inits;
	for (int i = 0; i < sz(v); i++) {
		v[i][1]++;
		auto [idx, p, q] = v[i];
		assoc[idx][p] = i; // (p+1, q) this place
		pos[idx][p + 1]++;
		pos[1 - idx][q + 1]++;
		inits.push_back({delta[idx][p], (s[idx][p] - '0') ^ (s[1 - idx][q] - '0')});
	}
	seg.init(0, sz(inits) - 1, 1, inits);
	for (int i = 0; i < 2; i++) {
		for (int j = 1; j <= n + 1; j++)
			pos[i][j] += pos[i][j - 1];
	}
	auto flip = [&](int z, int p) {
		if (0 < p && p < n) {
			delta[z][p] ^= 1;
			diffs[z] += 2 * delta[z][p] - 1;
			if (~assoc[z][p]) {
				seg.set(assoc[z][p], 0, sz(inits) - 1, 1);
			}
		}
	};
	while (q--) {
		int z, l, r;
		cin >> z >> l >> r;
		flip(z, l - 1);
		flip(z, r);
		int idx1 = pos[z][l - 1];
		int idx2 = pos[z][r];
		seg.rev(idx1, idx2 - 1, 0, sz(inits) - 1, 1);
		cout << diffs[0] + diffs[1] - seg.tree[1].zerA - 1 << "\n";
	}
}