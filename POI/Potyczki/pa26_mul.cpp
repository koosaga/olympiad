#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

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
	mint inv() const { return ipow(*this, mod - 2); }
	mint &operator/=(const mint &m) { return (*this) *= m.inv(); }

	friend mint operator+(mint a, const mint &b) { return a += b; }
	friend mint operator-(mint a, const mint &b) { return a -= b; }
	friend mint operator*(mint a, const mint &b) { return a *= b; }
	friend mint operator/(mint a, const mint &b) { return a /= b; }
	operator int64_t() const { return val; }
};
const int maxn = 1 << 22;
const int magic = 250; // threshold for sizes to run the naive algo

template <typename T> T fact(int n) {
	static T F[maxn];
	static bool init = false;
	if (!init) {
		F[0] = T(1);
		for (int i = 1; i < maxn; i++) {
			F[i] = F[i - 1] * T(i);
		}
		init = true;
	}
	return F[n];
}

template <typename T> T rfact(int n) {
	static T F[maxn];
	static bool init = false;
	if (!init) {
		F[maxn - 1] = T(1) / fact<T>(maxn - 1);
		for (int i = maxn - 2; i >= 0; i--) {
			F[i] = F[i + 1] * T(i + 1);
		}
		init = true;
	}
	return F[n];
}

map<vector<int>, mint> mp;
vector<int> ord;
int sodlve(vector<pi> v) {
	int n = sz(v) / 2;
	vector<int> pos(4 * n);
	for (int i = 0; i < 2 * n; i++) {
		for (int j = 0; j < 2; j++) {
			pos[v[i][j]] = i;
		}
	}
	int winner = pos[4 * n - 1] % 2;
	for (int i = 4 * n - 2; i >= 0; i--) {
		if (pos[i + 1] % 2 == pos[i] % 2) {
			if (winner == pos[i] % 2)
				return winner == 1 ? 0 : 2;
			return 1;
		}
		if (pos[i + 1] < pos[i]) {
			if (winner == pos[i] % 2) {
				return winner == 1 ? 0 : 2;
			}
			return 1;
		}
	}
	return 1;
}

void dfs(int n, int p, vector<int> cnt, vector<int> vis) {

	if (count(all(vis), -1) == 0) {
		mp[vis] += fact<mint>(4 * n - p) / ipow(mint(2), count(all(cnt), 2));
		return;
	}
	for (int i = 0; i < sz(cnt); i++) {
		if (cnt[i]) {
			cnt[i]--;
			ord.push_back(i);
			vector<int> nvis = vis;
			if (sz(ord) >= 2) {
				int towrite = 1;
				if (ord[0] % 2 == i % 2)
					towrite = 2 * (i % 2);
				if (ord[sz(ord) - 2] % 2 == i % 2) {
					for (auto &z : nvis) {
						if (z == -1)
							z = towrite;
					}
				} else {
					int L = ord[sz(ord) - 2];
					int R = ord[sz(ord) - 1];
					for (int j = L; j != R; j = (j + 1) % (2 * n)) {
						if (nvis[j] != -1)
							continue;
						nvis[j] = towrite;
					}
				}
			}
			dfs(n, p + 1, cnt, nvis);
			ord.pop_back();
			cnt[i]++;
		}
	}
}

mint eval(vector<int> &cnt) {
	mint prod = 1;
	int sum = 0;
	for (int i = 0; i < sz(cnt); i++) {
		if (cnt[i] < 0)
			return mint(0);
		sum += cnt[i];
		if (cnt[i] == 2)
			prod *= mint(2);
	}
	return fact<mint>(sum) / prod;
}

mint ipwr[maxn];

