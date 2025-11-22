#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 6969;

vector<pi> gph[MAXN];
lint pot[MAXN], vis[MAXN];

void dfs(int x) {
	if (vis[x])
		return;
	vis[x] = 1;
	for (auto &y : gph[x]) {
		pot[y[1]] = pot[x] + y[0];
		dfs(y[1]);
	}
}

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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<vector<int>> a(n + 2, vector<int>(n + 2));
	for (int i = 0; i <= n + 1; i++) {
		for (int j = 0; j <= n + 1; j++) {
			cin >> a[i][j];
		}
	}
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			int d = a[i][j] - a[i + 1][j] - a[i][j + 1] + a[i + 1][j + 1];
			int l = i + j + 1, r = 3 * n + 10 + i - j;
			gph[l].push_back({-d, r});
			gph[r].push_back({d, l});
		}
	}
	if (n % 2 == 1) {
		dfs(1);
		dfs(2 * n + 10);
	}
	if (n % 2 == 0) {
		dfs(1);
		dfs(2);
		lint sum = 0;
		for (int i = 2 * n + 10; i < 3 * n + 10; i++)
			sum += pot[i];
		if (sum != a[0][0] - a[0][1]) {
			assert(sum + (n / 2) == a[0][0] - a[0][1]);
			for (int i = 2; i < 2 * n + 1; i += 2)
				pot[i]++;
			for (int i = 2 * n + 11; i < 4 * n + 10; i += 2)
				pot[i]++;
		}
	}
	HLPP<lint> mf(4 * n + 12);
	for (int i = 1; i <= 2 * n + 1; i++) {
		mf.addEdge(0, i, pot[i]);
		mf.addEdge(2 * n + 9 + i, 4 * n + 11, pot[2 * n + 9 + i]);
	}
	vector<vector<int>> tab(n, vector<int>(n));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			tab[i - 1][j - 1] = mf.addEdge(i + j, 3 * n + 10 + i - j, 1);
		}
	}
	mf.flow(0, 4 * n + 11);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << mf.getFlow(i + j, tab[i - 1][j - 1]) << " ";
		}
		cout << "\n";
	}
}