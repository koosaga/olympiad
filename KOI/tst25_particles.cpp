#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

vector<vector<int>> gph;
vector<int> comp_nums, closed, counts;
vector<int> blacks;
int tot_black, tot_odd;

void initialize(int N, vector<int> A, vector<int> B) {
	cr(gph, N);
	cr(comp_nums, N);
	cr(blacks, 1);
	cr(closed, N);
	cr(counts, N);
	for (int i = 0; i < N - 1; i++) {
		gph[A[i]].push_back(B[i]);
		gph[B[i]].push_back(A[i]);
	}
}

void update(int x, int c) {
	blacks[x] += c;
	tot_black += c;
	if (abs(c) % 2 != 0) {
		if (blacks[x] % 2 == 1)
			tot_odd++;
		else
			tot_odd--;
	}
}
struct instance {
	queue<pi> que;
	int x, i, p = -1;
	instance() {}
	instance(int v, int par) {
		x = v;
		p = par;
		i = 0;
	}
};

void close(int v) {
	closed[v] = 1;
	vector<instance> inst;
	vector<int> active;
	vector<vector<int>> results;
	for (auto &w : gph[v]) {
		if (!closed[w]) {
			inst.push_back(instance(w, v));
			active.push_back(sz(inst) - 1);
		}
	}
	cr(results, sz(inst));
	if (sz(inst) <= 1)
		return;
	auto prog = [&](instance &inst, vector<int> &result) {
		if (sz(gph[inst.x]) == inst.i) {
			result.push_back(inst.x);
			if (sz(inst.que) == 0)
				return false;
			inst.x = inst.que.front()[0];
			inst.p = inst.que.front()[1];
			inst.i = 0;
			inst.que.pop();
			return true;
		}
		int to_vis = gph[inst.x][inst.i];
		inst.i++;
		if (!closed[to_vis] && to_vis != inst.p) {
			inst.que.push({to_vis, inst.x});
		}
		return true;
	};
	while (sz(active) >= 2) {
		vector<int> nxt;
		for (auto &i : active) {
			if (prog(inst[i], results[i]))
				nxt.push_back(i);
		}
		if (sz(nxt) == 0) {
			nxt.push_back(active[0]);
		}
		active = nxt;
	}
	for (int i = 0; i < sz(results); i++) {
		if (i == active[0])
			continue;
		int new_black = 0;
		int cidx = sz(blacks);
		int prev_num = comp_nums[results[i][0]];
		for (auto &v : results[i]) {
			comp_nums[v] = cidx;
			if (counts[v]) {
				new_black++;
			}
		}
		blacks.push_back(0);
		update(prev_num, -new_black);
		update(cidx, +new_black);
	}
}

int generate(int v, bool result) {
	if (result == true) {
		counts[v] = 1;
		update(comp_nums[v], +1);
	} else {
		close(v);
	}
	return (tot_black - tot_odd) / 2;
}
