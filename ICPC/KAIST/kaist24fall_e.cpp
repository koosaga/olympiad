#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 100005; // ok for n <= 125

struct mcmf {
	struct edg {
		int pos, cap, rev;
		lint cost;
	};
	vector<edg> gph[MAXN];
	void clear() {
		for (int i = 0; i < MAXN; i++)
			gph[i].clear();
	}
	void addEdge(int s, int e, int x, lint c) {
		gph[s].push_back({e, x, (int)gph[e].size(), c});
		gph[e].push_back({s, 0, (int)gph[s].size() - 1, -c});
	}
	lint dist[MAXN];
	int pa[MAXN], pe[MAXN];
	bool inque[MAXN];
	int vis[MAXN], instk[MAXN], rev[MAXN];
	vector<int> ord;
	void dfs(int x) {
		if (vis[x])
			return;
		vis[x] = 1;
		for (auto &y : gph[x])
			if (y.cap > 0)
				dfs(y.pos);
		ord.push_back(x);
	}
	bool spfa(int src, int sink, int n) {
		dfs(src);
		memset(dist, 0x3f, sizeof(dist[0]) * n);
		dist[src] = 0;
		reverse(all(ord));
		for (auto &x : ord) {
			for (int i = 0; i < gph[x].size(); i++) {
				edg e = gph[x][i];
				if (e.cap > 0 && dist[e.pos] > dist[x] + e.cost) {
					dist[e.pos] = dist[x] + e.cost;
					pa[e.pos] = x;
					pe[e.pos] = i;
				}
			}
		}
		return dist[sink] < 1e15;
	}
	lint new_dist[MAXN];
	pair<bool, lint> dijkstra(int src, int sink, int n) {
		priority_queue<pi, vector<pi>, greater<pi>> pq;
		memset(new_dist, 0x3f, sizeof(new_dist[0]) * n);
		new_dist[src] = 0;
		pq.push({0, src});
		bool isSink = 0;
		while (sz(pq)) {
			auto tp = pq.top();
			pq.pop();
			if (new_dist[tp[1]] != tp[0])
				continue;
			int v = tp[1];
			if (v == sink)
				isSink = 1;
			for (int i = 0; i < gph[v].size(); i++) {
				edg e = gph[v][i];
				lint new_weight = e.cost + dist[v] - dist[e.pos];
				if (e.cap > 0 && new_dist[e.pos] > new_dist[v] + new_weight) {
					new_dist[e.pos] = new_dist[v] + new_weight;
					pa[e.pos] = v;
					pe[e.pos] = i;
					pq.push({new_dist[e.pos], e.pos});
				}
			}
		}
		return make_pair(isSink, new_dist[sink]);
	}

	lint match(int src, int sink, int n) {
		spfa(src, sink, n);
		pair<bool, lint> path;
		lint ret = 0;
		while ((path = dijkstra(src, sink, n)).first) {
			for (int i = 0; i < n; i++)
				dist[i] += min(lint(2e15), new_dist[i]);
			lint cap = 1e18;
			for (int pos = sink; pos != src; pos = pa[pos]) {
				cap = min(cap, (lint)gph[pa[pos]][pe[pos]].cap);
			}
			ret += cap * (dist[sink] - dist[src]);
			for (int pos = sink; pos != src; pos = pa[pos]) {
				int rev = gph[pa[pos]][pe[pos]].rev;
				gph[pa[pos]][pe[pos]].cap -= cap;
				gph[pos][rev].cap += cap;
			}
		}
		return ret;
	}
} mf;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	// (2n+1, 2n+3, ..., 4n-1, 4n-1, ..., 2n+1)
	vector<int> lengths(2 * n), sum(2 * n);
	for (int i = 0; i < n; i++)
		lengths[i] = lengths[2 * n - 1 - i] = 2 * n + 1 + 2 * i;
	for (int i = 1; i < 2 * n; i++)
		sum[i] = sum[i - 1] + lengths[i - 1];
	lint dap = 0;
	vector<int> chk(6 * n * n);
	auto G = [&](int u, int v) { return sum[u] + v; };
	auto AutoDirect = [&](int x1, int y1, int x2, int y2, int x) {
		bool m1 = (y1 + (x1 / n)) % 2;
		bool m2 = (y2 + (x2 / n)) % 2;
		assert(m1 != m2);
		if (m1 > m2)
			swap(x1, x2), swap(y1, y2);
		mf.addEdge(G(x1, y1), G(x2, y2), 1, x);
	};
	auto ReverseDirect = [&](int x1, int y1, int x2, int y2, int x) {
		bool m1 = (y1 + (x1 / n)) % 2;
		bool m2 = (y2 + (x2 / n)) % 2;
		assert(m1 != m2);
		if (m1 < m2)
			swap(x1, x2), swap(y1, y2);
		dap += x;
		mf.addEdge(G(x1, y1), G(x2, y2), 1, -x);
		assert(chk[G(x1, y1)] == 0);
		assert(chk[G(x2, y2)] == 0);
		chk[G(x1, y1)] = chk[G(x2, y2)] = 1;
	};
	for (int i = 0; i < 2 * n; i++) {
		for (int j = 0; j < lengths[i] - 1; j++) {
			int x;
			cin >> x;
			AutoDirect(i, j, i, j + 1, x);
		}
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j <= lengths[i] / 2; j++) {
			int x;
			cin >> x;
			ReverseDirect(i, 2 * j, i + 1, 2 * j + 1, x);
		}
	}
	for (int j = 0; j < 2 * n; j++) {
		int x;
		cin >> x;
		ReverseDirect(n - 1, 2 * j, n, 2 * j, x);
	}
	for (int i = n; i < 2 * n - 1; i++) {
		for (int j = 0; j <= lengths[i + 1] / 2; j++) {
			int x;
			cin >> x;
			ReverseDirect(i, 2 * j + 1, i + 1, 2 * j, x);
		}
	}
	// Consider a symmetric difference between the current state and any optimal solution.
	// That symmetric difference consists of n paths from unchecked S to unchecked T
	// plus possibly some negative cycles, but which don't go through source or sink.
	// You can remove edges that will be clearly unused
	// and hope that negative cycle don't pop up
	// which will actually not pop up, as the initial state doesn't contain ANY cycles.
	for (int i = 0; i < 2 * n; i++) {
		for (int j = 0; j < lengths[i]; j++) {
			int v = G(i, j);
			if (chk[v])
				continue;
			if ((i / n + j) % 2 == 0) {
				if (!chk[v])
					mf.addEdge(6 * n * n, v, 1, 0);
				else
					mf.addEdge(v, 6 * n * n, 1, 0);
			} else {
				if (!chk[v])
					mf.addEdge(v, 6 * n * n + 1, 1, 0);
				else
					mf.addEdge(6 * n * n + 1, v, 1, 0);
			}
		}
	}
	cout << dap + mf.match(6 * n * n, 6 * n * n + 1, 6 * n * n + 2) << "\n";
}