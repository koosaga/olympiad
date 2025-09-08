#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 200005;

pi childs[MAXN];
vector<lint> dp[MAXN][2];
int subsz[MAXN];

void dfs(lint x) {
	subsz[x] = 1;
	for (int j = 0; j < 2; j++) {
		if (childs[x][j]) {
			dfs(childs[x][j]);
			subsz[x] += subsz[childs[x][j]];
		}
	}
	if (subsz[childs[x][0]] == 0 && subsz[childs[x][1]]) {
		cout << "impossible\n";
		exit(0);
	}
	if (subsz[x] == 1) {
		dp[x][0] = dp[x][1] = {x};
		return;
	}
	bool swp = false;
	int L = childs[x][0], R = childs[x][1];
	if (subsz[L] <= subsz[R])
		swap(L, R), swp = 1;
	int ref = sz(dp[L][0]) - sz(dp[R][0]);
	swap(dp[L][0], dp[x][0]);
	swap(dp[L][1], dp[x][1]);
	if (subsz[R] == 0) {
		dp[x][0].push_back(x);
		dp[x][1].push_back(x);
		if (sz(dp[x][0]) == 2 && swp == 0) {
			swap(dp[x][0][0], dp[x][0][1]);
		}
		return;
	}
	for (int i = 0; i < 2; i++) {
		vector<lint> z = {x};
		for (int j = 0; j < sz(dp[R][i]); j++) {
			z.push_back(dp[R][i][j]);
			z.push_back(dp[x][i][ref + j]);
			if (swp)
				swap(z[sz(z) - 2], z[sz(z) - 1]);
		}
		dp[x][i].resize(ref);
		for (auto &p : z)
			dp[x][i].push_back(p);
	}
	if (swp == 0) {
		if (ref == 1)
			swap(dp[x][0][ref - 1], dp[x][0][ref]);
	}
	if (swp == 1) {
		if (ref > 0)
			swap(dp[x][0][ref], dp[x][0][ref + 1]);
		swap(dp[x][1][ref], dp[x][1][ref + 1]);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> childs[i][0] >> childs[i][1];
	dfs(1);
	for (auto &p : dp[1][0])
		cout << p << " ";
	cout << "\n";
	for (auto &p : dp[1][1])
		cout << p << " ";
	cout << "\n";
}