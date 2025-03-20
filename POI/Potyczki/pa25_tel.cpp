#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

unsigned long long cands[404][404][7];

void solve() {
	int n;
	cin >> n;
	vector<string> a(n);
	for (auto &x : a)
		cin >> x;
	vector<vector<int>> adj(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j) {
				adj[i][j] = (a[i][j] == '1' ? 1 : int(1e9));
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= n; j++) {
			for (int k = 0; k < 7; k++)
				cands[i][j][k] = 0;
			for (int k = 0; k < n; k++) {
				if (adj[k][i] <= j - 1)
					cands[i][j][k >> 6] |= (1ull << (k & 63));
			}
		}
	}
	auto trial = [&](int t) {
		for (int s = 0; s < n; s++) {
			unsigned long long msk[7] = {};
			for (int i = 0; i < n; i++)
				msk[i >> 6] |= (1ull << (i & 63));
			for (int i = 0; i < n; i++) {
				for (int j = i + 1; j < n; j++) {
					if (adj[i][j] > t) {
						int q1 = max(-1, t - adj[s][i]) + 1;
						int q2 = max(-1, t - adj[s][j]) + 1;
						for (int x = 0; x < 7; x++) {
							msk[x] &= (cands[j][q1][x] | cands[i][q2][x]);
						}
					}
				}
			}
			for (int i = 0; i < 7; i++) {
				if (msk[i])
					return true;
			}
		}
		return false;
	};
	int s = 0, e = n - 1;
	while (s != e) {
		int m = (s + e) / 2;
		if (trial(m))
			e = m;
		else
			s = m + 1;
	}
	cout << s << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int tc;
	cin >> tc;
	while (tc--)
		solve();
}