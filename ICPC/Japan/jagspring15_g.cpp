#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXT = 132000;
const int mod = 1e9 + 7; // 1e9 + 7;//993244853;

int n, m;
vector<string> a;
string ans;

bool vis[1 << 16][16][6];
vector<vector<int>> orders[16];

int locate(int pos, vector<int> v) {
	vector<int> w = v;
	sort(all(w));
	for (int i = 0; i < sz(v); i++) {
		v[i] = lower_bound(all(w), v[i]) - w.begin();
	}
	for (int i = 0; i < sz(orders[pos]); i++) {
		if (orders[pos][i] == v)
			return i;
	}
	assert(0);
}

string ansex = "z";
bool dfs(int msk, int prv, int onum) {
	if (msk == (1 << n) - 1) {
		ansex = min(ans, ansex);
		return 1;
	}
	if (vis[msk][prv][onum])
		return 0;
	vis[msk][prv][onum] = 1;
	auto ord = orders[prv][onum];
	for (int i = 0; i < n; i++) {
		if ((msk >> i) & 1)
			continue;
		bool ok = 1;
		for (int j = 0; j + 1 < m; j++) {
			if (ord[a[i][j] - 'A'] < ord[a[i][j + 1] - 'A']) {
				ok = 0;
				break;
			}
		}
		if (!ok)
			continue;
		ans.push_back(i + 'A');
		vector<int> nord = ord;
		for (int j = 0; j < m; j++) {
			nord[a[i][j] - 'A'] = n + j;
		}
		int k = locate(i, nord);
		if (dfs(msk | (1 << i), i, k)) {
			return 1;
		}
		ans.pop_back();
	}
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	cr(a, n);
	for (auto &x : a)
		cin >> x;
	for (int i = 0; i < n; i++) {
		vector<int> chk(n), ord;
		for (int j = 0; j < m; j++)
			chk[a[i][j] - 'A'] = 1;
		for (int j = 0; j < n; j++) {
			if (!chk[j])
				ord.push_back(j);
		}
		do {
			vector<int> h(n, 0);
			for (int k = 0; k < sz(ord); k++)
				h[ord[k]] = sz(ord) - k - 1;
			for (int j = 0; j < m; j++)
				h[a[i][j] - 'A'] = j + sz(ord);
			orders[i].push_back(h);
		} while (next_permutation(all(ord)));
	}
	for (int i = 0; i < n; i++) {
		ansex = "z";
		for (int j = 0; j < sz(orders[i]); j++) {
			ans.clear();
			ans.push_back(i + 'A');
			dfs(1 << i, i, j);
		}
		if (ansex != "z") {
			cout << ansex << endl;
			return 0;
		}
		ans.pop_back();
	}
}