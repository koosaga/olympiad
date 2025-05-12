#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<vector<int>> seq(n + 1);
	for (int i = 0; i < n; i++) {
		int v;
		cin >> v;
		seq[v].push_back(i + 1);
	}
	auto ass = [&](bool p) {
		if (!p) {
			cout << "-1\n";
			exit(0);
		}
	};
	if (sz(seq[0]) >= n) {
		int y = seq[0].back();
		seq[0].pop_back();
		seq[1].push_back(y);
	}
	vector<int> pp;
	for (int i = 1; i <= n; i++) {
		while (sz(seq[i - 1]) < sz(seq[i])) {
			pp.push_back(seq[i].back());
			seq[i].pop_back();
		}
		while (sz(pp) && sz(seq[i - 1]) > sz(seq[i])) {
			seq[i].push_back(pp.back());
			pp.pop_back();
		}
	}
	ass(sz(pp) == 0);
	int j = n;
	while (!sz(seq[j]))
		j--;
	vector<pi> v;
	for (int x = 0; x < j; x++) {
		ass(sz(seq[x]) >= 2);
		for (int y = 0; y < sz(seq[x]); y++) {
			v.push_back({seq[x][y], seq[x + 1][min(y, sz(seq[x + 1]) - 1)]});
		}
	}
	for (int i = 1; i < sz(seq[j]); i++) {
		v.push_back({seq[j][0], seq[j][i]});
	}
	for (auto &[a, b] : v)
		cout << a << " " << b << "\n";
}