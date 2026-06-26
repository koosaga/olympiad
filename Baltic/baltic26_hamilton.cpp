#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	int n, t;
	cin >> n >> t;
	vector<vector<int>> a(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 1; j < n; j++) {
			int u = i, v = (i + j) % n;
			if (u < v) {
				a[u][v] = (j < n / 2);
				a[v][u] = !(a[u][v]);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << a[i][j];
		cout << endl;
	}
	auto query = [&](int x, int y) {
		if (a[x][y] != -1)
			return a[x][y];
		cout << "? " << x + 1 << " " << y + 1 << endl;
		string zz;
		cin >> zz;
		int z = (zz == ">");
		a[x][y] = z;
		a[y][x] = 1 - z;
		return z;
	};
	assert(n % 2 == 0);
	for (int T = 0; T < t; T++) {
		for (int i = 0; i < n; i++)
			fill(all(a[i]), -1);
		vector<vector<int>> paths;
		for (int i = 0; i < n; i += 2) {
			if (query(i, i + 1))
				paths.push_back({i, i + 1});
			else
				paths.push_back({i + 1, i});
		}
		auto rng = mt19937_64(0x1557);
		// todo: guarantee that every collision is kinda random?
		while (sz(paths) > 1) {
			bool prog = 0;
			for (int i = 1; i < sz(paths); i++) {
				if (query(paths[0].back(), paths[i][0])) {
					for (auto &j : paths[i])
						paths[0].push_back(j);
					prog = 1;
					paths.erase(paths.begin() + i);
					shuffle(i + all(paths), rng);
					break;
				}
			}
			if (!prog) {
				while (sz(paths) > 1) {
					int i = sz(paths) - 1;
					shuffle(all(paths[i]), rng);
					while (sz(paths[i])) {
						int v = paths[i].back();
						for (int j = sz(paths[0]) - 1; j >= 0; j--) {
							if (query(paths[0][j], v)) {
								paths[0].insert(paths[0].begin() + j + 1, v);
								paths[i].pop_back();
								break;
							}
						}
					}
					paths.pop_back();
				}
				break;
			}
		}
		auto P = paths[0];
		int c = n - 1;
		while (!query(P[c], P[0]))
			c--;
		for (int j = c + 1; j < n; j++) {
			for (int k = 0; k < j; k++) {
				if (query(P[j], P[k])) {
					rotate(P.begin() + k, P.begin() + j, P.begin() + j + 1);
					rotate(P.begin(), P.begin() + k + 1, P.begin() + j + 1);
					break;
				}
			}
		}
		cout << "!";
		for (auto &x : P)
			cout << " " << x + 1;
		cout << endl;
	}
}