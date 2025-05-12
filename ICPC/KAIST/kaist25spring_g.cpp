#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
 
int g(int x, int y) { return (x >> y) & 1; }
 
int main() {
	int n, m;
	cin >> n >> m;
	if (m >= 2 * n - 3) {
		cout << "0" << endl;
		for (int i = 1; i < (1 << n); i++) {
			int pos = -1;
			for (int j = 0; j < n; j++) {
				if (g(i, j) == 1 && g(i, (j + 1) % n) == 0) {
					pos = (j + 1) % n;
				}
			}
			for (int j = n-1; j >=0; j--){
				int k = g(i, j);
				if (j != pos && k == 0)
					k = 2;
				cout << k;
			}
			cout << endl;
		}
		return 0;
	} else {
		auto input = [&]() {
			string s;
			cin >> s;
			vector<int> v(n);
			for (int i = 0; i < n; i++)
				v[i] = (s[i] - '0');
			return v;
		};
		cout << "1" << endl;
		vector<int> holes(n);
		vector<vector<int>> tab(n, vector<int>(n));
		for (int i = 0; i < n; i++) {
			cout << "? ";
			for (int j = 0; j < n; j++) {
				cout << (i == j);
			}
			cout << endl;
			tab[i] = input();
			for (int j = 0; j < n; j++) {
				if (tab[i][j] == 0)
					holes[i]++;
			}
		}
		auto accuse = [&](int i, int j) {
			cout << "? ";
			for (int k = 0; k < n; k++) {
				cout << (i != k && j != k);
			}
			cout << endl;
			vector<int> v = input();
			cout << "! ";
			for (int k = 0; k < n; k++) {
				cout << (i == k);
			}
			cout << " ";
			for (int k = 0; k < n; k++) {
				cout << (j == k);
			}
			cout << " ";
			for (int k = 0; k < n; k++) {
				cout << (i != k && j != k);
			}
			cout << endl;
			exit(0);
		};
		for (int i = 0; i < n; i++) {
			vector<int> vect;
			for (int j = 0; j < n; j++) {
				if (tab[j][i] == 0)
					vect.push_back(j);
			}
			if (sz(vect) >= 2) {
				accuse(vect[0], vect[1]);
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				if (holes[i] + holes[j] <= 1) {
					accuse(i, j);
				}
			}
		}
		assert(count(all(holes), 1) == n);
		for (int i = 0; i < n; i++) {
			int nxt = -1;
			for (int j = 0; j < n; j++) {
				if (tab[i][j] == 0)
					nxt = j;
			}
			accuse(i, nxt);
		}
	}
}