#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

struct frac {
	lint a, b;
	frac(lint x) { a = x, b = 1; }
	frac(lint _a, lint _b) {
		if (_b < 0) {
			_a *= -1;
			_b *= -1;
		}
		lint g = gcd(abs(_a), _b);
		a = _a / g;
		b = _b / g;
	}
	bool operator>=(const frac &f) const { return a * f.b >= b * f.a; }
	bool operator<=(const frac &f) const { return a * f.b <= b * f.a; }
	bool operator>(const frac &f) const { return a * f.b > b * f.a; }
	bool operator<(const frac &f) const { return a * f.b < b * f.a; }
	frac operator+(const frac &f) const { return frac(a * f.b + b * f.a, b * f.b); }
	frac operator-(const frac &f) const { return frac(a * f.b - b * f.a, b * f.b); }
	frac operator*(const lint x) const { return frac(a * x, b); }
	frac operator*(const frac &f) const { return frac(a * f.a, b * f.b); }
	frac operator/(const frac &f) const { return frac(a * f.b, b * f.a); }
	void output() { cout << setprecision(69) << 1.0L * a / b << endl; }
	lint ceil() {
		if (a >= 0)
			return (a + b - 1) / b;
		return -(frac(-a, b).floor());
	}
	lint floor() {
		if (a >= 0)
			return a / b;
		return -(frac(-a, b).ceil());
	}
};

const int MAXN = 200005;
lint spt[18][MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, v[4];
	cin >> n;
	for (int i = 0; i < 4; i++)
		cin >> v[i];
	vector<string> s(3);
	for (int i = 0; i < 3; i++)
		cin >> s[i];
	s[2][0] = '.';
	vector<pi> ds2;
	{
		for (int i = 0; i < n;) {
			if (s[2][i] == '#') {
				i++;
				continue;
			}
			int j = i;
			while (j < n && s[2][j] == '.')
				j++;
			ds2.push_back({i, j});
			i = j;
		}
		ds2[0][0] = -1e9;
		if (s[2].back() == '#') {
			ds2.push_back({n, n});
		}
		ds2.back()[1] = 1e9;
	}
	vector<int> h1(n + 2), h2(n + 2);
	for (int i = 0; i < n; i++) {
		if (s[0][i] == '.')
			h1[i] = i;
		else
			h1[i] = h1[i - 1];
	}
	h2[n] = n;
	for (int i = n - 1; i >= 0; i--) {
		if (s[0][i] == '#') {
			h2[i] = i;
		} else
			h2[i] = h2[i + 1];
	}
	frac T = {0, 1};
	for (int i = 0; i < sz(ds2); i++)
		spt[0][i] = ds2[i][1] - ds2[i][0];
	for (int i = 1; i < 18; i++) {
		for (int j = 0; j < sz(ds2); j++) {
			spt[i][j] = spt[i - 1][j];
			if (j + (1 << (i - 1)) < sz(ds2))
				spt[i][j] = max(spt[i][j], spt[i - 1][j + (1 << (i - 1))]);
		}
	}
	for (int i = 0; i <= n;) {
		int j = i;
		while (j < n && s[1][j] == '.')
			j++;
		if (j == n) {
			frac pointPer0 = T * (v[2] - v[1]) + frac(i);
			frac pointPer2 = T * (v[2] - v[3]) + frac(i);
			int idx0 = n, idx2 = n;
			while (idx0 > 0 && s[0][idx0 - 1] == '.')
				idx0--;
			while (idx2 > 0 && s[2][idx2 - 1] == '.')
				idx2--;
			frac uptime(0);
			if (idx0 && frac(idx0) > pointPer0) {
				uptime = max(uptime, (frac(idx0) - pointPer0) / frac(v[0] - v[1]));
			}
			if (idx2 && frac(idx2) > pointPer2) {
				uptime = max(uptime, (frac(idx2) - pointPer2) / frac(v[0] - v[3]));
			}
			T = T + uptime;
			break;
		}
		T = T + frac(j - i - 1, v[0] - v[2]);
		i = j - 1;
		auto has = [&](int r, int c) {
			if (c >= n || c < 0)
				return false;
			return s[r][c] == '#';
		};
		// now standing in [i, i + 1)
		// want to go to [k, k + 1)
		int k = i + 1;
		while (has(1, k))
			k++;
		auto uptake0 = [&]() {
			frac pointPer0 = frac(v[2] - v[1]) * T + frac(i);
			if (has(0, pointPer0.ceil()) || has(0, pointPer0.floor())) {
				int j = pointPer0.floor();
				if (j >= 0)
					j = h1[j];
				frac ans = (pointPer0 - j) / (v[1] - v[2]) + frac(k - i, v[1] - v[2]);
				return ans;
			} else {
				int pos = pointPer0.ceil();
				pos = max(pos, 0);
				if (pos < n)
					pos = h2[pos];
				if (pos == n) {
					return frac(k - i, v[0] - v[2]);
				} else {
					// needed displacement
					frac fastTime = (frac(pos - 1) - pointPer0) / (v[0] - v[1]);
					frac lefty = frac(k - i) - fastTime * frac(v[0] - v[2]);
					if (lefty <= frac(0)) {
						return frac(k - i, v[0] - v[2]);
					}
					return fastTime + lefty / frac(v[1] - v[2]);
				}
			}
		};
		auto uptake2 = [&]() {
			frac pointPer2 = T * (v[2] - v[3]) + i;
			int pos = lower_bound(all(ds2), pi{(int)pointPer2.ceil(), -int(2e9)}) - ds2.begin() - 1;
			assert(pos >= 0);
			frac moves = frac(k - i, v[0] - v[2]);
			if (pointPer2 + 1 + moves * (v[0] - v[3]) <= ds2[pos][1]) {
				return moves;
			}
			int z = (moves * (v[0] - v[3])).ceil() + 1;
			for (int i = 17; i >= 0; i--) {
				if (pos + (1 << i) < sz(ds2) && spt[i][pos + 1] < z) {
					pos += (1 << i);
				}
			}
			if (pos + 1 < sz(ds2)) {
				return moves + (frac(ds2[pos + 1][0]) - pointPer2) / (v[2] - v[3]);
			}
			return frac(lint(1e18), 1);
		};
		//		uptake0().output();
		//		uptake2().output();
		frac delta = min(uptake0(), uptake2());
		i = k;
		T = T + delta;
		//		T.output();
	}
	T.output();
}