#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> a(n, vector<int>(m));
	for (auto &x : a)
		for (auto &y : x)
			cin >> y;
	auto locate = [&](int p) {
		for (int i = n - 1; i >= 0; i--) {
			int j = find(all(a[i]), p) - a[i].begin();
			if (j < m)
				return pi{i, j};
		}
		return pi{-1, -1};
	};
	vector<array<int, 3>> seq;
	auto rotR = [&](int x, int c) {
		c = (c % m + m) % m;
		seq.push_back({1, x + 1, c});
		vector<int> nxt(m);
		for (int i = 0; i < m; i++) {
			nxt[(i + c) % m] = a[x][i];
		}
		a[x] = nxt;
	};
	auto rotC = [&](int x, int c) {
		c = (c % n + n) % n;
		seq.push_back({2, x + 1, c});
		vector<int> nxt(n);
		for (int i = 0; i < n; i++) {
			nxt[(i + c) % n] = a[i][x];
		}
		for (int i = 0; i < n; i++) {
			a[i][x] = nxt[i];
		}
	};
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < m; j++) {
			auto [x, y] = locate(i * m + j);
			if (x == i && y == j)
				continue;
			if (x == i) {
				rotC(y, 1);
				rotR(x + 1, 1);
				rotC(y, n - 1);
				auto [fuckx, fucky] = locate(i * m + j);
				x = fuckx;
				y = fucky;
			}
			if (y == j) {
				rotR(x, 1);
				y = (y + 1) % m;
			}
			assert(x != i && y != j);
			rotC(j, x - i);
			rotR(x, (j - y + m) % m);
			rotC(j, n - (x - i));
		}
	}
	auto Swap = [&](int x, int y) {
		for (int i = 0; i < n / 2; i++) {
			rotC(y, n - 1);
			rotR(n - 1, y - x);
			rotC(y, n - 1);
			rotR(n - 1, x - y);
		}
		rotC(y, n - 1);
	};
	for (int i = 0; i < m; i++) {
		if (a[n - 1][i] != (n - 1) * m + i) {
			auto [x, y] = locate((n - 1) * m + i);
			assert(x == n - 1);
			Swap(i, y);
		}
	}
	cout << sz(seq) << "\n";
	for (auto &[a, b, c] : seq)
		cout << a << " " << b << " " << c << "\n";
}