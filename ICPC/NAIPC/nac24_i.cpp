#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

int n, k;
string s;

char dp[41][41][41][2557];
bool f(int pos, int ncnt, int ccnt, int k) {
	if (pos == n) {
		return ccnt == 0 && k == 0;
	}
	if (~dp[pos][ncnt][ccnt][k])
		return dp[pos][ncnt][ccnt][k];
	int ans = 0;
	if (s[pos] == 'N' || s[pos] == '?') {
		if (!ans && f(pos + 1, ncnt + 1, ccnt, k))
			ans = 1;
	}
	if (s[pos] == 'A' || s[pos] == '?') {
		if (!ans && ncnt * ccnt <= k && f(pos + 1, ncnt, ccnt, k - ncnt * ccnt))
			ans = 1;
	}
	if (s[pos] == 'C' || s[pos] == '?') {
		if (!ans && ccnt && f(pos + 1, ncnt, ccnt - 1, k))
			ans = 1;
	}
	if (s[pos] != 'N' && s[pos] != 'A' && s[pos] != 'C') {
		if (!ans && f(pos + 1, ncnt, ccnt, k))
			ans = 1;
	}
	return dp[pos][ncnt][ccnt][k] = ans;
}

void backtrack(int pos, int ncnt, int ccnt, int k) {
	if (pos == n) {
		return;
	}
	if (s[pos] == 'N' || s[pos] == '?') {
		if (f(pos + 1, ncnt + 1, ccnt, k)) {
			cout << 'N';
			backtrack(pos + 1, ncnt + 1, ccnt, k);
			return;
		}
	}
	if (s[pos] == 'A' || s[pos] == '?') {
		if (ncnt * ccnt <= k && f(pos + 1, ncnt, ccnt, k - ncnt * ccnt)) {
			cout << 'A';
			backtrack(pos + 1, ncnt, ccnt, k - ncnt * ccnt);
			return;
		}
	}
	if (s[pos] == 'C' || s[pos] == '?') {
		if (ccnt && f(pos + 1, ncnt, ccnt - 1, k)) {
			cout << 'C';
			backtrack(pos + 1, ncnt, ccnt - 1, k);
			return;
		}
	}
	if (s[pos] != 'N' && s[pos] != 'A' && s[pos] != 'C') {
		if (f(pos + 1, ncnt, ccnt, k)) {
			cout << 'X';
			backtrack(pos + 1, ncnt, ccnt, k);
			return;
		}
	}
	assert(0);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k >> s;
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i <= n; i++)
		if (f(0, 0, i, k)) {
			backtrack(0, 0, i, k);
			return 0;
		}
	cout << "-1\n";
}