#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int mod = 1e9 + 7; // 1e9 + 7;//993244853;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<lint> deg(n), nbr(n);
	for (int i = 0; i < 15; i++) {
		cout << "QUERY ";
		for (int j = 0; j < n; j++)
			cout << (j >> i) % 2;
		cout << endl;
		for (int j = 0; j < n; j++) {
			lint h;
			cin >> h;
			nbr[j] += (h << i);
		}
	}
	queue<int> que;
	cout << "QUERY " << string(n, '1') << endl;
	for (int j = 0; j < n; j++) {
		cin >> deg[j];
		if (deg[j] == 1) {
			que.push(j);
		}
	}
	vector<pi> edges;
	while (sz(edges) < n - 1) {
		int x = que.front();
		que.pop();
		edges.push_back({x, nbr[x]});
		nbr[nbr[x]] -= x;
		deg[nbr[x]] -= 1;
		if (deg[nbr[x]] == 1)
			que.push(nbr[x]);
	}
	cout << "ANSWER\n";
	for (auto &[u, v] : edges)
		cout << u + 1 << " " << v + 1 << "\n";
	cout << endl;
}