#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<lint, 2>;
const int MAXN = 500005;
const llf PI = acosl(-1);
const llf eps = 1e-11;

llf Ang(llf x1, llf r1, llf r2) {
	x1 = fabs(x1);
	if (r1 + r2 <= x1)
		return 0;
	llf cosval = (x1 * x1 + r2 * r2 - r1 * r1) / (2 * x1 * r2);
	assert(cosval >= -1.0L - eps && cosval <= 1.0L + eps);
	cosval = max(cosval, -1.0L);
	cosval = min(cosval, 1.0L);
	llf the = acos(cosval);
	the = max(the, 0.0L);
	the = min(the, PI);
	return the;
}

llf dist(array<llf, 2> a, array<llf, 2> b) { return hypotl(a[0] - b[0], a[1] - b[1]); }

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<array<llf, 2>> mapto(n);
	for (int i = 0; i < k; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		mapto[z - 1] = array<llf, 2>{x, y};
	}
	vector<pi> voronoi(n);
	for (auto &[pos, idx] : voronoi) {
		cin >> pos >> idx;
		idx--;
	}
	vector<int> L(n), R(n);
	int last = -1;
	for (int i = 0; i < n; i++) {
		if (mapto[voronoi[i][1]][1] < 0)
			last = i;
		L[i] = last;
	}
	last = -1;
	for (int i = n - 1; i >= 0; i--) {
		if (mapto[voronoi[i][1]][1] < 0)
			last = i;
		R[i] = last;
	}
	for (int i = 0; i < n; i++) {
		if (mapto[voronoi[i][1]][1] < 0)
			continue;
		llf a1 = 0, a2 = 0;
		llf r = 1e18;
		if (L[i] >= 0)
			r = min(r, dist(mapto[voronoi[L[i]][1]], array<llf, 2>{voronoi[i][0], 0}));
		if (R[i] >= 0)
			r = min(r, dist(mapto[voronoi[R[i]][1]], array<llf, 2>{voronoi[i][0], 0}));
		if (L[i] >= 0) {
			a1 = Ang(voronoi[i][0] - voronoi[L[i]][0],
					 dist(mapto[voronoi[L[i]][1]], array<llf, 2>{voronoi[L[i]][0], 0}), r);
		}
		if (R[i] >= 0) {
			a2 = Ang(voronoi[i][0] - voronoi[R[i]][0],
					 dist(mapto[voronoi[R[i]][1]], array<llf, 2>{voronoi[R[i]][0], 0}), r);
		}
		cout << voronoi[i][1] + 1 << " ";
		if (a1 <= PI / 2 && a2 <= PI / 2)
			cout << setprecision(15) << -r << "\n";
		else {
			cout << setprecision(15) << -r * sin(max(a1, a2)) << "\n";
		}
	}
}