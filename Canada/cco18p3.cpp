#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 20005;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, e;
	cin >> n >> e;
	vector<int> dp(MAXN, -1e9);
	iota(dp.begin(), dp.begin() + e, 0);
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		vector<int> nxt(MAXN, -1e9);
		int maxval = *max_element(dp.begin(), dp.begin() + a);
		for (int j = 0; j < b; j++)
			nxt[j] = maxval + j;
		for (int j = 0; j < MAXN; j++) {
			if (j >= a + b)
				nxt[j] = max(nxt[j], dp[j]);
			else if (j >= a)
				nxt[j - a] = max(nxt[j - a], dp[j]);
			else if (j + b < MAXN)
				nxt[j + b] = max(nxt[j + b], dp[j] + b);
		}
		dp = nxt;
	}
	cout << *max_element(all(dp)) << "\n";
}