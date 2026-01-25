#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXL = 20;
const int MAXN = 200005;

int dp[MAXL][MAXN];
int sum[MAXN];
vector<int> a;

long long initialize(int N, std::vector<int> A) {
	a = A;
	for (int i = 0; i < N; i++)
		dp[0][i] = 1;
	for (int i = 1; i < 20; i++) {
		int g = (1 << (i - 1));
		for (int j = g; j + g < N; j++) {
			dp[i][j] = (dp[i - 1][j - g] & dp[i - 1][j + g] & (a[j - g] < a[j] && a[j + g] < a[j]));
		}
	}
	for (int i = 0; i < 20; i++)
		sum[i] = accumulate(dp[i], dp[i] + N, 0);
	return accumulate(sum, sum + 20, 0);
}

long long update_sequence(int p, int v) {
	a[p] = v;
	set<int> to_upd;
	for (int i = 1; i < 20; i++) {
		int g = (1 << (i - 1));
		to_upd.insert(p - g);
		to_upd.insert(p);
		to_upd.insert(p + g);
		set<int> nxt;
		for (auto &j : to_upd) {
		    if(j < g || j + g >= sz(a)) continue;
			int newval = (dp[i - 1][j - g] & dp[i - 1][j + g] & (a[j - g] < a[j] && a[j + g] < a[j]));
			if (dp[i][j] != newval) {
				sum[i] -= dp[i][j];
				sum[i] += newval;
				dp[i][j] = newval;
				nxt.insert(j - 2 * g);
				nxt.insert(j + 2 * g);
			}
		}
		to_upd = nxt;
	}
	return accumulate(sum, sum + 20, 0);
}