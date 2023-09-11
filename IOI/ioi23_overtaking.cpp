#include "overtaking.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

set<pi> mp;
lint X, L;

void init(int _L, int N, std::vector<long long> T, std::vector<int> W, int _X, int M, std::vector<int> S) {
	X = _X;
	L = _L;
	vector<set<pi>> traj(M - 1);
	vector<pi> bus;
	for (int i = 0; i < N; i++) {
		if (W[i] > X) {
			bus.push_back({W[i] - X, T[i]});
		}
	}
	sort(all(bus));
	reverse(all(bus));
	for (auto &[w, t] : bus) {
		lint cur = t;
		for (int j = 0; j < M - 1; j++) {
			lint nxt = cur + (S[j + 1] - S[j]) * w;
			auto it = traj[j].lower_bound({cur, -lint(2e18)});
			if (it != traj[j].begin())
				nxt = max(nxt, (*prev(it))[1]);
			traj[j].insert({cur, nxt});
			// cout << j << " " << cur << " " << nxt << endl;
			cur = nxt;
		}
	}
	for (int j = M - 2; j >= 0; j--) {
		for (auto &[ts, te] : traj[j]) {
			lint s = ts, e = te;
			auto it = mp.lower_bound({e, -lint(2e18)});
			if (it != mp.begin())
				e = max(e, (*prev(it))[1]);
			it = mp.lower_bound({s, -lint(2e18)});
			while (it != mp.end() && (*it)[1] <= e) {
				it = mp.erase(it);
			}
			mp.insert({s, e});
		}
	}
}

long long arrival_time(long long Y) {
	auto it = mp.lower_bound({Y, -lint(2e18)});
	if (it != mp.begin())
		Y = max(Y, (*prev(it))[1]);
	return Y + X * L;
}