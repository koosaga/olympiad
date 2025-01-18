#include "grid_encoding.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

void send(vector<vector<int>> A) {
	int n = sz(A);
	vector<int> X(n), Y(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			X[i] += A[i][j];
			Y[j] += A[i][j];
		}
	}
	vector<int> ordx(n), ordy(n);
	iota(all(ordx), 0);
	iota(all(ordy), 0);
	sort(all(ordx), [&](int a, int b) { return X[a] < X[b]; });
	sort(all(ordy), [&](int a, int b) { return Y[a] < Y[b]; });
	for (int i = 0; i < n; i++) {
		int l = n - Y[ordy[i]];
		int r = n - (i + 1 < n ? Y[ordy[i + 1]] : n);
		for (int j = l - 1; j >= r; j--) {
			select(ordx[j], ordy[i]);
			A[ordx[j]][ordy[i]] = 2;
		}
	}
	for (int i = 0; i < n; i++) {
		int l = n - (i > 0 ? X[ordx[i - 1]] : 0);
		int r = n - X[ordx[i]];
		for (int j = r; j < l; j++) {
			select(ordx[i], ordy[j]);
			A[ordx[i]][ordy[j]] = 3;
		}
	}
}

void dfs(int x, int p, vector<int> &d, vector<vector<int>> &gph) {
	for (auto &y : gph[x]) {
		if (y != p) {
			d[y] = d[x] + 1;
			dfs(y, x, d, gph);
		}
	}
}

vector<vector<int>> reconstruct(vector<vector<int>> B) {
	int n = sz(B);
	vector<vector<int>> C(n + 1, vector<int>(n + 1, -1));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			C[i][j + 1] = B[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		bool ok0 = 0, ok1 = 0;
		for (int j = 1; j <= n; j++) {
			if (B[i - 1][j - 1] == 0)
				ok0 = 1;
			if (B[j - 1][i - 1] == 1)
				ok1 = 1;
		}
		if (!ok0)
			C[i - 1][0] = 0;
		if (!ok1)
			C[n][i] = 1;
	}
	vector<vector<int>> g1(n + 1), g2(n + 1);
	vector<int> distx(n + 1), disty(n + 1);
	for (int i = 0; i <= n; i++) {
		int src = 0;
		for (int j = 0; j <= n; j++) {
			if (C[i][j] == 0)
				src = j;
		}
		for (int j = 0; j <= n; j++) {
			if (C[i][j] == 1) {
				g1[src].push_back(j);
			}
		}
	}
	for (int i = 0; i <= n; i++) {
		int src = n;
		for (int j = 0; j <= n; j++) {
			if (C[j][i] == 1)
				src = j;
		}
		for (int j = 0; j <= n; j++) {
			if (C[j][i] == 0) {
				g2[src].push_back(j);
			}
		}
	}
	dfs(0, -1, disty, g1);
	dfs(n, -1, distx, g2);
	vector<vector<int>> ans(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 1; j <= n; j++) {
			if (~C[i][j])
				ans[i][j - 1] = C[i][j];
			else {
				if (distx[i] > disty[j])
					ans[i][j - 1] = 0;
				else if (distx[i] < disty[j])
					ans[i][j - 1] = 1;
				else if (count(all(C[n]), 1))
					ans[i][j - 1] = 0;
				else
					ans[i][j - 1] = 1;
			}
		}
	}
	return ans;
}