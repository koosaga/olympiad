#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXT = 530000;

struct node {
	bool lzset;
	lint A;
	lint B;
} tree[MAXT];

void lazydown(int p) {
	if (tree[p].lzset) {
		tree[p].lzset = false;
		for (int i = 2 * p; i < 2 * p + 2; i++) {
			tree[i].lzset = true;
			tree[i].A = tree[p].A;
			tree[i].B = 0;
		}
	}
	for (int i = 2 * p; i < 2 * p + 2; i++) {
		tree[i].B += tree[p].B;
	}
	tree[p].B = 0;
}
void init(int s, int e, int p) {
	if (s == e) {
		tree[p].lzset = true;
		tree[p].A = 0;
		tree[p].B = 1e18;
		return;
	}
	int m = (s + e) / 2;
	init(s, m, 2 * p);
	init(m + 1, e, 2 * p + 1);
}

void add(int s, int e, int ps, int pe, int p, lint x) {
	if (e < ps || pe < s) {
		return;
	}
	if (s <= ps && pe <= e) {
		tree[p].B += x;
		return;
	}
	lazydown(p);
	int pm = (ps + pe) / 2;
	add(s, e, ps, pm, 2 * p, x);
	add(s, e, pm + 1, pe, 2 * p + 1, x);
}

void sex(int s, int e, int ps, int pe, int p, lint A, lint B) {
	if (e < ps || pe < s)
		return;
	if (s <= ps && pe <= e) {
		tree[p].lzset = true;
		tree[p].A = A;
		tree[p].B = B;
		return;
	}
	int pm = (ps + pe) / 2;
	lazydown(p);
	sex(s, e, ps, pm, 2 * p, A, B);
	sex(s, e, pm + 1, pe, 2 * p + 1, A, B);
}

lint query(int pos, int s, int e, int p) {
	if (s == e) {
		return tree[p].A * pos + tree[p].B;
	}
	int m = (s + e) / 2;
	lazydown(p);
	if (pos <= m)
		return query(pos, s, m, 2 * p);
	return query(pos, m + 1, e, 2 * p + 1);
}

struct ds {
	vector<lint> v;
	int n;
	void init(int N) {
		n = N;
		::init(0, n - 1, 1);
	}
	void add(int s, int e, lint x) { ::add(s, e - 1, 0, n - 1, 1, x); }
	lint query(int x) { return ::query(x, 0, n - 1, 1); }
	void fill2(int s, int e, lint a, lint b) { ::sex(s, e - 1, 0, n - 1, 1, a, b); }
} ds;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> m >> n;
	vector<vector<pi>> src(n);
	vector<vector<pi>> obs(n);
	{
		int a, b;
		cin >> a >> b;
		while (a--) {
			lint p, q, r;
			cin >> p >> q >> r;
			src[q].push_back({p, r});
		}
		while (b--) {
			lint s, e, x, t;
			cin >> s >> e >> x >> t;
			obs[x].push_back({s, +t});
			obs[x].push_back({e + 1, -t});
		}
	}
	ds.init(m + 2);
	for (int i = 1; i < n; i++) {
		lint cost;
		cin >> cost;
		sort(all(src[i]));
		for (int j = 0; j < sz(src[i]);) {
			int k = j;
			while (k < sz(src[i]) && src[i][j][0] == src[i][k][0])
				k++;
			int z = src[i][j][0];
			lint v = src[i][j][1];
			lint d = ds.query(z);
			if (d > v) {
				obs[i].push_back({z, v - d});
				obs[i].push_back({z + 1, d - v});
			}
			j = k;
		}
		obs[i].push_back({0, 0});
		obs[i].push_back({m + 2, 0});
		sort(all(obs[i]));
		vector<int> vect;
		lint sum = 0;
		for (int j = 0; j < sz(obs[i]);) {
			int k = j;
			while (k < sz(obs[i]) && obs[i][j][0] == obs[i][k][0]) {
				sum += obs[i][k][1];
				k++;
			}
			vect.push_back(obs[i][j][0]);
			if (k == sz(obs[i])) {
				assert(sum == 0);
				break;
			}
			ds.add(obs[i][j][0], obs[i][k][0], sum);
			j = k;
		}
		for (int i = 1; i + 1 < sz(vect); i++) {
			lint z = ds.query(vect[i] - 1);
			if (ds.query(vect[i]) > z + cost) {
				int s = vect[i], e = vect[i + 1] - 1;
				while (s != e) {
					int m = (s + e + 1) / 2;
					if (ds.query(m) > z + (m - vect[i] + 1) * cost) {
						s = m;
					} else
						e = m - 1;
				}
				ds.fill2(vect[i], e + 1, cost, z - (vect[i] - 1) * cost);
			}
		}
		for (int i = sz(vect) - 2; i > 0; i--) {
			lint z = ds.query(vect[i]);
			if (ds.query(vect[i] - 1) > z + cost) {
				int s = vect[i - 1], e = vect[i] - 1;
				while (s != e) {
					int m = (s + e) / 2;
					if (ds.query(m) > z + (vect[i] - m) * cost) {
						e = m;
					} else
						s = m + 1;
				}
				ds.fill2(s, vect[i], -cost, z + vect[i] * cost);
			}
		}
	}
	for (int j = 1; j <= m; j++) {
		cout << ds.query(j) << "\n";
	}
}