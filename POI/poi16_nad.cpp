#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 200005;

vector<vector<int>> gph;
int dp[MAXN][3][3][3];

void dfs(int v) {
	for (auto &w : gph[v]) {
		gph[w].erase(find(all(gph[w]), v));
		dfs(w);
	}
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			for (int z = 0; z < 3; z++) {
				if (sz(gph[v]) == 0) {
					dp[v][x][y][z] = (z > 0 ? 1e9 : y);
					continue;
				}
				int aux[3];
				aux[0] = 0;
				aux[1] = aux[2] = 1e9;
				for (auto &w : gph[v]) {
					int nxt[3];
					fill(nxt, nxt + 3, 1e9);
					for (int zi = 0; zi < 3; zi++) {
						for (int ai = 0; ai < 3; ai++) {
							if (y + zi >= 1 || x + y + z + ai >= 2) {
								for (int cur = 0; cur < 3; cur++) {
									nxt[min(cur + zi, 2)] = min(nxt[min(cur + zi, 2)], aux[cur] + dp[w][y][zi][ai]);
								}
							}
						}
					}
					memcpy(aux, nxt, sizeof(nxt));
				}
				dp[v][x][y][z] = aux[z] + y;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	gph.resize(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	dfs(0);
	int ans = 1e9;
	for (int j = 0; j < 3; j++) {
		for (int k = 0; k < 3; k++) {
			ans = min(ans, dp[0][0][j][k]);
		}
	}
	cout << ans << "\n";
}