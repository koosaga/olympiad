#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 300005;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	int alow = 0;
	vector<pi> vect;
	lint tot = 0;
	for (int i = 0; i < n; i++) {
		int d, tf, ts;
		cin >> d >> tf >> ts;
		alow = max(alow, tf);
		vect.push_back({ts, d});
		tot += d;
	}
	sort(all(vect));
	bitset<MAXN> dp = 0;
	dp[0] = 1;
	lint sum = 0;
	vector<pi> dap;
	dap.push_back({tot, alow});
	for (auto &[d, t] : vect) {
		dp = dp | (dp << t);
		sum = sum + t;
		int pos = dp._Find_next((sum + 1) / 2 - 1);
		alow = max(alow, (int)d);
		if (pos < MAXN)
			dap.push_back({tot - sum + pos, alow});
	}
	sort(all(dap));
	for (int i = 1; i < sz(dap); i++)
		dap[i][1] = min(dap[i][1], dap[i - 1][1]);
	while (q--) {
		int x;
		cin >> x;
		auto it = lower_bound(all(dap), pi{x + 1, -1});
		if (dap.begin() == it)
			cout << "-1\n";
		else
			cout << (*prev(it))[1] << "\n";
	}
}