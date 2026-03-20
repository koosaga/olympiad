#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXT = 1200000;

struct bit {
	int tree[MAXT];
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

struct node {
	lint x, y;
	lint l, r;
	lint crs;
	node(pi a, pi b) {
		x = b[0] - a[0];
		y = b[1] - a[1];
		int g = gcd(abs(x), abs(y));
		x /= g;
		y /= g;
		l = x * a[0] + y * a[1];
		r = x * b[0] + y * b[1];
		crs = y * a[0] - x * a[1];
		crs *= -1;
		if (l > r)
			swap(l, r);
	}
};

lint ccw(node a, node b) { return a.x * b.y - b.x * a.y; }
bool operator<(node a, node b) {
	lint dx = ccw(a, b);
	if (dx != 0)
		return dx > 0;
	return a.crs < b.crs;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<pi> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i][0] >> a[i][1];
	sort(all(a));
	vector<node> vect;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			vect.push_back(node(a[i], a[j]));
		}
	}
	vector<lint> coords;
	for (auto &x : vect) {
		coords.push_back(x.l);
	}
	sort(all(coords));
	coords.resize(unique(all(coords)) - coords.begin());
	for (auto &x : vect) {
		x.l = lower_bound(all(coords), x.l) - coords.begin();
	}
	sort(all(vect));
	lint ans = 0;
	for (int i = 0; i < sz(vect);) {
		int j = i + 1;
		while (j < sz(vect) && ccw(vect[i], vect[j]) == 0)
			j++;
		int l = i;
		for (int k = i; k < j; k++) {
			while (vect[l].crs < vect[k].crs) {
				bit.add(vect[l].l, +1);
				l++;
			}
			int z = lower_bound(all(coords), vect[k].r) - coords.begin();
			ans += bit.query(z - 1);
		}
		for (int k = i; k < l; k++)
			bit.add(vect[k].l, -1);
		i = j;
	}
	cout << 2 * ans << "\n";
}