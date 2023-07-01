#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 3005;

vector<int> gph[MAXN];
int indeg[MAXN];

bool toposort(int n) {
	int cnt = 0;
	queue<int> que;
	for (int i = 0; i < n; i++) {
		if (!indeg[i])
			que.push(i);
	}
	while (sz(que)) {
		cnt++;
		int x = que.front();
		que.pop();
		for (auto &y : gph[x]) {
			if (indeg[y]) {
				indeg[y]--;
				if (indeg[y] == 0)
					que.push(y);
			}
		}
	}
	return cnt == n;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k, q;
	cin >> n >> k >> q;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i], a[i]--;
	auto good = [&](int l, int r) {
		for (int i = 0; i < k; i++) {
			gph[i].clear();
			indeg[i] = 0;
		}
		for (int i = l; i < r; i++) {
			if (i % 2 == l % 2) {
				gph[a[i]].push_back(a[i + 1]);
				indeg[a[i + 1]]++;
			} else {
				gph[a[i + 1]].push_back(a[i]);
				indeg[a[i]]++;
			}
		}
		return toposort(k);
	};
	vector<int> low(n);
	int j = 0;
	for (int i = 0; i < n; i++) {
		while (j < n && good(i, j))
			j++;
		low[i] = j;
	}
	while (q--) {
		int x, y;
		cin >> x >> y;
		x--;
		y--;
		if (low[x] <= y)
			cout << "NO\n";
		else
			cout << "YES\n";
	}
}