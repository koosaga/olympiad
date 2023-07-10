#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
using point = complex<double>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;

struct points {
	double x, y, val;
	int idx;
};

struct bit {
	double tree[MAXN];
	void clear() { fill(tree, tree + MAXN, 0); }
	void add(int x, double v) {
		for (int i = x + 2; i < MAXN; i += i & -i)
			tree[i] += v;
	}
	double query(int x) {
		double ret = 0;
		for (int i = x + 2; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit, bit2;
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<point> a(n);
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		a[i] = point(x, y);
	}
	auto rotate = [&](double ang) {
		point gob = exp(point(0, ang));
		for (auto &x : a)
			x = x * gob;
	};
	rotate(1557);
	vector<double> dap(n);
	double ang = acos(-1) / 69;
	for (int i = 0; i < 69; i++) {
		double m = tan(ang);
		vector<points> pt(n);
		for (int j = 0; j < n; j++) {
			pt[j] = {m * a[j].real() + a[j].imag(), -m * a[j].real() + a[j].imag(), a[j].real(), j};
		}
		sort(all(pt), [&](const points &a, const points &b) { return a.x > b.x; });
		vector<double> vect;
		for (int i = 0; i < n; i++) {
			vect.push_back(pt[i].y);
		}
		sort(all(vect));
		bit.clear();
		bit2.clear();
		for (int i = 0; i < n; i++) {
			auto pos = lower_bound(all(vect), pt[i].y) - vect.begin();
			dap[pt[i].idx] += bit.query(pos) - pt[i].val * bit2.query(pos);
			bit.add(pos, pt[i].val);
			bit2.add(pos, 1);
		}
		rotate(2 * ang);
	}
	cout.precision(69);
	for (int i = 0; i < n; i++)
		cout << dap[i] * 1.0008 << "\n";
}