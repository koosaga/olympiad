#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

// code written by https://loj.ac/u/teapotd
template <class flow_t> struct HLPP {
	struct Edge {
		int to, inv;
		flow_t rem, cap;
	};
	vector<vector<Edge>> G;
	vector<flow_t> excess;
	vector<int> hei, arc, prv, nxt, act, bot;
	queue<int> Q;
	int n, high, cut, work;
	HLPP(int k) : G(k) {}
	int addEdge(int u, int v, flow_t cap, flow_t rcap = 0) {
		assert(u != v);
		G[u].push_back({v, sz(G[v]), cap, cap});
		G[v].push_back({u, sz(G[u]) - 1, rcap, rcap});
		return sz(G[u]) - 1;
	}
	void raise(int v, int h) {
		prv[nxt[prv[v]] = nxt[v]] = prv[v];
		hei[v] = h;
		if (excess[v] > 0) {
			bot[v] = act[h];
			act[h] = v;
			high = max(high, h);
		}
		if (h < n)
			cut = max(cut, h + 1);
		nxt[v] = nxt[prv[v] = h += n];
		prv[nxt[nxt[h] = v]] = v;
	}
	void global(int s, int t) {
		hei.assign(n, n * 2);
		act.assign(n * 2, -1);
		iota(all(prv), 0);
		iota(all(nxt), 0);
		hei[t] = high = cut = work = 0;
		hei[s] = n;
		for (int x : {t, s})
			for (Q.push(x); !Q.empty(); Q.pop()) {
				int v = Q.front();
				for (auto &e : G[v])
					if (hei[e.to] == n * 2 && G[e.to][e.inv].rem)
						Q.push(e.to), raise(e.to, hei[v] + 1);
			}
	}
	void push(int v, Edge &e, bool z) {
		auto f = min(excess[v], e.rem);
		if (f > 0) {
			if (z && !excess[e.to]) {
				bot[e.to] = act[hei[e.to]];
				act[hei[e.to]] = e.to;
			}
			e.rem -= f;
			G[e.to][e.inv].rem += f;
			excess[v] -= f;
			excess[e.to] += f;
		}
	}
	void discharge(int v) {
		int h = n * 2, k = hei[v];
		for (int j = 0; j < sz(G[v]); j++) {
			auto &e = G[v][arc[v]];
			if (e.rem) {
				if (k == hei[e.to] + 1) {
					push(v, e, 1);
					if (excess[v] <= 0)
						return;
				} else
					h = min(h, hei[e.to] + 1);
			}
			if (++arc[v] >= sz(G[v]))
				arc[v] = 0;
		}
		if (k < n && nxt[k + n] == prv[k + n]) {
			for (int j = k; j < cut; j++)
				while (nxt[j + n] < n)
					raise(nxt[j + n], n);
			cut = k;
		} else
			raise(v, h), work++;
	}
	// Compute maximum flow from src to dst
	flow_t flow(int src, int dst) {
		excess.assign(n = sz(G), 0);
		arc.assign(n, 0);
		prv.assign(n * 3, 0);
		nxt.assign(n * 3, 0);
		bot.assign(n, 0);
		for (auto &e : G[src])
			excess[src] = e.rem, push(src, e, 0);
		global(src, dst);
		for (; high; high--)
			while (act[high] != -1) {
				int v = act[high];
				act[high] = bot[v];
				if (v != src && hei[v] == high) {
					discharge(v);
					if (work > 4 * n)
						global(src, dst);
				}
			}
		global(src, dst);
		return excess[dst];
	}
	// Get flow through e-th edge of vertex v
	flow_t getFlow(int v, int e) { return G[v][e].cap - G[v][e].rem; }
	// Get if v belongs to cut component with src
	bool cutSide(int v) { return hei[v] >= n; }
};

template <class T> struct Circulation {
	const T INF = numeric_limits<T>::max() / 2;
	T lowerBoundSum = 0;
	HLPP<T> mf;

	// Initialize for n vertices
	Circulation(int k) : mf(k + 2) {}
	void addEdge(int s, int e, T l, T r) {
		mf.addEdge(s + 2, e + 2, r - l);
		if (l > 0) {
			mf.addEdge(0, e + 2, l);
			mf.addEdge(s + 2, 1, l);
			lowerBoundSum += l;
		} else {
			mf.addEdge(0, s + 2, -l);
			mf.addEdge(e + 2, 1, -l);
			lowerBoundSum += -l;
		}
	}
	bool solve(int s, int e) {
		//       mf.addEdge(e+2, s+2, INF); // to reduce as maxflow with lower bounds, in circulation problem skip this line
		return lowerBoundSum == mf.flow(0, 1);
		// to get maximum LR flow, run maxflow from s+2 to e+2 again
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, a, b, c;
	cin >> n >> m >> a >> b >> c;
	vector<string> s(n);
	for (int i = 0; i < n; i++) {
		cin >> s[i];
	}
	auto BHQ = [&](int x, int y) { return (x * m + y); };
	auto WVQ = [&](int x, int y) { return n * m + (x * m + y); };
	auto BV = [&](int x, int y) { return 2 * n * m + (x * m + y); };
	auto WH = [&](int x, int y) { return 3 * n * m + (x * m + y); };
	int SRC = 4 * n * m;
	int SNK = 4 * n * m + 1;
	int inf = 1e6;
	HLPP<lint> mf(4 * n * m + 2);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (s[i][j] == '#') {
				mf.addEdge(BV(i, j), BHQ(i, j), c);
				mf.addEdge(WVQ(i, j), SNK, inf);
				mf.addEdge(SRC, WH(i, j), inf);
			} else {
				mf.addEdge(WH(i, j), BV(i, j), c);
				mf.addEdge(BHQ(i, j), WVQ(i, j), c);
				mf.addEdge(BHQ(i, j), BV(i, j), inf);
			}
			mf.addEdge(BHQ(i, j), WH(i, j), inf);
			mf.addEdge(WVQ(i, j), BV(i, j), inf);
			mf.addEdge(SRC, BV(i, j), a);
			mf.addEdge(SRC, WH(i, j), a);
			mf.addEdge(BHQ(i, j), SNK, a);
			mf.addEdge(WVQ(i, j), SNK, a);
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 1; j <= m; j++) {
			mf.addEdge((j == m ? SRC : WH(i, j)), WH(i, j - 1), b);
			mf.addEdge(BHQ(i, j - 1), (j == m ? SNK : BHQ(i, j)), b);
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 1; j <= n; j++) {
			mf.addEdge((j == n ? SRC : BV(j, i)), BV(j - 1, i), b);
			mf.addEdge(WVQ(j - 1, i), (j == n ? SNK : WVQ(j, i)), b);
		}
	}
	cout << mf.flow(SRC, SNK) << "\n";
}
