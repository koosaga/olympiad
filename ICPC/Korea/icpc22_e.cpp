#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 30005;

struct edge {
	int u, v, w;
};

vector<edge> edg;
vector<int> forb[MAXN * 10];
set<int> unproped[MAXN];
map<pi, int> mp;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, k;
	cin >> m >> n >> k;
	int s, t;
	cin >> s >> t;
	if (s == t) {
		cout << "0\n";
		return 0;
	}
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		edg.push_back({u, v, w});
		unproped[u].insert(i);
		mp[pi(u, v)] = i;
	}
	for (int i = 0; i < m; i++) {
		forb[i].push_back(-1);
		forb[i].push_back(m);
	}
	for (int i = 0; i < k; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		if (!mp.count(pi(a, b)) || !mp.count(pi(b, c)))
			continue;
		int s = mp[pi(a, b)];
		int e = mp[pi(b, c)];
		forb[s].push_back(e);
	}
	priority_queue<pi, vector<pi>, greater<pi>> pq;
	for (int i = 0; i < m; i++)
		sort(all(forb[i]));
	vector<int> dist(m, 1e9);
	auto enq = [&](int v, int w) {
		if (dist[v] > w) {
			//	cout << v << " " << w << endl;
			dist[v] = w;
			pq.emplace(w, v);
		}
	};
	unproped[s].clear();
	for (int i = 0; i < sz(edg); i++) {
		if (edg[i].u == s)
			enq(i, edg[i].w);
	}
	while (sz(pq)) {
		auto x = pq.top();
		pq.pop();
		if (dist[x.second] != x.first)
			continue;
		int vid = edg[x.second].v;
		for (int i = 0; i < sz(forb[x.second]) - 1; i++) {
			int l = forb[x.second][i];
			int r = forb[x.second][i + 1];
			//	cout << "from " << vid << " " << l << " " << r << endl;
			auto it = unproped[vid].upper_bound(l);
			while (true) {
				if (it == unproped[vid].end())
					break;
				if (*it >= r)
					break;
				enq(*it, x.first + edg[*it].w);
				it = unproped[vid].erase(it);
			}
		}
	}
	int ans = 1e9;
	for (int i = 0; i < sz(edg); i++) {
		if (edg[i].v == t)
			ans = min(ans, dist[i]);
	}
	if (ans > 8e8)
		ans = -1;
	cout << ans << "\n";
}