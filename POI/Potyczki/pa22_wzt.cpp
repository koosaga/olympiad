#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXT = 530005;
const int mod = 1e9 + 7;

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

struct seg {
	struct node {
		mint A[3][3];
		node() {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					A[i][j] = (i == j);
				}
			}
		}
		node(char c) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					A[i][j] = 0;
				}
			}
			if (c != 'C') {
				for (int i = 0; i < 3; i++) {
					A[i][(i + 1) % 3] += mint(1);
				}
			}
			if (c != 'Z') {
				for (int i = 0; i < 3; i++) {
					A[i][(i + 2) % 3] += mint(1);
				}
			}
		}
		node operator*(const node &nd) const {
			node ret;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					ret.A[i][j] = 0;
				}
			}
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					for (int k = 0; k < 3; k++) {
						ret.A[j][k] += A[j][i] * nd.A[i][k];
					}
				}
			}
			return ret;
		}
	} tree[MAXT];
	int lim;
	void init(string &s) {
		for (lim = 1; lim <= sz(s); lim <<= 1)
			;
		for (int i = 0; i < sz(s); i++) {
			tree[i + lim] = node(s[i]);
		}
		for (int i = lim - 1; i; i--) {
			tree[i] = tree[2 * i] * tree[2 * i + 1];
		}
	}
	void update(int x, char c) {
		x += lim;
		tree[x] = node(c);
		while (x > 1) {
			x >>= 1;
			tree[x] = tree[2 * x] * tree[2 * x + 1];
		}
	}
} seg;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.precision(69);
	int n, q;
	cin >> n >> q;
	string s;
	cin >> s;
	seg.init(s);
	int oddGap = 0, evenGap = 0;
	for (int x = 0; x < n; x++) {
		if (s[x] == 'N')
			continue;
		if (x % 2 != s[x] % 2)
			oddGap++;
		else
			evenGap++;
	}
	auto query = [&]() {
        if(n == 1) return (s[0] == 'N' ? mint(2) : mint(1));
        mint ans = seg.tree[1].A[0][1] + seg.tree[1].A[0][2];
		if (n % 2 == 1) {
			if (oddGap == 0)
				ans -= mint(1);
			if (evenGap == 0)
				ans -= mint(1);
		}
		return ans;
	};
	cout << query() << "\n";
	while (q--) {
		int x;
		char c;
		cin >> x >> c;
		x--;
		if (s[x] != 'N') {
			if (x % 2 != s[x] % 2)
				oddGap--;
			else
				evenGap--;
		}
		s[x] = c;
		seg.update(x, c);
		if (s[x] != 'N') {
			if (x % 2 != s[x] % 2)
				oddGap++;
			else
				evenGap++;
		}
		cout << query() << "\n";
	}
}