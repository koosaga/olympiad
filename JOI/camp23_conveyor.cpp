#include "conveyor.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;

int gabs(int x) {
	if (x < 0)
		return ~x;
	return x;
}

int determined[MAXN];
int par[MAXN], pae[MAXN], dep[MAXN];
vector<pi> gph[MAXN];

int comp[MAXN];
int compDepthCount[MAXN][3];

void dfs(int x, int p = -1) {
	if (comp[x] != x)
		compDepthCount[comp[x]][dep[x] % 3]++;
	for (auto &[i, y] : gph[x]) {
		if (y == p)
			continue;
		if (determined[gabs(i)]) {
			comp[y] = y;
		} else
			comp[y] = comp[x];
		par[y] = x;
		pae[y] = ~i;
		dep[y] = dep[x] + 1;
		dfs(y, x);
	}
}

void Solve(int N, std::vector<int> A, std::vector<int> B) {
	for (int i = 0; i < N - 1; i++) {
		gph[A[i]].push_back({i, B[i]});
		gph[B[i]].push_back({~i, A[i]});
	}
	while (count(determined, determined + N - 1, 0)) {
		memset(compDepthCount, 0, sizeof(compDepthCount));
		dfs(0);
		vector<int> is_out(N);
		vector<int> edges(N - 1);
		for (int i = 0; i < N; i++) {
			if (comp[i] != i) {
				int j = max_element(compDepthCount[comp[i]], compDepthCount[comp[i]] + 3) - compDepthCount[comp[i]];
				if (dep[i] % 3 == j)
					is_out[i] = 1;
			}
		}
		for (int i = 0; i < N - 1; i++) {
			if (determined[i]) {
				// if -1: B[i] -> A[i]
				// if +1: A[i] -> B[i]
				if (par[A[i]] == B[i]) { // need route A[i] -> B[i];
					edges[i] = (determined[i] == -1);
				} else {
					edges[i] = (determined[i] == +1);
				}
			}
		}
		auto ans = Query(edges, is_out);
		for (int i = 0; i < N; i++) {
			if (!is_out[i])
				continue;
			if (ans[i]) {
				for (auto &[idx, j] : gph[i]) {
					if (determined[gabs(idx)])
						continue;
					if (idx < 0)
						determined[~idx] = 1;
					else
						determined[idx] = -1;
				}
			} else {
				int wentJasik = 0;
				for (auto &[idx, j] : gph[i]) {
					if (determined[gabs(idx)])
						continue;
					if (j == par[i])
						continue;
					if (ans[j]) {
						wentJasik = 1;
						if (idx < 0)
							determined[~idx] = -1;
						else
							determined[idx] = 1;
					}
				}
				if (!wentJasik) {
					assert(ans[par[i]]);
					if (pae[i] < 0) {
						determined[~pae[i]] = -1;
					} else {
						determined[pae[i]] = 1;
					}
				}
			}
		}
	}
	vector<int> ans(N - 1);
	for (int i = 0; i < N - 1; i++) {
		ans[i] = (1 - determined[i]) / 2;
	}
	Answer(ans);
}
