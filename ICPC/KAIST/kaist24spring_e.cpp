#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using node = array<int, 5>;
lint solve(vector<node> a) {
	// (x, y, WB, BW, has right)
	int n = sz(a);
	sort(all(a), [&](const node &a, const node &b) { return pi{-a[0], a[1]} < pi{-b[0], b[1]}; });
	vector<lint> dp = {0}; // bottom T is BW
	int last = 1e7;
	for (int i = 0; i < n;) {
		int j = i;
		while (j < n && a[i][0] == a[j][0])
			j++;
		if (last > a[i][0] + 1) {
			lint z = *max_element(all(dp));
			dp.resize(j - i + 1);
			fill(all(dp), -1e18);
			// case 1. everything BW
			{
				lint allBW = z;
				for (int x = i; x < j; x++)
					allBW += a[x][3];
				dp[j - i] = allBW;
			}
			// else. there are <=howmax BWs
			int howmax = j - i - 1;
			for (int x = i; x < j; x++) {
				if (a[x][4])
					howmax = min(howmax, x - i);
			}
			lint curWB = z;
			for (int x = i; x < j; x++) {
				curWB += a[x][2];
			}
			for (int x = 0; x <= howmax; x++) {
				dp[x] = curWB;
				curWB += a[x + i][3] - a[x + i][2];
			}
		} else {
			vector<lint> nxtdp(j - i + 1, -1e18);
			// case 1. everything BW
			{
				lint allBW = 0;
				int lowestLeft = 1e9;
				for (int x = i; x < j; x++) {
					allBW += a[x][3];
					if (a[x][4])
						lowestLeft = min(lowestLeft, a[x][1]);
				}
				for (int x = 0; x < sz(dp); x++) {
					if (x > 0 && a[i - sz(dp) + x][1] > lowestLeft)
						continue;
					nxtdp[j - i] = max(nxtdp[j - i], allBW + dp[x]);
				}
			}
			// else. there are <=howmax BWs
			int howmax = j - i - 1;
			for (int x = i; x < j; x++) {
				if (a[x][4])
					howmax = min(howmax, x - i);
			}
			lint thisRowCost = 0;
			for (int x = i; x < j; x++) {
				thisRowCost += a[x][2];
			}
			// but it can affect WB in next column, so carefully ass
			lint admissible = -1e18;
			for (int k = sz(dp) - 1; k >= 0; k--) {
				if (k < sz(dp) - 1 && a[j - 1][1] > a[i - sz(dp) + 1 + k][1])
					break;
				admissible = max(admissible, dp[k]);
			}
			for (int x = 0; x <= howmax; x++) {
				nxtdp[x] = max(nxtdp[x], admissible + thisRowCost);
				thisRowCost += a[x + i][3] - a[x + i][2];
			}
			dp = nxtdp;
		}
		last = a[i][0];
		i = j;
	}
	return *max_element(all(dp));
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<node> global;
	vector<vector<node>> points(k - 1);
	for (int i = 0; i < n; i++) {
		int x, y, a, b;
		cin >> x >> y >> a >> b;
		global.push_back({x, y, a, b, 0});
	}
	sort(all(global), [&](const node &a, const node &b) { return pi{a[1], a[0]} < pi{b[1], b[0]}; });
	for (int i = 0; i < n;) {
		int j = i;
		while (j < n && global[j][1] == global[i][1])
			j++;
		for (int k = i; k < j - 1; k++)
			global[k][4] = 1;
		i = j;
	}
	for (auto &[x, y, a, b, z] : global) {
		points[x % (k - 1)].push_back({x / (k - 1), y, a, b, z});
	}
	lint ans = 0;
	for (auto &p : points)
		if (sz(p)) {
			ans += solve(p);
			if (ans < -1e17) {
				cout << "-1\n";
				return 0;
			}
		}
	cout << ans << "\n";
}