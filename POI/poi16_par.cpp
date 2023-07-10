#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = array<int, 2>;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int solve_domino(vector<string> &a, vector<vector<int>> &label, vector<int> &sizes) {
	int ans = 0;
	int n = sz(a);
	auto ok = [&](int x, int y) { return x >= 0 && x < n && y >= 0 && y < n && label[x][y] >= 0; };
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (a[i][j] == 'A' && a[i][j + 1] == 'A') {
				set<int> s;
				for (auto &p : {pi{i, j}, pi{i, j + 1}}) {
					for (int d = 0; d < 4; d++) {
						if (ok(p[0] + dx[d], p[1] + dy[d])) {
							s.insert(label[p[0] + dx[d]][p[1] + dy[d]]);
						}
					}
				}
				int ret = 2;
				for (auto &q : s)
					ret += sizes[q];
				ans = max(ans, ret);
			}
		}
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] == 'A' && a[i + 1][j] == 'A') {
				set<int> s;
				for (auto &p : {pi{i, j}, pi{i + 1, j}}) {
					for (int d = 0; d < 4; d++) {
						if (ok(p[0] + dx[d], p[1] + dy[d])) {
							s.insert(label[p[0] + dx[d]][p[1] + dy[d]]);
						}
					}
				}
				int ret = 2;
				for (auto &q : s)
					ret += sizes[q];
				ans = max(ans, ret);
			}
		}
	}
	return ans;
}

int solve_each(vector<string> &a, vector<vector<int>> &label, vector<int> &sizes) {
	int ans = 0;
	int n = sz(a);
	vector<int> solved(sz(sizes));
	auto okB = [&](int x, int y) { return x >= 0 && x < n && y >= 0 && y < n && a[x][y] == 'B'; };
	auto okA = [&](int x, int y) { return x >= 0 && x < n && y >= 0 && y < n && a[x][y] == 'A'; };
	vector<vector<int>> rgph(sz(sizes));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] == 'B' && !solved[label[i][j]]) {
				solved[label[i][j]] = 1;
				int sx = i, sy = j, ex = i, ey = j;
				while (ey < n && a[i][ey] == 'B')
					ey++;
				while (ex < n && a[ex][j] == 'B')
					ex++;
				set<set<int>> vect;
				auto push = [&](int x, int y) {
					if (!okA(x, y))
						return;
					set<int> s;
					for (int d = 0; d < 4; d++) {
						if (okB(x + dx[d], y + dy[d])) {
							s.insert(label[x + dx[d]][y + dy[d]]);
						}
					}
					if (s.count(label[i][j]))
						s.erase(s.find(label[i][j]));
					vect.insert(s);
				};
				for (int i = sx; i < ex; i++) {
					push(i, sy - 1);
					push(i, ey);
				}
				for (int i = sy; i < ey; i++) {
					push(sx - 1, i);
					push(ex, i);
				}
				vector<vector<int>> gph;
				vector<int> weights(sz(vect));
				for (auto &x : vect) {
					vector<int> v(all(x));
					gph.push_back(v);
					for (auto &y : v) {
						weights[sz(gph) - 1] += sizes[y];
						rgph[y].push_back(sz(gph) - 1);
					}
				}
				int offset = sizes[label[i][j]] + 2;
				ans = max(ans, offset);
				for (int i = 0; i < sz(gph); i++) {
					int cur = weights[i] + offset;
					for (auto &j : gph[i]) {
						for (auto &k : rgph[j]) {
							weights[k] -= sizes[j];
						}
					}
					cur += *max_element(all(weights));
					for (auto &j : gph[i]) {
						for (auto &k : rgph[j]) {
							weights[k] += sizes[j];
						}
					}
					ans = max(ans, cur);
				}
				for (auto &x : gph) {
					for (auto &y : x) {
						rgph[y].clear();
					}
				}
			}
		}
	}
	return ans;
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	int cntA = 0;
	vector<string> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		cntA += count(all(a[i]), 'A');
	}
	if (cntA <= 2) {
		cout << n * n << "\n";
		return 0;
	}
	vector<vector<int>> label(n, vector<int>(n, -1));
	vector<int> sizes;
	int comp = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (label[i][j] == -1 && a[i][j] == 'B') {
				int csz = 0;
				for (int k = i; k < n; k++) {
					if (a[k][j] == 'A')
						break;
					for (int l = j; l < n; l++) {
						if (a[k][l] == 'A')
							break;
						label[k][l] = comp;
						csz++;
					}
				}
				comp++;
				sizes.push_back(csz);
			}
		}
	}
	int ans1 = solve_domino(a, label, sizes);
	int ans2 = solve_each(a, label, sizes);
	cout << max(ans1, ans2) << "\n";
}