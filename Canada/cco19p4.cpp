#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
using lint = long long;
#define sz(v) ((int)(v).size())

int n, k;

struct ds {
	// compute max of a + (x - b)^{k/2}
	vector<array<double, 2>> vect;
	double eval(array<double, 2> p, int x) {
		if (k == 2)
			return p[0] + x - p[1];
		if (k == 4)
			return p[0] + (x - p[1]) * (x - p[1]);
		return p[0] + (x - p[1]) * sqrt(x - p[1]);
	}
	int cross(array<double, 2> p, array<double, 2> q) {
		int st = (int)round(max(p[1], q[1])), ed = n + 1;
		while (st != ed) {
			int m = (st + ed) / 2;
			if (eval(p, m) < eval(q, m))
				st = m + 1;
			else
				ed = m;
		}
		return st;
	}
	void insert(double a, double b) {
		array<double, 2> p = {a, b};
		while (sz(vect) >= 2 && cross(vect[sz(vect) - 2], vect.back()) <= cross(vect.back(), p)) {
			vect.pop_back();
		}
		vect.push_back(p);
	}
	double query(int x) {
		while (sz(vect) >= 2 && eval(vect[sz(vect) - 2], x) >= eval(vect.back(), x))
			vect.pop_back();
		return eval(vect.back(), x);
	}
} ds[MAXN];

vector<int> event[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> k >> n;
	vector<double> dp(n + 1);
	vector<int> cnt(n + 1);
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		ds[x].insert(dp[i - 1], cnt[x]);
		cnt[x]++;
		dp[i] = max(dp[i], ds[x].query(cnt[x]));
	}
	cout << setprecision(69) << dp[n] << "\n";
}