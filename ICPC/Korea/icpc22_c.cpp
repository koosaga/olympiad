#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

lint ccw(pi a, pi b, pi c) {
	lint dx1 = b.first - a.first;
	lint dy1 = b.second - a.second;
	lint dx2 = c.first - a.first;
	lint dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

int bit[305], fuck[305];

auto gpair = [](vector<pi> &a) {
	memset(bit, 0, sizeof(bit));
	memset(fuck, 0, sizeof(fuck));
	pi ret(0, 0);
	for (int i = 0; i < sz(a); i++) {
		for (int x = a[i].second; x > 0; x -= x & -x)
			fuck[i] += bit[x];
		for (int x = a[i].second + 1; x < 305; x += x & -x)
			bit[x]++;
		if (fuck[i] == 0)
			ret.first++;
	}
	vector<int> coords[305];
	for (int i = 0; i < sz(a); i++) {
		coords[fuck[i]].push_back(-a[i].second);
		if (fuck[i] > 0) {
			auto l = lower_bound(all(coords[fuck[i] - 1]), -a[i].second);
			ret.second += coords[fuck[i] - 1].end() - l;
		}
	}
	return ret;
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<pi> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].first >> a[i].second;
	}
	lint ret = 0;
	vector<vector<int>> ords(n);
	vector<vector<int>> revord(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j) {
				ords[i].push_back(j);
			}
		}
		sort(all(ords[i]), [&](const int &p, const int &q) {
			bool mode1 = (a[i] > a[p]);
			bool mode2 = (a[i] > a[q]);
			if (mode1 != mode2)
				return mode1 < mode2;
			return ccw(a[i], a[p], a[q]) > 0;
		});
		revord[i].resize(n);
		for (int j = 0; j < n - 1; j++)
			revord[i][ords[i][j]] = j;
	}
	vector<vector<int>> A(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)
				continue;
			vector<pi> ord1;
			int Q = revord[i][j];
			for (int x = 1; x < n - 1; x++) {
				int k = ords[i][(Q + x) % (n - 1)];
				if (ccw(a[i], a[j], a[k]) > 0) {
					ord1.emplace_back(x, revord[j][i] - revord[j][k]);
				}
			}
			for (auto &x : ord1) {
				if (x.second < 0)
					x.second += n - 1;
			}
			auto ans = gpair(ord1);
			A[i][j] = ans.first;
			ret += ans.second;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			ret += A[i][j] * A[j][i];
		}
	}
	//	assert(ret % 2 == 0);
	cout << ret / 2 << "\n";
}