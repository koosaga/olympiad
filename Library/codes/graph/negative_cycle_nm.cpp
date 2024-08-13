#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

struct disj {
	vector<int> pa;
	void init(int n) {
		pa.clear();
		pa.resize(n);
		iota(all(pa), 0);
	}
	int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
	bool uni(int p, int q) {
		p = find(p);
		q = find(q);
		if (p == q)
			return 0;
		pa[q] = p;
		return 1;
	}
} disj;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, s;
	cin >> n >> m >> s;
	vector<vector<pi>> gph(n);
	vector<lint> dist(n, 1e18), par(n, -1), pae(n);
	for (int i = 0; i < m; i++) {
		int s, e, x;
		cin >> s >> e >> x;
		gph[s].push_back({x, e});
	}
	dist[s] = 0;
	for (int i = 0; i <= n; i++) {
		bool upd = 0;
		for (int j = 0; j < n; j++) {
			for (auto &[w, k] : gph[j]) {
				if (dist[k] > dist[j] + w) {
					dist[k] = dist[j] + w;
					par[k] = j;
					pae[k] = w;
					upd = 1;
				}
			}
		}
		if (!upd) {
			cout << "PATH\n";
			for (int i = 0; i < n; i++)
				cout << dist[i] << (i + 1 < n ? " " : "\n");
			return 0;
		}
	}
	disj.init(n);
	for (int i = 0; i < n; i++) {
		if (~par[i] && !disj.uni(par[i], i)) {
			vector<int> vis(n);
			cout << "CYCLE\n";
			vector<int> seq;
			lint lsum = 0;
			for (int j = i; !vis[j]; j = par[j]) {
				lsum += pae[j];
				seq.push_back(j);
				vis[j] = 1;
			}
			cout << sz(seq) << "\n";
			reverse(all(seq));
			for (auto &v : seq)
				cout << v << " ";
			cout << seq[0] << "\n";
			return 0;
		}
	}
	assert(0);
}
