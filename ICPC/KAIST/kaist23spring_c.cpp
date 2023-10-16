#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 200005;

vector<int> v, gph[MAXN];

int dfs(int x) {
	int ret = 1;
	for (auto &y : gph[x]) {
		ret += dfs(y);
	}
	v.push_back(ret);
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u;
		cin >> u;
		u--;
		gph[u].push_back(i);
	}
	dfs(0);
	sort(all(v));
	cout << "0";
	lint sum = 0;
	for (int i = 0; i < n; i++) {
		sum += v[i];
		cout << " " << sum - (i + 1);
	}
}