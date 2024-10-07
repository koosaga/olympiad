#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 1600005;

int n;
pi a[MAXN];
int pfx[MAXN], sfx[MAXN];
int dp[MAXN], nxt[MAXN];

void solve() {
    vector<int> v;
	int k, z;
	cin >> z >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].first >> a[i].second;
		v.push_back(a[i].first);
		v.push_back(a[i].first - 1);
		v.push_back(a[i].second);
		v.push_back(a[i].second + 1);
	}
	sort(all(v));
	v.resize(unique(all(v)) - v.begin());
	fill(pfx, pfx + sz(v) + 2, 0);
	fill(sfx, sfx + sz(v) + 2, sz(v) + 1);
	fill(dp, dp + sz(v) + 2, 0);
	iota(nxt, nxt + sz(v) + 2, 0);
	for (int i = 1; i <= n; i++) {
		a[i].first = lower_bound(all(v), a[i].first) - v.begin() + 1;
		a[i].second = lower_bound(all(v), a[i].second) - v.begin() + 1;
		pfx[a[i].first] = max(pfx[a[i].first], a[i].second);
		sfx[a[i].first] = min(sfx[a[i].first], a[i].second);
	}
	for (int i = 1; i <= sz(v); i++)
		pfx[i] = max(pfx[i], pfx[i - 1]);
	for (int i = sz(v); i >= 0; i--)
		sfx[i] = min(sfx[i], sfx[i + 1]);

	dp[sz(v) + 1] = 1;
	nxt[sz(v) + 1] = sz(v) + 1;
	int ptr = sz(v) + 1;
	
	vector<int> ans(z);
	for (int i = sz(v); i >= 0; i--) {
		ptr = min(ptr, sfx[i + 1]);
		while (ptr > i && !dp[ptr])
			ptr--;
		if (dp[ptr] && ptr > pfx[i]) {
			dp[i] = 1;
			nxt[i] = ptr;
		}
	}
	if (dp[0]) {
		for (int i = 0; nxt[i] <= sz(v); i = nxt[i]) {
		    ans[v[nxt[i]-1]-1]++;
		}
	} else {
		cout << "-1\n";
		return;
	}
	for (auto &x : ans)
		cout << x * k << " ";
	cout << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int tc;
	cin >> tc;
	for (int i = 1; i <= tc; i++) {
		solve();
	}
}