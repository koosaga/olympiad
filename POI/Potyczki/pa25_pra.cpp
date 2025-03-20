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
	int n, t, k;
	cin >> n >> k >> t;
	string s;
	cin >> s;
	vector<array<int, 3>> sum(n + 1);
	for (int i = 0; i < n; i++) {
		sum[i + 1] = sum[i];
		sum[i + 1][s[i] - '1']++;
	}
	auto miss = [&](int l, int r, int msk) {
		int ans = 0;
		for (int i = 0; i < 2; i++) {
			if ((msk >> i) & 1) {
				ans += sum[r][i] - sum[l][i];
			}
		}
		return ans;
	};
	int ans = -1;
	{
		int f = miss(0, n, 1);
		int g = miss(0, n, 2);
		if (f <= k) {
			int tot = n;
			if (f + g > k) {
				tot -= (f + g - k);
			}
			ans = max(ans, tot);
		}
	}
	for (int i = t; i < n; i++) {
		for (int j = i; j + t <= n; j++) {
			// [i-t, i) [i, j) [j, j+t)
			int f = miss(i - t, i, 3) + miss(j, j + t, 3) + miss(0, i - t, 1) + miss(j + t, n, 1);
			int g = miss(0, i - t, 2) + miss(j + t, n, 2);
			if (f <= k) {
				int tot = i - t + (n - j - t);
				if (f + g > k)
					tot -= (f + g - k);
				ans = max(ans, tot);
			}
		}
	}
	cout << ans << "\n";
}