void solve() {
	int n;
	cin >> n;
	vector<int> a(2 * n);
	for (auto &x : a)
		cin >> x;
	if (*max_element(all(a)) - *min_element(all(a)) >= 2) {
		cout << "0\n";
		return;
	}
	if (*max_element(all(a)) == 2) {
		for (auto &x : a)
			x = 2 - x;
		rotate(a.begin(), 1 + all(a));
	}
	if (count(all(a), 0) == 2 * n) {
		mint ans = 0;
		ans += mint(n) * fact<mint>(4 * n - 2) * ipwr[2 * n - 1];
		ans += mint(n) * mint(n - 1) * fact<mint>(4 * n - 2) * ipwr[2 * n - 2];
		cout << ans << "\n";
		return;
	}
	if (count(all(a), 1) == 2 * n) {
		mint ans = 0;
		ans += mint(n) * fact<mint>(4 * n - 3) * ipwr[2 * n - 2];
		if (n > 1)
			ans += mint(n) * mint(n - 1) * fact<mint>(4 * n - 3) * ipwr[2 * n - 3];
		cout << ans * mint(2 * n) << "\n";
		return;
	}
	vector<int> cnt(2 * n, 2);
	for (int i = 0; i < 2 * n; i++) {
		if (a[i] != a[(i + 2 * n - 1) % (2 * n)]) {
			if (a[i] == i % 2) {
				cout << "0\n";
				return;
			}
			cnt[i]--;
		}
	}
	vector<int> cons(2 * n);
	for (int j = 0; j < 2 * n; j++) {
		if (a[(j + 2 * n - 1) % (2 * n)] != a[j]) {
			int last = a[j], con = 0;
			for (int k = j; k < j + 2 * n; k++) {
				if (last != a[k % (2 * n)])
					last = a[k % (2 * n)], con = 0;
				con++;
				cons[(k + 1) % (2 * n)] = con;
			}
			break;
		}
	}
	int counts[2][3] = {};
	for (int i = 0; i < 2 * n; i++) {
		counts[i % 2][cnt[i]]++;
	}
	auto eval_fast = [&] {
		int c1 = counts[0][1] + counts[1][1];
		int c2 = counts[0][2] + counts[1][2];
		return fact<mint>(c1 + 2 * c2) * ipwr[c2];
	};
	vector<array<int, 3>> psum(4 * n + 2);
	for (int i = 4 * n - 1; i >= 0; i--) {
		psum[i] = psum[i + 2];
		psum[i][cnt[i % (2 * n)]]++;
	}
	mint ans = 0;
	for (int i = 0; i < 2 * n; i += 2) {
		if (a[i] == 0)
			continue;
		if (a[i] == a[(i + 2 * n - 1) % (2 * n)]) {
			counts[i % 2][cnt[i]]--;
			cnt[i]--;
			counts[i % 2][cnt[i]]++;
		}
		int pos = (i + 2 * n - cons[i]) % (2 * n);
		int len = cons[i];
		int whohowmuch[3] = {};
		int is = i + (len % 2 == 0 ? 1 : 0);
		int ie = i + 2 * n - len;
		if ((is & 1) != (ie & 1))
			ie--;
		if (is <= ie) {
			for (int j = 0; j < 3; j++) {
				whohowmuch[j] = psum[is][j] - psum[ie + 2][j];
			}
		}
		int v = (pos + 1) % 2;
		for (int i = 1; i <= 2; i++) {
			if (whohowmuch[i] == 0)
				continue;
			counts[v][i]--;
			counts[v][i - 1]++;
			ans += eval_fast() * mint(whohowmuch[i]);
			counts[v][i]++;
			counts[v][i - 1]--;
		}
		if (len > 1) {
			assert(counts[v][2] > 0);
			counts[v][2]--;
			counts[v][1]++;
			if (counts[v][1]) {
				counts[v][1]--;
				ans += mint(len / 2) * mint(counts[v][1] + 1) * eval_fast();
				counts[v][1]++;
			}
			if (counts[v][2]) {
				counts[v][2]--;
				counts[v][1]++;
				ans += mint(len / 2) * mint(counts[v][2] + 1) * eval_fast();
				counts[v][2]++;
				counts[v][1]--;
			}
			counts[v][2]++;
			counts[v][1]--;
		}
		if (a[i] == a[(i + 2 * n - 1) % (2 * n)]) {
			counts[i % 2][cnt[i]]--;
			cnt[i]++;
			counts[i % 2][cnt[i]]++;
		}
	}
	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ipwr[0] = 1;
	for (int i = 1; i < maxn; i++)
		ipwr[i] = ipwr[i - 1] * mint((mod + 1) / 2);
	int tc;
	cin >> tc;
	while (tc--)
		solve();
}