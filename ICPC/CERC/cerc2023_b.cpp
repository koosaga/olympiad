#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 20005;
using point = complex<double>;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	string s;
	cin >> s;
	vector<point> p[2];
	for (int i = 0; i < n; i++) {
		double x, y;
		cin >> x >> y;
		p[s[i] == 'B'].emplace_back(x, y);
	}
	double ans = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < sz(p[i]) / 2; j++) {
			ans += abs(p[i][j] - p[i][j + sz(p[i]) / 2]);
		}
	}
	cout << setprecision(69) << ans << "\n";
}