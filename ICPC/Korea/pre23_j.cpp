#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

lint nxt[1005], dp[1005];
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<lint> v;
	for (int i = 0; i < n; i++) {
		vector<int> a(n);
		for (auto &j : a)
			cin >> j;
		lint cur = 0;
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= n / 3; i++) {
			nxt[0] = -1e18;
			for (int j = 1; j <= n; j++) {
				nxt[j] = nxt[j - 1];
				if (j >= 3)
					nxt[j] = max(nxt[j], dp[j - 3] + a[j - 3] + a[j - 2] + a[j - 1]);
			}
			if (nxt[n] <= cur)
				break;
			v.push_back(nxt[n] - cur);
			memcpy(dp, nxt, sizeof(dp));
			cur = nxt[n];
		}
	}
	sort(all(v));
	reverse(all(v));
	if (k < sz(v))
		v.resize(k);
	cout << accumulate(all(v), 0ll) << "\n";
}
