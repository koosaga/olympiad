#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 100005;

struct disj {
	int pa[MAXN];
	void init(int n) { iota(pa, pa + n + 1, 0); }
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
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	vector<vector<int>> gph(n);
	{
		vector<pi> b(n);
		for (int i = 0; i < n; i++)
			cin >> b[i][0], b[i][1] = i;
		sort(all(b));
		vector<int> rev(n);
		for (int i = 0; i < n; i++) {
			a[i] = b[i][0];
			rev[b[i][1]] = i;
		}
		for (int i = 0; i < m; i++) {
			int u, v;
			cin >> u >> v;
			u--;
			v--;
			u = rev[u], v = rev[v];
			gph[u].push_back(v);
			gph[v].push_back(u);
		}
		for (int i = 0; i < n; i++) {
			sort(all(gph[i]));
		}
	}
	vector<int> comp(n);
	iota(all(comp), 0);
	lint ans = 0;
	int ccomp = n;
	while (ccomp > 1) {
		vector<vector<pi>> freeSpace(ccomp);
		vector<pi> nextPtr(ccomp, pi{int(2e9), -1});
		for (int i = 0; i < n;) {
			int j = i;
			while (j < n && comp[i] == comp[j])
				j++;
			freeSpace[comp[i]].push_back({i, j});
			i = j;
		}
		for (int i = 0; i < ccomp; i++) {
			if (sz(freeSpace[i]) == 0) {
				freeSpace[i].push_back({0, n});
				continue;
			}
			vector<pi> nxt;
			if (freeSpace[i][0][0] > 0) {
				nxt.push_back({0, freeSpace[i][0][0]});
			}
			for (int j = 0; j < sz(freeSpace[i]); j++) {
				int k = (j + 1 < sz(freeSpace[i]) ? freeSpace[i][j + 1][0] : n);
				nxt.push_back({freeSpace[i][j][1], k});
			}
			freeSpace[i] = nxt;
		}
		for (int i = 0; i < n; i++) {
			int j = 0;
			bool found = 0;
			for (auto &[l, r] : freeSpace[comp[i]]) {
				for (int k = l; k < r; k++) {
					while (j < sz(gph[i]) && gph[i][j] < k)
						j++;
					if (j < sz(gph[i]) && gph[i][j] == k)
						continue;
					nextPtr[comp[i]] = min(nextPtr[comp[i]], pi{a[i] + a[k] + max(a[i], a[k]), comp[k]});
					found = 1;
					break;
				}
				if (found)
					break;
			}
		}
		disj.init(ccomp);
		for (int i = 0; i < ccomp; i++) {
			if(nextPtr[i][1] == -1){
				cout << "NIE\n";
				return 0;
			}
			if (disj.uni(i, nextPtr[i][1])) {
				ans += nextPtr[i][0];
			}
		}
		vector<int> rev(ccomp);
		ccomp = 0;
		for (int i = 0; i < sz(rev); i++) {
			if (disj.find(i) == i)
				rev[i] = ccomp++;
		}
		for (auto &x : comp)
			x = rev[disj.find(x)];
	}
	cout << ans - accumulate(all(a), 0ll) << "\n";
}
