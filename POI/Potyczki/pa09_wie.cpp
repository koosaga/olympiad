#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXT = 2005;

struct seg {
	int tree[MAXT];
	void init() { fill(tree, tree + MAXT, 2.1e9); }
	int prod(int x) {
		int ret = 2.1e9;
		for (int i = x + 3; i; i -= i & -i)
			ret = min(ret, tree[i]);
		return ret;
	}
	void set(int x, int v) {
		for (int i = x + 3; i < MAXT; i += i & -i)
			tree[i] = min(tree[i], v);
	}
} segL[2005], segR;

int dp[2005][2005];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;

	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];

	for (int i = 0; i <= n; i++)
		segL[i].init();
	for (int e = 0; e <= n; e++) {
		segR.init();
		for (int s = e; s >= 0; s--) {
			if (s != e) {
				int l = s, r = e - 1;
				while (l != r) {
					int m = (l + r) / 2;
					if (dp[s][m] < dp[m + 1][e])
						l = m + 1;
					else
						r = m;
				}
				dp[s][e] = min(segR.prod(l - 1), segL[s].prod(n - l));
			}
			if (s > 0)
				segR.set(s - 1, dp[s][e] + a[s - 1]);
			if (e < n)
				segL[s].set(n - e, dp[s][e] + a[e]);
		}
	}
	cout << dp[0][n] << "\n";
}