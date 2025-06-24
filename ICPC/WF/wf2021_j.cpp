#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

pi par[50005];
int sz[50005];

int query(int x, int k) {
	if (k >= sz[x])
		return -1;
	// cout << x << " " << k << endl;
	if (x == 0)
		return k;
	if (par[x][1] >= 0) {
		if (k < min(sz[par[x][0]], sz[par[x][1]]) * 2) {
			return query(par[x][k % 2], k / 2);
		}
		k -= min(sz[par[x][0]], sz[par[x][1]]) * 2;
		if (sz[par[x][0]] > sz[par[x][1]])
			return query(par[x][0], k + sz[par[x][1]]);
		else
			return query(par[x][1], k + sz[par[x][0]]);
	}

	return query(par[x][0], k * 2 + 2 + par[x][1]);
}

int f(int x) {
	if (~sz[x])
		return sz[x];
	if (par[x][1] >= 0)
		return sz[x] = f(par[x][0]) + f(par[x][1]);
	else {
		return sz[x] = ((par[x][1] == -2) + f(par[x][0])) / 2;
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	memset(sz, -1, sizeof(sz));
	int m, q;
	cin >> sz[0] >> m >> q;
	for (int i = 0; i < m; i++) {
		string s;
		cin >> s;
		int x, y, z;
		cin >> x >> y >> z;
		x--;
		y--;
		z--;
		if (s == "S") {
			par[y] = {x, -2};
			par[z] = {x, -1};
		} else {
			par[z] = {x, y};
		}
		// assert(sz[z] <= sz[0]);
	}
	while (q--) {
		int x, k;
		cin >> x >> k;
		f(x - 1);
		int ans = query(x - 1, k - 1);
		if (ans < 0)
			cout << "none\n";
		else
			cout << ans + 1 << "\n";
	}
}