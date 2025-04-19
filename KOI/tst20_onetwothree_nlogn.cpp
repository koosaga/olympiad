#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
#include "onetwothree.h"

void maximize(std::vector<int> A) {
	vector<int> pos[3];
	int n = sz(A);
	for (int i = 0; i < n; i++) {
		A[i]--;
		pos[A[i]].push_back(i);
	}
	auto solve = [&](array<int, 3> msk) {
		vector<vector<int>> dp(n + 1, vector<int>(3));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 3; j++) {
				dp[i + 1][j] = dp[i][j] + (msk[j] >> A[i]) % 2;
			}
			for (int j = 1; j < 3; j++)
				dp[i + 1][j] = min(dp[i + 1][j], dp[i + 1][j - 1]);
		}
		return dp[n][2];
	};
	auto ok = [&](int l, int r, int track) {
		if (l + r > sz(pos[0]) || l + r > sz(pos[2]) || l + r > sz(pos[1]))
			return false;
		vector<pi> v;
		for (int i = 0; i < l; i++) {
			v.push_back({pos[0][i], pos[2][sz(pos[2]) - l + i]});
		}
		for (int i = 0; i < r; i++) {
			v.push_back({pos[2][i], pos[0][sz(pos[0]) - r + i]});
		}
		sort(all(v));
		reverse(all(v));
		set<int> s;
		int p = sz(pos[1]);
		for (auto &[x, y] : v) {
			while (p > 0 && pos[1][p - 1] >= x) {
				s.insert(pos[1][--p]);
			}
			auto it = s.upper_bound(y);
			if (it != s.begin()) {
				it--;
				if (track)
					answer(x, *it, y);
				s.erase(it);
			} else
				return false;
		}
		return true;
	};
	int amin = solve(array<int, 3>{1, 2, 4});
	int bmin = solve(array<int, 3>{4, 2, 1});
	int hmin = solve(array<int, 3>{5, 2, 5});
	hmin = min({hmin, (int)count(all(A), 0), (int)count(all(A), 2)});
	amin = min(amin, hmin);
	bmin = min(bmin, hmin - amin);
	assert(ok(amin, bmin, 1));
}