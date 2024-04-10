#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 200005;

int par[MAXN], pae[MAXN];
vector<int> gph[MAXN];
map<int, int> mp[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int m, n;
	string s;
	cin >> m >> n;
	cin >> s;
	int ans = 2 * n;
	int p = 0;
	for (int i = 0; i < n && p < sz(s); i++) {
		int q = p + 1;
		int r = p;
		while (r < sz(s) && s[r] == s[p])
			r++;
		r++;
		if (q <= sz(s))
			ans--;
		if (r <= sz(s))
			ans--;
		p = r;
	}
	cout << ans << "\n";
}