// Implmemtation of https://www.sciencedirect.com/science/article/pii/S0022000076800451
// Coded By Aeren
// https://github.com/infossm/infossm.github.io/blob/10c3bcc308147b9da0ef6b00c57fb186d88bc118/_posts/2021-10-20-PQ_Tree_Part_1.md
// Elements are 0-based

struct pq_tree {
	int n;
	bool is_null_tree = false;
	vector<vector<int>> gph;
	/*
		For internal nodes, data indicates whether current node is P node(stores 0) or Q node(stores 1).
		For leaf nodes, data represents the value
		P node: Can shuffle all childs (|ch| >= 2)
		Q node: Can reverse all childs (|ch| >= 3)
	*/
	vector<int> data;
	pq_tree(int n) : n(n), gph(n + 1), data(n + 1), label(n + 1), in_s(n) {
		gph[0].resize(n);
		iota(gph[0].begin(), gph[0].end(), 1);
		iota(data.begin() + 1, data.end(), 0);
	}
	operator bool() { return !is_null_tree; }
	int new_node(int type, int state) {
		gph.emplace_back();
		data.push_back(type);
		label.push_back(state);
		return (int)gph.size() - 1;
	}
	/*
		Label
		0: empty
		1: full
		2: partial
	*/
	vector<int> label, in_s;
	// Constrain the permutation so that elements in S appear as a consecutive subsegments
	// O(n^2)? but it's very fast
	bool reduce(const vector<int> &s) {
		if (is_null_tree)
			return false;
		if ((int)s.size() == 1)
			return true;
		fill(in_s.begin(), in_s.end(), false);
		for (auto x : s)
			in_s[x] = true;
		bool done = false;
		auto dfs = [&](auto self, int u) -> int {
			if (gph[u].empty()) {
				// Leaf node
				return label[u] = in_s[data[u]];
			}
			int deg = (int)gph[u].size(), pertinence = 0;
			array<int, 3> count{};
			for (auto v : gph[u]) {
				pertinence += self(self, v);
				if (is_null_tree || done)
					return 0;
				++count[label[v]];
			}
			bool is_root = pertinence == (int)s.size();
			if (data[u] == 0) {
				// P node
				if (count[0] == deg) {
					// Template P0
					label[u] = 0;
				} else if (count[1] == deg) {
					// Template P1
					label[u] = 1;
				} else if (count[0] + count[1] == deg) {
					if (is_root) {
						// Template P2
						int u2 = new_node(0, 1);
						auto it = partition(gph[u].begin(), gph[u].end(), [&](int v) { return label[v] == 0; });
						move(it, gph[u].end(), back_inserter(gph[u2]));
						gph[u].erase(it, gph[u].end());
						gph[u].push_back(u2);
					} else {
						// Template P3
						array<int, 2> v;
						for (auto t = 0; t < 2; ++t) {
							if (count[t] == 1) {
								v[t] = *find_if(gph[u].begin(), gph[u].end(), [&](int v) { return label[v] == t; });
							} else {
								v[t] = new_node(0, t);
								auto it = partition(gph[u].begin(), gph[u].end(), [&](int v) { return label[v] != t; });
								move(it, gph[u].end(), back_inserter(gph[v[t]]));
							}
						}
						gph[u] = {v[0], v[1]};
						data[u] = 1;
						label[u] = 2;
					}
				} else if (count[2] == 1) {
					if (is_root) {
						// Template P4
						if (auto it = partition(gph[u].begin(), gph[u].end(), [&](int v) { return label[v] != 1; }); gph[u].end() - it >= 2) {
							int u2 = new_node(0, 1);
							move(it, gph[u].end(), back_inserter(gph[u2]));
							gph[u].erase(it, gph[u].end());
							for (auto v : gph[u]) {
								if (label[v] == 2) {
									if (label[gph[v].back()] != 1)
										reverse(gph[v].begin(), gph[v].end());
									gph[v].push_back(u2);
									break;
								}
							}
						} else if (gph[u].end() - it == 1) {
							int u2 = gph[u].back();
							gph[u].pop_back();
							for (auto v : gph[u]) {
								if (label[v] == 2) {
									if (label[gph[v].back()] != 1)
										reverse(gph[v].begin(), gph[v].end());
									gph[v].push_back(u2);
									break;
								}
							}
						}
						if (count[0] == 0) {
							int v = gph[u][0];
							gph[u] = gph[v];
							gph[v].clear();
							data[u] = 1;
							label[u] = 2;
						}
					} else {
						// Template P5
						array<int, 2> v{-1, -1};
						for (auto t = 0; t < 2; ++t) {
							if (count[t] == 1)
								v[t] = *find_if(gph[u].begin(), gph[u].end(), [&](int v) { return label[v] == t; });
							else if (count[t] >= 2) {
								v[t] = new_node(0, t);
								for (auto w : gph[u])
									if (label[w] == t)
										gph[v[t]].push_back(w);
							}
						}
						int pu = *find_if(gph[u].begin(), gph[u].end(), [&](int v) { return label[v] == 2; });
						if (label[gph[pu][0]])
							reverse(gph[pu].begin(), gph[pu].end());
						gph[u].clear();
						if (~v[0])
							gph[u].push_back(v[0]);
						move(gph[pu].begin(), gph[pu].end(), back_inserter(gph[u]));
						if (~v[1])
							gph[u].push_back(v[1]);
						data[u] = 1;
						label[u] = 2;
					}
				} else if (count[2] == 2 && is_root) {
					// Template P6
					int v = -1;
					if (count[1] == 1) {
						auto it = find_if(gph[u].begin(), gph[u].end(), [&](int v) { return label[v] == 1; });
						v = *it;
						gph[u].erase(it);
					} else if (count[1] >= 2) {
						v = new_node(0, 1);
						auto it = partition(gph[u].begin(), gph[u].end(), [&](int v) { return label[v] != 1; });
						move(it, gph[u].end(), back_inserter(gph[v]));
						gph[u].erase(it, gph[u].end());
					}
					array<int, 2> w;
					auto it = find_if(gph[u].begin(), gph[u].end(), [&](int v) { return label[v] == 2; });
					w[0] = *it;
					it = find_if(next(it), gph[u].end(), [&](int v) { return label[v] == 2; });
					w[1] = *it;
					if (label[gph[w[0]][0]] != 0)
						reverse(gph[w[0]].begin(), gph[w[0]].end());
					if (~v)
						gph[w[0]].push_back(v);
					if (label[gph[w[1]][0]] != 1)
						reverse(gph[w[1]].begin(), gph[w[1]].end());
					move(gph[w[1]].begin(), gph[w[1]].end(), back_inserter(gph[w[0]]));
					gph[w[1]].clear();
					gph[u].erase(it);
					count[1] = 0;
					if (count[1])
						is_null_tree = true;
				} else
					is_null_tree = true;
			} else {
				// Q node
				if (count[0] == deg) {
					// Template Q0
					label[u] = 0;
				} else if (count[1] == deg) {
					// Template Q1
					label[u] = 1;
				} else {
					if (label[gph[u].back()] == 0)
						reverse(gph[u].begin(), gph[u].end());
					if (label[gph[u].front()] != 0 && label[gph[u].back()] == 2)
						reverse(gph[u].begin(), gph[u].end());
					int i = 0;
					while (label[gph[u][i]] == 0)
						++i;
					int j = i + 1;
					while (j < deg && label[gph[u][j]] == 1)
						++j;
					if (j == deg) {
						// Template Q2
						if (label[gph[u][i]] == 2) {
							int v = gph[u][i];
							auto it = gph[u].erase(gph[u].begin() + i);
							if (label[gph[v][0]] != 0)
								reverse(gph[v].begin(), gph[v].end());
							gph[u].insert(it, gph[v].begin(), gph[v].end());
							gph[v].clear();
						}
						label[u] = 2;
					} else {
						int k = j + 1;
						while (k < deg && label[gph[u][k]] == 0)
							++k;
						if (k == deg && is_root) {
							// Template Q3
							if (i < j && label[gph[u][j]] == 2) {
								int v = gph[u][j];
								auto it = gph[u].erase(gph[u].begin() + j);
								if (label[gph[v].front()] == 0)
									reverse(gph[v].begin(), gph[v].end());
								gph[u].insert(it, gph[v].begin(), gph[v].end());
								gph[v].clear();
							}
							if (label[gph[u][i]] == 2) {
								int v = gph[u][i];
								auto it = gph[u].erase(gph[u].begin() + i);
								if (label[gph[v].back()] == 0)
									reverse(gph[v].begin(), gph[v].end());
								gph[u].insert(it, gph[v].begin(), gph[v].end());
								gph[v].clear();
							}
						} else
							is_null_tree = true;
					}
				}
			}
			if (is_root)
				done = true;
			return pertinence;
		};
		dfs(dfs, 0);
		return !is_null_tree;
	}
	// sample functions
	mint dfs(int x = 0) {
		if (is_null_tree)
			return 0;
		if (sz(gph[x]) == 0)
			return 1;
		mint ans = 1;
		for (auto &y : gph[x]) {
			ans *= dfs(y);
		}
		if (data[x] == 0) {
			for (int i = 1; i <= sz(gph[x]); i++)
				ans *= i;
		}
		if (data[x] == 1) {
			ans *= 2;
		}
		return ans;
	}
	void print_any(int x, vector<int> &ret) {
		assert(!is_null_tree);
		if (sz(gph[x]) == 0) {
			ret.push_back(data[x]);
		} else {
			for (auto &y : gph[x])
				print_any(y, ret);
		}
	}
	template <class T> T count_permutation() const {
		if (is_null_tree)
			return 0;
		vector<T> fact(n + 1, 1);
		for (auto x = 1; x <= n; ++x)
			fact[x] = fact[x - 1] * x;
		auto dfs = [&](auto self, int u) -> T {
			T res = gph[u].empty() ? 1 : data[u] ? 2 : fact[(int)gph[u].size()];
			for (auto v : gph[u])
				res *= self(self, v);
			return res;
		};
		return dfs(dfs, 0);
	}
	vector<int> frontier() const {
		vector<int> order;
		auto dfs = [&](auto self, int u) -> void {
			if (gph[u].empty())
				order.push_back(data[u]);
			for (auto v : gph[u])
				self(self, v);
		};
		dfs(dfs, 0);
		return order;
	}
};