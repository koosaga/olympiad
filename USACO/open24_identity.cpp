#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 1000005;

int trie[MAXN][2], cnt[MAXN], piv;
lint bloom[MAXN][30];

int dfs(int x) {
	int ans = 0;
	if (!trie[x][0] && !trie[x][1]) {
		bloom[x][0] = 1;
		for (int i = 2; i < 30; i++)
			bloom[x][i] = (1 << (i - 2));
		// idk, corner case?
	} else {
		for (int i = 0; i < 2; i++) {
			if (trie[x][i]) {
				ans += dfs(trie[x][i]);
				for (int j = 1; j < 30; j++) {
					bloom[x][j] += bloom[trie[x][i]][j - 1];
				}
			} else {
				bloom[x][1]++;
				for (int j = 3; j < 30; j++) {
					bloom[x][j] += (1ll << (j - 3));
				}
			}
		}
	}
	for (int i = 0; i < 30; i++) {
		int d = min(1ll * cnt[x], bloom[x][i]);
		ans += d * i;
		bloom[x][i] -= d;
		cnt[x] -= d;
	}
	return ans;
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		int p = 0;
		for (auto &j : s) {
			if (!trie[p][j - '0']) {
				trie[p][j - '0'] = ++piv;
			}
			p = trie[p][j - '0'];
		}
		cnt[p]++;
	}
	cout << dfs(0) << "\n";
}