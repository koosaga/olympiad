#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> a(2 * n), b(m);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a[i + n] = a[i];
	}
	for (int i = 0; i < m; i++)
		cin >> b[i];
	for (int it = 0; it < 2; it++) {
		vector<int> fail(m + 1);
		{
			int p = 0;
			for (int i = 1; i < m; i++) {
				while (p && b[i] != b[p])
					p = fail[p];
				if (b[i] == b[p])
					p++;
				fail[i + 1] = p;
			}
		}
		int p = 0;
		for (int i = 0; i < 2 * n; i++) {
			while (p && a[i] != b[p])
				p = fail[p];
			if (a[i] == b[p])
				p++;
			if (p == m) {
				cout << "1\n";
				return 0;
			}
		}
		reverse(all(b));
	}
	cout << "0\n";
}
