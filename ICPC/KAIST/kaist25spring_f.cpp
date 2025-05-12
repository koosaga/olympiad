#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using point = array<lint, 3>;

point operator-(point a, point b) { return point{a[0] - b[0], a[1] - b[1], a[2] - b[2]}; }
lint ccw(point a, point b, point c) {
	b = b - a;
	c = c - a;
	return b[0] * c[1] - c[0] * b[1];
}

lint dist(point a, point b) {
	b = b - a;
	return b[0] * b[0] + b[1] * b[1];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<point> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i][0] >> a[i][1];
		a[i][2] = i + 1;
	}
	swap(a[0], *min_element(all(a)));
	sort(1 + all(a), [&](const point &p, const point &q) {
		lint d = ccw(a[0], p, q);
		if (d != 0)
			return d > 0;
		return dist(a[0], p) < dist(a[0], q);
	});
	for (int i = 2; i < n - 1; i++) {
		if (ccw(a[i - 1], a[i], a[i + 1]) < 0) {
			cout << 2 * n - 2 << "\n";
			auto pr = [&](int u, int v, char c) { cout << a[u][2] << " " << a[v][2] << " " << c << "\n"; };
			pr(0, i + 1, 'R');
			pr(0, i - 1, 'R');
			pr(0, i, 'B');
			pr(i - 1, i + 1, 'B');
			pr(i, i + 1, 'B');
			pr(i, i - 1, 'R');
			for (int j = 1; j < i - 1; j++) {
				pr(0, j, 'R');
				pr(j, j + 1, 'B');
			}
			for (int j = i + 2; j < n; j++) {
				pr(0, j, 'R');
				pr(j, j - 1, 'B');
			}
			return 0;
		}
	}
	cout << "-1\n";
	return 0;
}