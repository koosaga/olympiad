#include "Aoi.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 20005;

namespace {
vector<int> tr[MAXN], gph[MAXN];
int mark[MAXN], mask[MAXN], revidx[MAXN], din[MAXN], dout[MAXN];
vector<int> ord;
vector<pi> comps;
vector<lint> dp;

void dfs(int x) {
	vector<pi> intv;
	din[x] = sz(ord);
	if (mark[x]) {
		intv.push_back({sz(ord), sz(ord) + 1});
		comps.push_back({sz(ord), sz(ord) + 1});
		ord.push_back(revidx[x]);
		mask[x] |= (1 << revidx[x]);
	}
	for (auto &y : tr[x]) {
		dfs(y);
		mask[x] |= mask[y];
		if (din[y] < dout[y])
			intv.push_back({din[y], dout[y]});
	}
	if (sz(intv) > 1) {
		for (int j = 1; j < sz(intv); j++) {
			comps.push_back({intv[0][0], intv[j][1]});
		}
	}
	dout[x] = sz(ord);
}

int mask_small[MAXN];
int mask_to_normal[1 << 16], piv;

void normalize(int x) {
	if (comps[x][1] == comps[x][0] + 1) {
		assert(sz(gph[x]) == 0);
		mask_small[x] = (1 << ord[comps[x][0]]);
	} else {
		assert(sz(gph[x]) == 2);

		normalize(gph[x][0]);
		normalize(gph[x][1]);
		if (mask_small[gph[x][0]] > mask_small[gph[x][1]])
			swap(gph[x][0], gph[x][1]);
		mask_small[x] = (mask_small[gph[x][0]] | mask_small[gph[x][1]]);
	}
}

void actuallylabelshits(int x) {
	if (comps[x][1] == comps[x][0] + 1) {
		mask_to_normal[mask_small[x]] = piv++;
		//	cout << "leaf " << mask_small[x] << "\n";
	} else {
		assert(sz(gph[x]) == 2);
		mask_to_normal[mask_small[x]] = piv++;
		actuallylabelshits(gph[x][0]);
		actuallylabelshits(gph[x][1]);
		//	cout << "internal " << mask_small[x] << "\n";
	}
}

lint get_ord(int x) {
	if (comps[x][1] == comps[x][0] + 1) {
		return 0;
	} else {
		assert(sz(gph[x]) == 2);
		lint A = get_ord(gph[x][0]);
		lint B = get_ord(gph[x][1]);
		lint ord = 0;
		for (int j = mask_small[x]; j >= mask_small[gph[x][1]]; j = (j - 1) & mask_small[x]) {
			if (j > mask_small[gph[x][1]]) {
				ord += dp[j] * dp[mask_small[x] - j];
			} else if (j == mask_small[gph[x][1]]) {
				ord += A * dp[mask_small[gph[x][1]]] + B;
				break;
			}
		}
		return ord;
	}
}
} // namespace

std::string aoi(int n, int m, int Q, int K, std::vector<int> A, std::vector<int> B, std::vector<long long> C, std::vector<int> T, std::vector<int> X) {
	vector<lint> dist(n, 1e18);
	vector<int> par(n);
	{
		vector<vector<pi>> gph(n);
		for (int i = 0; i < m; i++) {
			gph[A[i]].push_back({C[i], B[i]});
			gph[B[i]].push_back({C[i], A[i]});
		}
		priority_queue<pi, vector<pi>, greater<pi>> pq;
		dist[0] = 0;
		pq.push({0, 0});
		while (sz(pq)) {
			auto [d, v] = pq.top();
			pq.pop();
			if (dist[v] != d)
				continue;
			for (auto &[c, w] : gph[v]) {
				if (dist[w] > dist[v] + c) {
					dist[w] = dist[v] + c;
					par[w] = v;
					pq.push({dist[w], w});
				}
			}
		}
		for (int i = 1; i < n; i++) {
			tr[par[i]].push_back(i);
		}
		for (int i = 0; i < Q; i++) {
			revidx[T[i]] = i;
			mark[T[i]] = 1;
		}
	}
	dfs(0);
	sort(all(comps), [&](const pi &a, const pi &b) { return pi{a[0], -a[1]} < pi{b[0], -b[1]}; });
	assert(sz(comps) == 2 * Q - 1);
	for (int i = 1; i < sz(comps); i++) {
		int pari = -1;
		for (int j = i - 1; j >= 0; j--) {
			if (comps[j][1] >= comps[i][1]) {
				pari = j;
				break;
			}
		}
		assert(~pari);
		gph[pari].push_back(i);
	}
	dp.resize(1 << Q);
	for (int i = 1; i < sz(dp); i++) {
		if (__builtin_popcount(i) == 1)
			dp[i] = 1;
		else {
			for (int j = i; j >= (i - j); j = (j - 1) & i)
				dp[i] += dp[j] * dp[i - j];
		}
	}

	piv = 0;
	memset(mask_to_normal, -1, sizeof(mask_to_normal));
	// compute submask info
	normalize(0);
	// normalize, so that childs are ordered per submasks, and vertices are labeled per preorder
	actuallylabelshits(0);
	string ans;
	for (int i = 0; i < K; i++) {
		int u = A[X[i]], v = B[X[i]];
		if (dist[u] > dist[v])
			swap(u, v);
		if (par[v] == u) {
			int pos = sz(comps);
			if (mask[v] > 0) {
				pos = mask_to_normal[mask[v]];
				assert(pos != -1);
			}
			for (int j = 4; j >= 0; j--) {
				ans.push_back((pos >> j) % 2 + '0');
			}
		} else {
			int pos = sz(comps);
			for (int j = 4; j >= 0; j--) {
				ans.push_back((pos >> j) % 2 + '0');
			}
		}
	}
	{
		lint ord = get_ord(0);
		for (int i = 59; i >= 0; i--) {
			ans.push_back((ord >> i) % 2 + '0');
		}
		return ans;
	}
}
