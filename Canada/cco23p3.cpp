#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 500005;

struct bit {
	int tree[MAXN];
	void add(int x, int v) {
		for (int i = x + 2; i < MAXN; i += i & -i)
			tree[i] += v;
	}
	int query(int x) {
		int ret = 0;
		for (int i = x + 2; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit, bit2, bit3;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<pi> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i][0];
		if (i % 2 == 1)
			a[i][0] *= -1;
		a[i][1] = i;
	}
	sort(all(a), [&](const pi &a, const pi &b) { return pi{abs(a[0]), a[1]} < pi{abs(b[0]), b[1]}; });
	lint dp[2] = {0, lint(1e18)};
	for (int i = 0; i < n; i++)
		bit.add(i, 1);
	for (int i = n - 1; i >= 0;) {
		int j = i;
		while (j >= 0 && abs(a[i][0]) == abs(a[j][0])) {
			bit.add(a[j][1], -1);
			j--;
		}
		if (abs(a[i][0]) == 0)
			break;
		vector<array<lint, 3>> values[2];
		for (int k = j + 1; k <= i; k++) {
			int L = bit.query(a[k][1]);
			int R = j + 1 - L;
			if (a[k][0] > 0)
				values[0].push_back({L, R, (int)a[k][1]});
			else
				values[1].push_back({L, R, (int)a[k][1]});
		}
		for (int i = 0; i < 2; i++) {
			for (int j = 1; j < sz(values[i]); j++) {
				values[i][j][0] += values[i][j - 1][0];
			}
			for (int j = sz(values[i]) - 2; j >= 0; j--) {
				values[i][j][1] += values[i][j + 1][1];
			}
		}
		lint nxt[2] = {lint(1e18), lint(1e18)};
		for (int j = 0; j < 2; j++) {
			int LS = (j + 1) % 2;
			int RS = (j + i) % 2;
			int len = sz(values[0]) + sz(values[1]);
			vector<int> seq0(len), seq1(len);
			{
				int pl[2] = {};
				int pr[2] = {sz(values[0]), sz(values[1])};
				for (int x = 0; x < len; x++) {
					int pos = (LS + x) % 2;
					if (pl[pos] < sz(values[pos])) {
						seq0[x] = values[pos][pl[pos]][2];
					}
					pl[pos]++;
				}
				for (int x = len - 1; x >= 0; x--) {
					int pos = (RS + len - 1 - x) % 2;
					pr[pos]--;
					if (pr[pos] >= 0)
						seq1[x] = values[pos][pr[pos]][2];
				}
			}
			lint curinv = 0;
			for (int i = len - 1; i >= 0; i--) {
				curinv += bit2.query(seq1[i] - 1);
				bit2.add(seq1[i], 1);
			}
			for (int k = 0; k <= len; k++) {
				int pl[2] = {};
				int pr[2] = {sz(values[0]), sz(values[1])};
				pl[LS] += (k + 1) / 2;
				pl[LS ^ 1] += k / 2;
				pr[RS] -= (len - k + 1) / 2;
				pr[RS ^ 1] -= (len - k) / 2;
				if (pl[0] == pr[0] && pl[1] == pr[1]) {
					lint cost = curinv;
					for (int i = 0; i < 2; i++) {
						if (pl[i])
							cost += values[i][pl[i] - 1][0];
						if (pl[i] < sz(values[i]))
							cost += values[i][pl[i]][1];
					}
					nxt[j ^ (k % 2)] = min(nxt[j ^ (k % 2)], dp[j] + cost);
				}
				if (k < len) {
					curinv -= bit2.query(seq1[k] - 1);
					curinv -= bit3.query(MAXN - 3) - bit3.query(seq1[k]);
					bit2.add(seq1[k], -1);
					curinv += bit2.query(seq0[k] - 1);
					curinv += bit3.query(MAXN - 3) - bit3.query(seq0[k]);
					bit3.add(seq0[k], +1);
				}
			}
			for (auto &x : seq0)
				bit3.add(x, -1);
		}
		dp[0] = nxt[0];
		dp[1] = nxt[1];
		i = j;
		// cout << dp[0] << " " << dp[1] << endl;
	}
	lint ans = min(dp[0], dp[1]);
	if (ans > 1e12)
		ans = -1;
	cout << ans << "\n";
}