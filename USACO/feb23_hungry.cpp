#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int mod = 1e9 + 7;
const int B = 256;

struct mint {
	int val;
	mint() { val = 0; }
	mint(const lint &v) {
		val = (-mod <= v && v < mod) ? v : v % mod;
		if (val < 0)
			val += mod;
	}

	friend ostream &operator<<(ostream &os, const mint &a) { return os << a.val; }
	friend bool operator==(const mint &a, const mint &b) { return a.val == b.val; }
	friend bool operator!=(const mint &a, const mint &b) { return !(a == b); }
	friend bool operator<(const mint &a, const mint &b) { return a.val < b.val; }

	mint operator-() const { return mint(-val); }
	mint &operator+=(const mint &m) {
		if ((val += m.val) >= mod)
			val -= mod;
		return *this;
	}
	mint &operator-=(const mint &m) {
		if ((val -= m.val) < 0)
			val += mod;
		return *this;
	}
	mint &operator*=(const mint &m) {
		val = (lint)val * m.val % mod;
		return *this;
	}
	friend mint ipow(mint a, lint p) {
		mint ans = 1;
		for (; p; p /= 2, a *= a)
			if (p & 1)
				ans *= a;
		return ans;
	}
	friend mint inv(const mint &a) {
		assert(a.val);
		return ipow(a, mod - 2);
	}
	mint &operator/=(const mint &m) { return (*this) *= inv(m); }

	friend mint operator+(mint a, const mint &b) { return a += b; }
	friend mint operator-(mint a, const mint &b) { return a -= b; }
	friend mint operator*(mint a, const mint &b) { return a *= b; }
	friend mint operator/(mint a, const mint &b) { return a /= b; }
	operator int64_t() const { return val; }
};

vector<pi> invert(vector<pi> v) {
	vector<pi> ret;
	if (sz(v) == 0) {
		ret.push_back({0, lint(1e15)});
	} else {
		ret.push_back({0, v[0][0]});
		for (int i = 0; i < sz(v); i++) {
			if (i + 1 < sz(v))
				ret.push_back({v[i][1], v[i + 1][0]});
			else
				ret.push_back({v[i][1], lint(1e15)});
		}
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<pi> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i][0] >> a[i][1];
	map<lint, lint> lengths;
	for (int i = 0; i < n; i += B) {
		int l = i, r = min(i + B, n);
		set<lint> upds;
		for (int j = l; j < r; j++) {
			upds.insert(a[j][0]);
		}
		map<lint, lint> tentative;
		pi interval = {-1, -1};
		vector<pi> v;
		for (auto &[x, c] : lengths) {
			if (upds.count(x)) {
				tentative[x] = c;
				continue;
			}
			if (interval[1] < x) {
				if (interval[0] < interval[1])
					v.push_back(interval);
				interval[0] = interval[1] = x;
			}
			interval[1] += c;
		}
		if (interval[0] < interval[1])
			v.push_back(interval);
		mint sum = 0;
		for (auto &z : v) {
			sum += mint(z[0] + z[1] - 1) * mint(z[1] - z[0]);
		}
		v = invert(v);
		vector<lint> lenSum(sz(v) + 1);
		vector<mint> numSum(sz(v) + 1);
		for (int i = 1; i <= sz(v); i++) {
			lenSum[i] = lenSum[i - 1] + v[i - 1][1] - v[i - 1][0];
			numSum[i] = numSum[i - 1] + mint(v[i - 1][1] + v[i - 1][0] - 1) * mint(v[i - 1][1] - v[i - 1][0]);
		}
		// todo: optimize this shit
		auto jump = [&](lint pos, lint nxt, mint &ans) {
			if (nxt == 0)
				return pos;
			int s = 0, e = sz(v);
			while (s != e) {
				int m = (s + e) / 2;
				if (v[m][1] > pos)
					e = m;
				else
					s = m + 1;
			}
			if (v[s][0] > pos)
				pos = v[s][0];
			lint goalSum = lenSum[s] + max(pos - v[s][0], 0ll) + nxt;
			int goalWhere = upper_bound(all(lenSum), goalSum) - lenSum.begin() - 1;
			lint remLength = goalSum - lenSum[goalWhere];
			lint destination = v[goalWhere][0] + remLength;
			ans += numSum[goalWhere] + mint(v[goalWhere][0] * 2 + remLength - 1) * mint(remLength);
			ans -= numSum[s] + mint(v[s][0] * 2 + max(pos - v[s][0], 0ll) - 1) * mint(max(pos - v[s][0], 0ll));
			return destination;
		};
		auto getSumFromTentative = [&]() {
			pi interval = {-1, -1};
			mint ans;
			for (auto &[x, c] : tentative) {
				if (interval[1] < x) {
					interval[0] = interval[1] = x;
				}
				interval[1] = jump(interval[1], c, ans);
			}
			return ans;
		};
		for (int j = l; j < r; j++) {
			tentative[a[j][0]] = a[j][1];
			cout << (sum + getSumFromTentative()) * mint((mod + 1) / 2) << "\n";
		}
		for (int j = l; j < r; j++) {
			lengths[a[j][0]] = a[j][1];
		}
	}
}