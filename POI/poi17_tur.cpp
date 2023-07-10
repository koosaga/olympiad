#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 2005;

int n;
bitset<MAXN> adj[MAXN], vis;
vector<int> ord;
void dfs(int x) {
	if (vis[x])
		return;
	vis[x] = 1;
	while (true) {
		auto z = (adj[x] & ~vis)._Find_first();
		if (z < n)
			dfs(z);
		else
			break;
	}
	ord.push_back(x);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			int x;
			cin >> x;
			adj[i][j] = 1 - x;
			adj[j][i] = x;
		}
	}
	for (int i = 0; i < n; i++) {
		vis = 0;
		ord.clear();
		dfs(i);
		reverse(all(ord));
		cout << sz(ord);
		for (auto &x : ord)
			cout << " " << x + 1;
		cout << "\n";
	}
}