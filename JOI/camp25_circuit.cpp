#include "circuit.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

vector<pi> gph;
vector<int> sub;
string ans;

void dfs(int x) {
	sub[x] = 1;
	if (x >= sz(gph))
		return;
	dfs(gph[x][0]);
	dfs(gph[x][1]);
	if (sub[gph[x][0]] < sub[gph[x][1]])
		swap(gph[x][0], gph[x][1]);
	sub[x] = 1 + sub[gph[x][0]] + sub[gph[x][1]];
}

vector<vector<int>> paths_depth[20];

void rec(int x, int d = 0) {
	int n = sz(gph);
	vector<int> pth = {x};
	for (int i = x; i < n; i = gph[i][0]) {
		pth.push_back(gph[i][0]);
	}
	paths_depth[d].push_back(pth);
	for (int i = x; i < n; i = gph[i][0])
		rec(gph[i][1], d + 1);
}

std::string solve(int N, int R, std::vector<int> U, std::vector<int> V) {
	cr(gph, N);
	cr(sub, 2 * N + 1);
	for (int i = 0; i < N; i++) {
		gph[i] = {U[i], V[i]};
	}
	dfs(0);
	ans = string(N, '&');
	rec(0);
	for (int i = 0; sz(paths_depth[i]); i++) {
		vector<pi> v;
		for (int j = 0; j < sz(paths_depth[i]); j++) {
			for (int k = 0; k < sz(paths_depth[i][j]) - 1; k++) {
				v.push_back({j, k});
			}
		}
		int l = 0;
		auto bin = [&](int r) {
			if (l == r)
				return false;
			string s(2 * N + 1, '0');
			for (int j = N; j < 2 * N + 1; j++)
				s[j] = '1';
			auto pos = v[r - 1];
			for (int j = 0; j < pos[0]; j++) {
				s[paths_depth[i][j].front()] ^= 1;
				s[paths_depth[i][j].back()] ^= 1;
			}
			s[paths_depth[i][pos[0]].front()] ^= 1;
			s[paths_depth[i][pos[0]][pos[1] + 1]] ^= 1;
			for (int j = 0; j < N; j++) {
				if (ans[j] == '|') {
					s[j] ^= 1;
					s[gph[j][0]] ^= 1;
					s[gph[j][1]] ^= 1;
				}
			}
			return query(s) == 0;
		};
		while (true) {
			int r = l;
			while (r < sz(v) && !bin(min(sz(v), r + 64))) {
				r += 64;
			}
			if (r >= sz(v))
				break;
			int s = r + 1, e = min(r + 64, sz(v));
			while (s != e) {
				int m = (s + e) / 2;
				if (bin(m))
					e = m;
				else
					s = m + 1;
			}
			int vtx = paths_depth[i][v[s - 1][0]][v[s - 1][1]];
			ans[vtx] = '|';
			// s-th (1-based) is OR gate
			l = s;
		}
	}
	return ans;
}
