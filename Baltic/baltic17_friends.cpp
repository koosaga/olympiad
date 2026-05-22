#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;
const int MAXN = 2505;

int n, b, c;
vector<int> gph[MAXN];
int chk[MAXN];
vector<int> ans;

bool adj[2505][2505];
int getcut(vector<int> v) {
	int ret = 0;
	for (auto &x : v) {
		ret += sz(gph[x]);
		for (auto &y : v) {
			if (adj[x][y])
				ret--;
		}
	}
	return ret;
}

int getcut2(vector<int> &v) {
	int ret = 0;
	for (auto &x : v) {
		for (auto &y : gph[x]) {
			if (chk[y] != 1)
				ret++;
		}
	}
	return ret;
}

bool dfs(int x, int i, int dec, vector<int> toExamine, vector<int> &solset) {
	if (sz(solset) > b)
		return 0;
	if (getcut2(solset) <= c) {
		ans = solset;
		return 1;
	}
	if (dec >= b + c)
		return 0;
	if (sz(gph[x]) == i) {
		while (sz(toExamine) && chk[toExamine.back()] == -1)
			toExamine.pop_back();
		if (sz(toExamine) == 0)
			return 0;
		int v = toExamine.back();
		toExamine.pop_back();
		return dfs(v, 0, dec, toExamine, solset);
	}
	if (chk[gph[x][i]]) {
		return dfs(x, i + 1, dec, toExamine, solset);
	}
	chk[gph[x][i]] = 1;
	toExamine.push_back(gph[x][i]);
	solset.push_back(gph[x][i]);
	if (dfs(x, i + 1, dec + 1, toExamine, solset))
		return 1;
	toExamine.pop_back();
	solset.pop_back();
	chk[gph[x][i]] = -1;
	if (dfs(x, i + 1, dec + 1, toExamine, solset))
		return 1;
	chk[gph[x][i]] = 0;
	return 0;
}

vector<int> sub(vector<int> &a, vector<int> &b) {
	vector<int> ans;
	for (auto &x : a)
		chk[x] = 1;
	for (auto &x : b)
		if (!chk[x])
			ans.push_back(x);
	for (auto &x : a)
		chk[x] = 0;
	return ans;
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> b >> c;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		if (x > b + c) {
			cout << "detention\n";
			return 0;
		}
		gph[i].resize(x);
		for (auto &j : gph[i]) {
			cin >> j;
			adj[i][j] = 1;
		}
		sort(all(gph[i]));
	}
	for (int i = 0; i < n; i++) {
		for (auto &j : gph[i]) {
			if (!adj[j][i]) {
				cout << "detention\n";
				return 0;
			}
		}
	}
	vector<int> cut(n);
	vector<vector<int>> cs(n);
	for (int i = 0; i < n; i++) {
		if (cut[i])
			continue;
		memset(chk, 0, sizeof(chk));
		ans.clear();
		chk[i] = 1;
		vector<int> v, w = {i};
		if (!dfs(i, 0, 1, v, w)) {
			cout << "detention\n";
			return 0;
		}
		sort(all(ans));
		cs[i] = ans;
		for (auto &z : cs[i])
			cut[z] = 1;
	}
	memset(chk, 0, sizeof(chk));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			vector<int> subA = sub(cs[j], cs[i]);
			if (sz(subA) == sz(cs[i]))
				continue;
			if (getcut(subA) <= c)
				cs[i] = subA;
			else {
				vector<int> subB = sub(cs[i], cs[j]);
				if (getcut(subB) <= c)
					cs[j] = subB;
				else
					assert(0);
			}
		}
	}
	vector<vector<int>> ans;
	for (int i = 0; i < n; i++) {
		if (sz(cs[i]))
			ans.push_back(cs[i]);
	}
	cout << "home\n" << sz(ans) << "\n";
	for (auto &i : ans) {
		cout << sz(i);
		for (auto &j : i)
			cout << " " << j;
		cout << "\n";
	}
}
