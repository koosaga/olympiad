#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

pi operator+(const pi &a, const pi &b) { return pi{a[0] + b[0], a[1] + b[1]}; }
pi operator-(const pi &a, const pi &b) { return pi{a[0] - b[0], a[1] - b[1]}; }
lint ccw(pi a, pi b) { return a[0] * b[1] - b[0] * a[1]; }
lint ccw(pi a, pi b, pi c) { return ccw(b - a, c - a); }

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<int> ord(n);
		vector<vector<int>> go(n, vector<int>(n));
		iota(all(ord), 0);
		for (int i = n - 1; i >= 1; i--) {
			cout << "?";
			for (int j = 0; j < n; j++)
				cout << " " << ord[j] + 1;
			cout << endl;
			for (int j = n - 1; j >= 0; j--) {
				int ans;
				cin >> ans;
				if (i - j >= 0) {
					// go[s][e] = s -> [s + 1, ... e]
					go[i - j][i] = ans;
				}
			}
			rotate(ord.begin(), ord.end() - 1, ord.end());
		}
		vector<pi> ans;
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				for (int k = go[i][j - 1]; k < go[i][j]; k++)
					ans.push_back({i + 1, j + 1});
			}
		}
		cout << "! " << sz(ans) << endl;
		for (auto &[u, v] : ans)
			cout << u << " " << v << endl;
	}
}