#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 1050000;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.precision(69);
	int n;
	cin >> n;
	vector<int> sum(MAXN);
	for (int i = 1; i < MAXN; i++)
		sum[i] = sum[i - 1] + __builtin_popcount(i);
	for (int i = 1; i <= n; i++) {
		if (sum[i] >= n) {
			int w = sum[i] - n;
			vector<int> v;
			for (int j = i; j > 0; j--) {
				if (sum[j] - sum[j - 1] <= w) {
					w -= (sum[j] - sum[j - 1]);
				} else {
					v.push_back(j);
				}
			}
			assert(w == 0);
			cout << sz(v) << "\n";
			for (int i = 0; i < sz(v); i++) {
				cout << v[i] << " ";
			}
			cout << "\n";
			return 0;
		}
	}
}