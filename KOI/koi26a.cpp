#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<vector<int>> a(n), b(n);
	vector<int> deg(n);
	queue<int> que;
	for (int i = 0; i < n; i++) {
		cin >> deg[i];
		a[i].resize(deg[i]);
		for (int j = 0; j < deg[i]; j++) {
			cin >> a[i][j];
			a[i][j]--;
			b[a[i][j]].push_back(i);
		}
		if (deg[i] == 1)
			que.push(i);
	}
	vector<int> ans;
	while (sz(que)) {
		int x = que.front();
		que.pop();
		if (deg[x] == 0) {
			break;
		}
		ans.push_back(x + 1);
		for (auto &y : a[x]) {
			if (sz(b[y])) {
				for (auto &z : b[y]) {
					deg[z]--;
					if (deg[z] == 1)
						que.push(z);
				}
				b[y].clear();
			}
		}
	}
	if (sz(ans) < n)
		cout << "-1\n";
	else
		for (auto &x : ans)
			cout << x << " ";
}