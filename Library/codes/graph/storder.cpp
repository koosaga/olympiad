// Given an undirected graph where G + {source, sink} is 2-vertex-connected
// compute a permutation of vertices where
// - the first vertex is a source
// - the last vertex is a sink
// - each non-source vertex has an adjacent vertex which appears earlier in the permutation
// - each non-sink vertex has an adjacent vertex which appears later in the permutation
// ref: https://codeforces.com/contest/1916/submission/239741602
namespace std {

template <class Fun> class y_combinator_result {
	Fun fun_;

  public:
	template <class T> explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

	template <class... Args> decltype(auto) operator()(Args &&...args) { return fun_(std::ref(*this), std::forward<Args>(args)...); }
};

template <class Fun> decltype(auto) y_combinator(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }

} // namespace std
vector<int> storder(vector<vector<int>> adj, int source, int sink) {
	int N = int(adj.size());
	assert(N >= 2);
	assert(source != sink);
	adj[source].insert(adj[source].begin(), sink);
	adj[sink].insert(adj[sink].begin(), source);
	vector<int> depth(N, -1);
	vector<int> lowval(N);
	vector<bool> has_sink(N);
	vector<vector<int>> ch(N);
	y_combinator([&](auto self, int cur, int prv) -> void {
		depth[cur] = prv != -1 ? depth[prv] + 1 : 0;
		lowval[cur] = depth[cur];
		ch[cur].reserve(adj[cur].size());
		has_sink[cur] = (cur == sink);
		for (int nxt : adj[cur]) {
			if (nxt == prv)
				continue;
			if (depth[nxt] == -1) {
				ch[cur].push_back(nxt);
				self(nxt, cur);
				lowval[cur] = min(lowval[cur], lowval[nxt]);
				if (has_sink[nxt])
					has_sink[cur] = true;
				if (lowval[nxt] >= depth[cur] && !has_sink[nxt]) {
					// WARNING: This component will be directed arbitrarily.
					// In practice, we'll just make the first child an extra sink
				}
			} else if (depth[nxt] < depth[cur]) {
				lowval[cur] = min(lowval[cur], depth[nxt]);
			} else {
				// down edge
			}
		}
	})(source, -1);

	// true is after, false is before
	vector<bool> edge_dir(N, false);
	vector<int> lst_nxt(N, -1);
	bool notbcc = false;
	auto lst = y_combinator([&](auto self, int cur) -> array<int, 2> {
		array<int, 2> res{cur, cur};
		for (int nxt : ch[cur]) {
			// If we're on the path to the sink, mark it as downwards.

			bool d;
			if (has_sink[nxt]) {
				d = true;
			} else if (lowval[nxt] >= depth[cur]) {
				notbcc = true;
				// continue;
			} else {
				d = !edge_dir[lowval[nxt]];
			}
			edge_dir[depth[cur]] = d;

			auto ch_res = self(nxt);

			// Join res and ch
			if (!d)
				swap(res, ch_res);
			lst_nxt[exchange(res[1], ch_res[1])] = ch_res[0];
		}
		return res;
	})(source);
	if (notbcc)
		return {};

	vector<int> res(N);
	int cur = lst[0];
	for (int i = 0; i < N; i++) {
		res[i] = cur;
		cur = lst_nxt[cur];
	}
	return res;
}
