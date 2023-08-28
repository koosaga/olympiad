#include <bits/stdc++.h>
using namespace std;
using lint = long long;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXT = 1050000;

struct bit {
	lint tree[MAXT];
	void add(int x, lint v) {
		for (int i = x + 2; i < MAXT; i += i & -i)
			tree[i] += v;
	}
	lint query(int x) {
		lint ret = 0;
		for (int i = x + 2; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit;

lint l;

vector<lint> vect;
struct node {
	lint adj[2][2][2]; // (use fwt, not use fwt)
	lint lazy;
	node() {
		lazy = 0;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					adj[i][j][k] = -1e18;
				}
			}
		}
	}
	void addLazy(lint x) {
		lazy += x;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				adj[i][j][1] -= x;
			}
		}
	}
} tree[MAXT];

node add(node a, node b) {
	node ret;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				for (int l = 0; l < 2; l++) {
					for (int m = 0; m < 2; m++) {
						ret.adj[j][k][min(l + m, 1)] = max(ret.adj[j][k][min(l + m, 1)], a.adj[j][i][l] + b.adj[i][k][m]);
					}
				}
			}
		}
	}
	return ret;
}
node add_safe(node a, node b) {
	node ret;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				for (int l = 0; l < 2; l++) {
					for (int m = 0; l + m < 2; m++) {
						ret.adj[j][k][l + m] = max(ret.adj[j][k][l + m], a.adj[j][i][l] + b.adj[i][k][m]);
					}
				}
			}
		}
	}
	return ret;
}

void init(int s, int e, int p, vector<node> &v) {
	if (s == e) {
		tree[p] = v[s];
		return;
	}
	int m = (s + e) / 2;
	init(s, m, 2 * p, v);
	init(m + 1, e, 2 * p + 1, v);
	if (s == 0 || vect[e] - vect[s - 1] > 2 * l)
		tree[p] = add(tree[2 * p], tree[2 * p + 1]);
	else
		tree[p] = add_safe(tree[2 * p], tree[2 * p + 1]);
}

void lazydown(int p) {
	if (tree[p].lazy) {
		for (int i = 2 * p; i < 2 * p + 2; i++) {
			tree[i].addLazy(tree[p].lazy);
		}
		tree[p].lazy = 0;
	}
}
void upd(int pos, int s, int e, int p, node v) {
	if (s == e) {
		tree[p] = v;
		return;
	}
	int m = (s + e) / 2;
	lazydown(p);

	if (pos <= m)
		upd(pos, s, m, 2 * p, v);
	else
		upd(pos, m + 1, e, 2 * p + 1, v);
	if (s == 0 || vect[e] - vect[s - 1] > 2 * l)
		tree[p] = add(tree[2 * p], tree[2 * p + 1]);
	else
		tree[p] = add_safe(tree[2 * p], tree[2 * p + 1]);
}

void lazy(int s, int e, int ps, int pe, int p, lint v) {
	if (e < ps || pe < s)
		return;
	if (s <= ps && pe <= e) {
		tree[p].addLazy(v);

		return;
	}
	int pm = (ps + pe) / 2;
	lazydown(p);
	lazy(s, e, ps, pm, 2 * p, v);
	lazy(s, e, pm + 1, pe, 2 * p + 1, v);

	if (ps == 0 || vect[pe] - vect[ps - 1] > 2 * l)
		tree[p] = add(tree[2 * p], tree[2 * p + 1]);
	else
		tree[p] = add_safe(tree[2 * p], tree[2 * p + 1]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint q;
	cin >> q >> l;
	vector<array<lint, 3>> qry(q);
	for (int i = 0; i < q; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> qry[i][j];
		}
		if (qry[i][0] == 1) {
			qry[i][1] -= l;
		}
		if (qry[i][0] == 2)
			vect.push_back(qry[i][1]);
	}
	if (sz(vect) == 0) {
		while (q--)
			cout << "0\n";
		return 0;
	}
	sort(all(vect));
	vect.resize(unique(all(vect)) - vect.begin());
	// (my weight, R mode, T mode)
	vector<array<lint, 2>> values(sz(vect));
	auto genNode = [&](int pos) {
		node ret;
		ret.adj[0][0][0] = 0;
		ret.adj[0][1][1] = values[pos][0] - bit.query(pos);
		ret.adj[1][0][0] = 0;
		ret.adj[1][1][0] = values[pos][0] - values[pos][1];
		ret.adj[1][1][1] = values[pos][0] - bit.query(pos);
		return ret;
	};
	vector<node> nodes;
	for (int i = 0; i < sz(vect); i++) {
		nodes.push_back(genNode(i));
	}
	init(0, sz(vect) - 1, 1, nodes);
	lint sugsum = 0;
	for (int i = 0; i < q; i++) {
		if (qry[i][0] == 1) {
			int st = lower_bound(all(vect), qry[i][1]) - vect.begin();
			int ed = lower_bound(all(vect), qry[i][1] + 2 * l + 1) - vect.begin();
			if (st < sz(vect)) {
				values[st][1] += qry[i][2];
				upd(st, 0, sz(vect) - 1, 1, genNode(st));
			}
			if (st < ed) {
				bit.add(st, qry[i][2]);
				bit.add(ed, -qry[i][2]);
				lazy(st + 1, ed - 1, 0, sz(vect) - 1, 1, qry[i][2]);
				upd(st, 0, sz(vect) - 1, 1, genNode(st));
			}
		} else {
			auto it = lower_bound(all(vect), qry[i][1]) - vect.begin();
			values[it][0] += qry[i][2];
			sugsum += qry[i][2];
			upd(it, 0, sz(vect) - 1, 1, genNode(it));
		}
		/*if (i == q / 2 || q <= 3000) {
			for (int j = 0; j < sz(vect); j++)
				upd(j, 0, sz(vect) - 1, 1, genNode(j));
		}*/
		lint ans = -1e18;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				ans = max(ans, tree[1].adj[i][j][0]);
				ans = max(ans, tree[1].adj[i][j][1]);
			}
		}
		cout << sugsum - ans << "\n";
	}
}