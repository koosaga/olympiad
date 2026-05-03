#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

struct disj {
	vector<int> pa;
	void init(int n) {
		pa.clear();
		pa.resize(n);
		iota(all(pa), 0);
	}
	int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
	bool uni(int p, int q) {
		p = find(p);
		q = find(q);
		if (p == q)
			return 0;
		pa[q] = p;
		return 1;
	}
} disj;
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	array<int, 3> dim;
	cin >> dim[0] >> dim[1] >> dim[2];
	int n;
	cin >> n;
	if (n == 0) {
		cout << "1\n";
		return 0;
	}
	vector<array<int, 3>> a(n);
	{
		vector<int> coords[3];
		for (auto &v : a) {
			for (int j = 0; j < 3; j++) {
				cin >> v[j];
				for (int k = -1; k <= 1; k++) {
					if (v[j] + k >= 0 && v[j] + k < dim[j])
						coords[j].push_back(v[j] + k);
				}
			}
		}
		for (int j = 0; j < 3; j++) {
			sort(all(coords[j]));
			coords[j].resize(unique(all(coords[j])) - coords[j].begin());
			dim[j] = sz(coords[j]);
		}
		for (auto &v : a) {
			for (int j = 0; j < 3; j++) {
				v[j] = lower_bound(all(coords[j]), v[j]) - coords[j].begin();
			}
		}
	}
	set<pi> imp;
	map<pi, vector<int>> inp;
	vector<vector<int>> imps(dim[0]);
	for (auto &[x, y, z] : a) {
		imps[x].push_back(y);
		inp[pi{x, y}].push_back(z);
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				if (x + j >= 0 && x + j < dim[0] && y + k >= 0 && y + k < dim[1]) {
					imp.insert({x + j, y + k});
				}
			}
		}
	}
	for (int i = 0; i < dim[0]; i++)
		imp.insert({i, 0});
	int cidx = 0;
	map<pi, vector<array<int, 3>>> segs;
	for (auto &[x, y] : imp) {
		vector<int> points = {-1};
		for (auto &j : inp[pi{x, y}])
			points.push_back(j);
		points.push_back(dim[2]);
		sort(all(points));
		for (int i = 1; i < sz(points); i++) {
			if (points[i - 1] + 1 < points[i]) {
				int l = points[i - 1] + 1, r = points[i] - 1;
				segs[pi{x, y}].push_back({l, r, cidx++});
			}
		}
	}
	int res = cidx;
	disj.init(cidx);
	auto merge = [&](vector<array<int, 3>> &a, vector<array<int, 3>> &b) {
		int j = 0;
		for (int i = 0; i < sz(a); i++) {
			j = max(j - 3, 0);
			assert(j == 0 || b[j][1] < a[i][0]);
			while (j < sz(b) && b[j][0] <= a[i][1]) {
				if (max(b[j][0], a[i][0]) <= min(b[j][1], a[i][1]))
					res -= disj.uni(b[j][2], a[i][2]);
				j++;
			}
		}
	};
	for (auto &[x, y] : imp) {
		if (imp.count(pi{x + 1, y})) {
			merge(segs[pi{x, y}], segs[pi{x + 1, y}]);
		}
		if (imp.count(pi{x, y + 1})) {
			merge(segs[pi{x, y}], segs[pi{x, y + 1}]);
		}
	}
	vector<array<int, 3>> pseg, cseg;
	for (int i = 0; i < dim[0]; i++) {
		imps[i].push_back(-1);
		imps[i].push_back(dim[1]);
		sort(all(imps[i]));
		cseg.clear();
		for (int j = 1; j < sz(imps[i]); j++) {
			int l = imps[i][j - 1] + 1;
			int r = imps[i][j] - 1;
			if (l <= r) {
				auto it = segs.lower_bound(pi{i, l});
				int cnum = -1;
				while (it != segs.end() && it->first <= pi{i, r}) {
					if (~cnum)
						res -= disj.uni(cnum, (it->second)[0][2]);
					cnum = (it->second)[0][2];
					it++;
				}
				cseg.push_back({l, r, cnum});
			}
		}
		merge(pseg, cseg);
		pseg = cseg;
	}
	cout << res << "\n";
}