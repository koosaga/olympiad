#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

const int MAXN = 2020 + 1;
// 1-based Vertex index
int vis[MAXN], par[MAXN], orig[MAXN], match[MAXN], aux[MAXN], t, N;
vector<int> conn[MAXN];
queue<int> Q;
void addEdge(int u, int v) {
	conn[u].push_back(v);
	conn[v].push_back(u);
}
void init(int n) {
	N = n;
	t = 0;
	for (int i = 0; i <= n; ++i) {
		conn[i].clear();
		match[i] = aux[i] = par[i] = 0;
	}
}
void augment(int u, int v) {
	int pv = v, nv;
	do {
		pv = par[v];
		nv = match[pv];
		match[v] = pv;
		match[pv] = v;
		v = nv;
	} while (u != pv);
}
int lca(int v, int w) {
	++t;
	while (true) {
		if (v) {
			if (aux[v] == t)
				return v;
			aux[v] = t;
			v = orig[par[match[v]]];
		}
		swap(v, w);
	}
}
void blossom(int v, int w, int a) {
	while (orig[v] != a) {
		par[v] = w;
		w = match[v];
		if (vis[w] == 1)
			Q.push(w), vis[w] = 0;
		orig[v] = orig[w] = a;
		v = par[w];
	}
}
bool bfs(int u) {
	fill(vis + 1, vis + 1 + N, -1);
	iota(orig + 1, orig + N + 1, 1);
	Q = queue<int>();
	Q.push(u);
	vis[u] = 0;
	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();
		for (int x : conn[v]) {
			if (vis[x] == -1) {
				par[x] = v;
				vis[x] = 1;
				if (!match[x])
					return augment(u, x), true;
				Q.push(match[x]);
				vis[match[x]] = 0;
			} else if (vis[x] == 0 && orig[v] != orig[x]) {
				int a = lca(orig[v], orig[x]);
				blossom(x, v, a);
				blossom(v, x, a);
			}
		}
	}
	return false;
}
int Match() {
	int ans = 0;
	// find random matching (not necessary, constant improvement)
	vector<int> V(N - 1);
	iota(V.begin(), V.end(), 1);
	shuffle(V.begin(), V.end(), mt19937(0x94949));
	for (auto x : V)
		if (!match[x]) {
			for (auto y : conn[x])
				if (!match[y]) {
					match[x] = y, match[y] = x;
					++ans;
					break;
				}
		}
	for (int i = 1; i <= N; ++i)
		if (!match[i] && bfs(i))
			++ans;
	return ans;
}
bool isprime(int n) {
	if (n == 1)
		return false;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0)
			return false;
	}
	return true;
}

int prune(int x) {
	while (x % 2 == 0)
		x /= 2;
	return x;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		if (n <= 100) {
			vector<pi> edges;
			for (int x = 1; x <= n; x++) {
				for (int y = 2 * x; y <= n; y += x) {
					if (isprime(y / x))
						edges.push_back({x - 1, y - 1});
				}
			}
			auto MM = [&](vector<pi> edges) {
				init(n);
				for (auto &[x, y] : edges)
					addEdge(x + 1, y + 1);
				return Match();
			};
			int opt = MM(edges);
			int ans = -1;
			set<int> s;
			for (int z = 1; z < n; z += 2) {
				vector<pi> new_edges;
				for (auto &[u, v] : edges) {
					if (u == z || v == z)
						continue;
					new_edges.push_back(pi{u, v});
				}
				if (opt == MM(new_edges)) {
					ans = z + 1;
					break;
				}
			}
			if (ans == -1)
				cout << "second\n";
			else
				cout << "first " << ans << "\n";
		} else {
			int j = (n / 2) + 1;
			if (j % 2)
				j++;
			while (!isprime(j / 2))
				j += 2;
			cout << "first " << j << "\n";
		}
	}
}