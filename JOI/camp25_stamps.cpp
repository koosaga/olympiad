#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXT = 3050000;

struct bit {
	int tree[MAXT];
	void clear() { memset(tree, 0, sizeof(tree)); }
	void add(int x, int v) {
		for (int i = x + 2; i < MAXT; i += i & -i)
			tree[i] += v;
	}
	int query(int x) {
		int ret = 0;
		for (int i = x + 2; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, x;
	cin >> n >> x;
	vector<lint> a(n * 2), c(n * 2);
	for (auto &x : a)
		cin >> x, x--;
	for (auto &x : c)
		cin >> x;
	vector<pi> vect;
	vector<pi> pos(n, pi{-1, -1});
	for (int j = 0; j < 2 * n; j++) {
		int z = a[j];
		if (~pos[z][0])
			pos[z][1] = j;
		else
			pos[z][0] = j;
	}
	sort(all(pos));
	vector<lint> mtch(n * 4), con(n * 2);
	for (int i = 0; i < n; i++) {
		mtch[pos[i][0]] = pos[i][1];
		mtch[pos[i][1]] = pos[i][0] + 2 * n;
		mtch[pos[i][0] + 2 * n] = pos[i][1] + 2 * n;
		mtch[pos[i][1] + 2 * n] = pos[i][0] + 4 * n;
	}
	vector<int> cross_ratio(n), fuck(n * 2);
	{
		for (int i = 0; i < n; i++) {
			cross_ratio[i] += i - bit.query(pos[i][1]);
			bit.add(pos[i][1], +1);
		}
		bit.clear();
		for (int i = n - 1; i >= 0; i--) {
			cross_ratio[i] += bit.query(pos[i][1]);
			bit.add(pos[i][1], +1);
		}
		bit.clear();
		for (int i = 0; i < n; i++) {
			int z = bit.query(pos[i][0]);
			cross_ratio[i] += z;
			con[0] += z;
			bit.add(pos[i][1], +1);
		}
		bit.clear();
		for (int i = n - 1; i >= 0; i--) {
			bit.add(pos[i][0], +1);
			cross_ratio[i] += n - i - bit.query(pos[i][1]);
		}
		bit.clear();
	}
	for (int i = 0; i < n; i++) {
		fuck[pos[i][0]] = fuck[pos[i][1]] = cross_ratio[i];
	}
	for (int i = 0; i < 2 * n; i++)
		bit.add(mtch[i], +1);
	for (int i = 1; i < 2 * n; i++) {
		bit.add(mtch[i - 1], -1);
		bit.add(mtch[i + (2 * n - 1)], +1);
		int crossin = bit.query(mtch[i - 1] - 1);
		int crossout = fuck[i - 1] - crossin;
		con[i] = con[i - 1] + crossin - crossout;
	}
	for (int i = 0; i < n * 2; i++) {
		vect.push_back({1ll * n * n - con[i], c[i]});
	}
	sort(all(vect));
	vector<lint> pmin(2 * n + 1), smin(2 * n + 1);
	smin[2 * n] = 5e18;
	for (int i = 2 * n - 1; i >= 0; i--) {
		smin[i] = min(smin[i + 1], vect[i][1]);
	}
	pmin[0] = 5e18;
	for (int i = 1; i < 2 * n + 1; i++) {
		pmin[i] = min(pmin[i - 1], vect[i - 1][1] - vect[i - 1][0] * x);
	}
	int q;
	cin >> q;
	while (q--) {
		lint z;
		cin >> z;
		int pos = lower_bound(all(vect), pi{z, -1}) - vect.begin();
		lint ans = min(pmin[pos] + z * x, smin[pos]);
		cout << ans << "\n";
	}
}