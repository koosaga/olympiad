#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

vector<int> ord;
vector<vector<array<int, 3>>> gph;

void dfs(int x) {
	sort(all(gph[x]));
	for (auto &[a, b, y] : gph[x]) {
		dfs(y);
	}
	ord.push_back(x);
}

struct node {
	set<pi> s;
	lint h;
	int ssz;
	node() { s.clear(), h = 0, ssz = 0; }
	void extend(int d) { h += d; }
	void INSERT(lint x) {
		ssz++;
		lint l = x, r = x + 1;
		auto it = s.lower_bound({l, -1});
		if (it != s.begin() && (*prev(it))[1] == l) {
			it--;
			l = (*it)[0];
			s.erase(it);
		}
		it = s.lower_bound({r, -1});
		if (it != s.end() && (*it)[0] == r) {
			r = (*it)[1];
			s.erase(it);
		}
		s.insert({l, r});
	}
	void merge(node &nd) {
		ssz += nd.ssz;
		for (auto &[l, r] : nd.s) {
			for (lint j = l; j < r; j++) {
				auto it = s.lower_bound({j + 1, -1});
				if (it != s.begin()) {
					it--;
					if ((*it)[0] <= j && j < (*it)[1]) {
						INSERT((*it)[1]);
					} else
						INSERT(j);
				} else
					INSERT(j);
			}
		}
		h = max(h, nd.h);
		if (sz(s))
			h = max(h, (*--s.end())[1]);
		INSERT(h);
		h++;
	}
};

long long compute_min_depth(int N, vector<int> P, vector<int> C, vector<int> D) {
	cr(gph, N);
	for (int i = 0; i < N - 1; i++) {
		gph[P[i]].push_back({D[i], C[i], i + 1});
	}
	dfs(0);
	vector<node> dp(N);
	vector<int> idx(N);
	for (auto &v : ord) {
		if (sz(gph[v]) == 0) {
			dp[v].h = 0;
			idx[v] = v;
			continue;
		}
		int lc = idx[gph[v][0][2]];
		int rc = idx[gph[v][1][2]];
		dp[lc].extend(gph[v][0][1] - 1);
		dp[rc].extend(gph[v][1][1] - 1);
		if (dp[lc].ssz < dp[rc].ssz)
			swap(lc, rc);
		dp[lc].merge(dp[rc]);
		idx[v] = lc;
	}
	return dp[idx[0]].h;
}
