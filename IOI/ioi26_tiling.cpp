#include "tiling.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

vector<vector<int>> A;
vector<pi> p[4];

void init(int N, int M) {
	cr(A, N);
	for (auto &x : A)
		cr(x, M);
	for (int k = 0; k < 4; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				p[k].push_back({i, j});
			}
		}
	}
	sort(all(p[0]), [&](pi a, pi b) { return pi{a[0], a[1]} < pi{b[0], b[1]}; });
	sort(all(p[1]), [&](pi a, pi b) { return pi{a[0], -a[1]} < pi{b[0], -b[1]}; });
	sort(all(p[2]), [&](pi a, pi b) { return pi{-a[0], a[1]} < pi{-b[0], b[1]}; });
	sort(all(p[3]), [&](pi a, pi b) { return pi{-a[0], -a[1]} < pi{-b[0], -b[1]}; });
}

std::pair<int, int> receive_block(int TL, int TR, int BL, int BR) {
	array<int, 4> a = {TL, TR, BL, BR};
	for (int i = 0; i < 4; i++) {
		if (a[i] == 0) {
			while (sz(p[i])) {
				auto v = p[i].back();
				p[i].pop_back();
				if (A[v[0]][v[1]] == 0) {
					A[v[0]][v[1]] = 1;
					return make_pair(2 * v[0], 2 * v[1]);
				}
			}
		}
	}
	return make_pair(0, 0);
}