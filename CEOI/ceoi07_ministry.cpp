#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;

// Given a tree rooted at vertex root, compute the equivalence class up to isomorphism
// In other words, returns a function f : V -> [0 .. K - 1] such that
// - f(u) = f(v) iff sub(u) and sub(v) are isomorphic
// - for all 0 <= i < K, exists v \in V such that f(v) = i
// https://suisen-cp.github.io/cp-library-cpp/

pair<int, vector<int>> isomorphism(const vector<vector<int>> &g, int root) {
	const int n = g.size();
	vector<int> ids(n);
	vector<int> mp1(n, -1);
	vector<map<vector<int>, int>> mps(n);
	int next_id = 0;
	vector<int> ch_ids;
	ch_ids.reserve(n);
	auto dfs = [&](auto dfs, int u, int p) -> void {
		for (int v : g[u])
			if (v != p)
				dfs(dfs, v, u);
		for (int v : g[u])
			if (v != p)
				ch_ids.push_back(ids[v]);
		if (ch_ids.size() == 1) {
			int ch = ch_ids[0];
			ids[u] = mp1[ch] < 0 ? mp1[ch] = next_id++ : mp1[ch];
		} else {
			sort(ch_ids.begin(), ch_ids.end());
			auto [it, inserted] = mps[ch_ids.size()].try_emplace(ch_ids, next_id);
			next_id += inserted;
			ids[u] = it->second;
		}
		ch_ids.clear();
	};
	dfs(dfs, root, -1);
	return {next_id, ids};
}

void calc_depth(vector<vector<int>> &gph, vector<int> &dep, int x = 0, int p = -1) {
	for (auto &y : gph[x]) {
		if (y != p) {
			calc_depth(gph, dep, y, x);
			dep[x] = max(dep[x], dep[y] + 1);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string s;
	cin >> s;
	int n = sz(s) / 2;
	vector<int> stk;
	vector<vector<int>> gph(n);
	vector<int> dep(n);
	int cur = 0;
	for (int i = 0; i < sz(s); i++) {
		if (s[i] == ')')
			stk.pop_back();
		else {
			stk.push_back(cur++);
			if (sz(stk) >= 2) {
				int u = stk[sz(stk) - 2];
				int v = stk.back();
				gph[u].push_back(v);
				gph[v].push_back(u);
			}
		}
	}
	calc_depth(gph, dep);
	int mxdep = *max_element(all(dep));
	vector<set<int>> ids(mxdep + 1);
	auto [_, sol] = isomorphism(gph, 0);
	for (int i = 0; i < n; i++) {
		ids[dep[i]].insert(sol[i]);
	}
	for (int i = 0; i <= mxdep; i++)
		cout << sz(ids[i]) << "\n";
}