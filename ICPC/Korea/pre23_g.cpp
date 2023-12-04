#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 5005;

int moe[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	moe[1] = 1;
	for (int i = 1; i < MAXN; i++) {
		for (int j = 2 * i; j < MAXN; j += i) {
			moe[j] -= moe[i];
		}
	}
	int n, k;
	cin >> n >> k;
	double s = 0, e = 1;
	for (int i = 0; i < 50; i++) {
		double m = (s + e) / 2;
		vector<lint> counts(n + 1);
		for (int i = 1; i <= n; i++) {
			counts[i] = counts[i - 1] + (int)floor(i * m);
		}
		lint cnt = 0;
		for (int i = 1; i <= n; i++)
			cnt += counts[n / i] * moe[i];
		if (cnt + 1 >= k )
			e = m;
		else
			s = m;
	}
	double m = (s + e) / 2;
	for (int i = 1; i <= n; i++) {
		if (fabs(m * i - round(m * i)) < 1e-10) {
			cout << (int)round(m * i) << " " << i << endl;
			return 0;
		}
	}
}