#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

pi pat[8] = {{1, 3}, {1, 3}, {1, 3}, {2, 4}, {4, 6}, {5, 8}, {5, 8}, {5, 8}};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cout << i << " " << 2*n + 1 - i << "\n";
	cout << "\n";
	for (int i = 0; i < n / 8; i++) {
		for (int j = 0; j < 8; j++) {
			int s = i * 8 + pat[j][0];
			int e = i * 8 + pat[j][1];
			cout << e << " " << 2*n + 1 - s << "\n";
		}
	}
	for (int i = (n / 8) * 8 + 1; i <= n; i++) {
		cout << i << " " << 2*n + 1 - i << "\n";
	}
}