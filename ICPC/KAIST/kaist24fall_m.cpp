#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 500005;

int n;
string s;
vector<int> gph[MAXN];
int in[MAXN][2], siz[MAXN];
lint sub[MAXN][2], psub[MAXN][2];

void dfs(int x) {
	for (auto &y : gph[x]) {
		gph[y].erase(find(all(gph[y]), x));
		dfs(y);
		siz[x] += siz[y];
		in[x][0] += in[y][0];
		in[x][1] += in[y][1];
		sub[x][0] += in[y][0] + sub[y][0];
		sub[x][1] += in[y][1] + sub[y][1];
	}
	siz[x]++;
	in[x][s[x] - 'A']++;
}

void dfs2(int x) {
	lint t[2] = {psub[x][0], psub[x][1]};
	for (auto &y : gph[x]) {
		t[0] += sub[y][0] + in[y][0];
		t[1] += sub[y][1] + in[y][1];
	}
	for (auto &y : gph[x]) {
		t[0] -= sub[y][0] + in[y][0];
		t[1] -= sub[y][1] + in[y][1];
		psub[y][0] = t[0] + (in[0][0] - in[y][0]);
		psub[y][1] = t[1] + (in[0][1] - in[y][1]);
		dfs2(y);
		t[0] += sub[y][0] + in[y][0];
		t[1] += sub[y][1] + in[y][1];
	}
}

lint solve() {
	lint ans = 1e18;
	for (int i = 1; i < n; i++) {
		if (siz[i] == in[0][0]) {
			ans = min(ans, sub[i][1] + psub[i][0]);
		}
		if (siz[i] == in[0][1]) {
			ans = min(ans, sub[i][0] + psub[i][1]);
		}
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> s;
	// prepare to cheat
	for (auto &x : s)
		if (x == 'W')
			x = 'A';
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	dfs(0);
	dfs2(0);
	lint edge_cost = 0;
	for (int x = 1; x < n; x++) {
		if (in[x][0] && in[x][0] < in[0][0])
			edge_cost++;
		if (in[x][1] && in[x][1] < in[0][1])
			edge_cost++;
	}
	cout << min(edge_cost, n - 2 + solve()) << "\n";
}