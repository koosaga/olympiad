#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 200005;

lint udiv(lint x, lint y) { return (x + y - 1) / y; }
lint ans[5005][5005];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<vector<pi>> trees;
	for (int i = 2; i <= n; i += 2) {
		// new vertex: i-2, i-1
		vector<pi> edges;
		for (int j = 0; j < sz(trees); j++) {
			trees[j].push_back({2 * j, i - 2});
			trees[j].push_back({2 * j + 1, i - 1});
			edges.push_back({2 * j + 1, i - 2});
			edges.push_back({2 * j, i - 1});
		}
		edges.push_back({i - 2, i - 1});
		trees.push_back(edges);
	}
	if (n % 2 == 1) {
		for (int i = 0; i < sz(trees); i++) {
			trees[i].push_back({0, n - 1});
		}
		vector<pi> edges;
		for (int i = 0; i < n - 1; i++) {
			edges.push_back({i, n - 1});
		}
		trees.push_back(edges);
	}
	cout << sz(trees) << "\n";
	for (auto &x : trees) {
		for (auto &[p, q] : x) {
			cout << p + 1 << " " << q + 1 << "\n";
		}
	}
}