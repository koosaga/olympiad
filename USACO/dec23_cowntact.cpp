#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;

const int MAXN = 100005;
vector<int> gph[MAXN];
vector<int> d1, d2;
string s;
int ans;

// state:
// dist d to closest chosen: {1, d}
// dist d to farthest uncovered: {-1, d}
// nothing: {0, 0}
pi dfs(int x, int p, int l) {
	auto merge = [&](pi a, pi b) {
		if (a > b)
			swap(a, b);
		if (a[0] == 0)
			return b;
		if (b[0] == 0)
			return a;
		if (b[0] == -1)
			return max(a, b);
		if (a[0] == 1)
			return min(a, b);
		return a[1] + b[1] > l ? a : b;
	};
	pi cur = {s[x] == '1' ? -1 : 0, 0};
	for (auto &i : gph[x]) {
		if (i == p)
			continue;
		auto ch = dfs(i, x, l);
		if (ch[0])
			ch[1]++;
		cur = merge(cur, ch);
	}
	if (cur[0] == -1) {
		if (p == -1 || cur[1] + 1 + d2[p] > l) {
			ans++;
			cur = {1, d2[x]};
		}
	}
	return cur;
}

vector<int> bfs(int n, vector<int> src) {
	vector<int> dist(n, 1e9);
	queue<int> que;
	for (auto &x : src) {
		que.push(x);
		dist[x] = 0;
	}
	while (sz(que)) {
		int x = que.front();
		que.pop();
		for (auto &y : gph[x]) {
			if (dist[y] > dist[x] + 1) {
				dist[y] = dist[x] + 1;
				que.push(y);
			}
		}
	}
	return dist;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	cin >> s;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	vector<int> zeros;
	for (int i = 0; i < n; i++) {
		if (s[i] == '0')
			zeros.push_back(i);
	}
	d1 = bfs(n, zeros);
	int q;
	cin >> q;
	while (q--) {
		int l;
		cin >> l;
		vector<int> okays;
		for (int i = 0; i < n; i++) {
			if (d1[i] > l)
				okays.push_back(i);
		}
		bool bad = 0;
		d2 = bfs(n, okays);
		for (int i = 0; i < n; i++) {
			if ((d2[i] <= l) != (s[i] == '1')) {
				bad = 1;
			}
		}
		if (bad) {
			cout << "-1\n";
			continue;
		}
		ans = 0;
		dfs(0, -1, l);
		cout << ans << "\n";
	}
}