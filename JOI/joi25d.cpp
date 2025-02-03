#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

const int MAXN = 5000005;

int dp[1 << 21], pcnt[1 << 21];
int nxt[MAXN][21];
int fst[MAXN][21];
int paired[MAXN][21];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &x : a)
		cin >> x;
	for (int i = 1; i < (1 << 21); i++) {
		pcnt[i] = pcnt[i - (i & -i)] + 1;
	}
	int m = *max_element(all(a));
	{
		for (int i = 0; i < n; i++)
			a[i] = m - a[i];
		memset(fst[0], -1, sizeof(fst[0]));
		for (int i = 0; i < n; i++) {
			memcpy(fst[i + 1], fst[i], sizeof(fst[i]));
			fst[i + 1][a[i]] = i + 1;
		}
		fill(nxt[n], nxt[n] + m, n);
		for (int i = n - 1; i >= 0; i--) {
			memcpy(nxt[i], nxt[i + 1], sizeof(nxt[i]));
			nxt[i][a[i]] = i;
		}
		fill(paired[n - 1], paired[n - 1] + m, n);
		fill(paired[n], paired[n] + m, n);
		for (int i = n - 2; i >= 0; i--) {
			int pos = nxt[i + 1][a[i]];
			memcpy(paired[i], paired[pos], sizeof(paired[pos]));
			paired[i][a[i + 1]] = i;
		}
	}
	dp[0] = 0;
	vector<int> midx(1 << m);
	iota(all(midx), 0);
	sort(all(midx), [&](int a, int b) { return pi{pcnt[a], -a} < pi{pcnt[b], -b}; });
	int ans = m;
	for (auto &msk : midx) {
		int lo = 1e9;
		for (int j = 0; j < m; j++) {
			if ((msk >> j) & 1)
				continue;
			int poz = nxt[dp[msk]][j];
			for (int k = 0; k < m; k++) {
				if ((msk >> k) & 1)
					continue;
				lo = min(lo, paired[poz][k]);
			}
		}
		if (lo >= n) {
			ans = min(ans, pcnt[msk]);
			continue;
		}
		int last = m;
		for (int j = m - 1; j >= 0; j--) {
			if ((msk >> j) & 1) {
				last = j;
				continue;
			}
			int todo = (msk & ~(1 << last)) | (1 << j);
			if (dp[msk] <= fst[lo + 2][j]) {
				dp[todo] = max(dp[todo], fst[lo + 2][j]);
			}
		}
	}
	cout << ans << "\n";
}