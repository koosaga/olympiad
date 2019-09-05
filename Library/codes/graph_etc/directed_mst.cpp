// starts from node 0. assumes there exists at least one dmst.
// edge is reversed : if there is edge s -> e, INSERT IN gph[e]
struct edge { int to, cost, id; };
using elist = vector<edge>;
void dmst(vector<elist> &g, vector<int>& res) {
	const int n = g.size();
	vector<edge*> to(n);
	vector<int> u(n, 0);
	for (int i = 1; i < n; ++i) {
		int mn = g[i][0].cost;
		for (int j = 0; j < g[i].size(); ++j)
			mn = min(mn, g[i][j].cost);
		for (int j = 0; j < g[i].size(); ++j) {
			if (g[i][j].cost == mn)
				to[i] = &g[i][j];
			g[i][j].cost -= mn;
		}
	}
	for (int i = 1; i < n; ++i) {
		if (u[i]) continue;
		int x = i;
		vector<int> order(1, x);
		u[x] = 1;
		while (to[x]->to > 0 && u[to[x]->to] == 0) {
			x = to[x]->to;
			u[x] = 1;
			order.push_back(x);
		}
		int y = to[x]->to;
		vector<int> cycle(find(order.begin(), order.end(), y), order.end());
		if (cycle.size() == 0) continue;
		vector<int> in_cycle(n);
		for (int j = 0; j < cycle.size(); ++j) in_cycle[cycle[j]] = 1;
		vector<int> nw_id(n);
		for (int j = 1; j < n; ++j) nw_id[j] = nw_id[j - 1] + !in_cycle[j];
		int nn = n - cycle.size();
		vector<elist> gn(nn + 1);
		for (int j = 1; j < n; ++j) {
			if (in_cycle[j]) {
				for (int k = 0; k < g[j].size(); ++k)
					if (!in_cycle[g[j][k].to])
						gn[nn].push_back({nw_id[g[j][k].to], g[j][k].cost, g[j][k].id});
			} else {
				for (int k = 0; k < g[j].size(); ++k)
					if (in_cycle[g[j][k].to])
						gn[nw_id[j]].push_back({nn, g[j][k].cost, g[j][k].id});
					else
						gn[nw_id[j]].push_back({nw_id[g[j][k].to], g[j][k].cost, g[j][k].id});
			}
		}
		dmst(gn, res);
		set<int> used_e(res.begin(), res.end());
		for (int j = 0; j < cycle.size(); ++j) {
			bool found = false;
			for (int k = 0; k < g[cycle[j]].size(); ++k)
				found |= used_e.count(g[cycle[j]][k].id);
			if (found) {
				for (int k = 0; k < cycle.size(); ++k) {
					if (k != j)
						res.push_back(to[cycle[k]]->id);
				}
				return;
			}
		}
	}
	for (int i = 1; i < n; ++i) res.push_back(to[i]->id);
}
