#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

using ll = long long;
struct H {
	typedef uint64_t ull;
	ull x;
	H(ull x = 0) : x(x) {}
#define OP(O, A, B)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    \
	H operator O(H o) {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                \
		ull r = x;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     \
		asm(A "addq %%rdx, %0\n adcq $0,%0" : "+a"(r) : B);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            \
		return r;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      \
	}
	OP(+, , "d"(o.x)) OP(*, "mul %1\n", "r"(o.x) : "rdx") H operator-(H o) { return *this + ~o.x; }
	ull get() const { return x + !~x; }
	bool operator==(H o) const { return get() == o.get(); }
	bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11 + 3; // (order ~ 3e9; random also ok)

struct HashInterval {
	vector<H> ha, pw;
	HashInterval(string &str) : ha(sz(str) + 1), pw(ha) {
		pw[0] = 1;
		for (int i = 0; i < sz(str); i++)
			ha[i + 1] = ha[i] * C + str[i], pw[i + 1] = pw[i] * C;
	}
	H query(int a, int b) { // hash [a, b)
		return ha[b] - ha[a] * pw[b - a];
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	string s;
	cin >> s;
	auto hi = HashInterval(s);
	auto eq = [&](int l1, int r1, int l2, int r2) {
		assert(r1 - l1 == r2 - l2);
		return hi.query(l1, r1) == hi.query(l2, r2);
	};
	for (int i = n - (n + 1) / 2; i > 0; i--){
		if (eq(0, i, n - i, n))
			continue;
		int s = 0, e = i, ok = 1;
		while (e - s > 1) {
			int m = (s + e) / 2;
			if (eq(s, m, n - i + s, n - i + m))
				s = m;
			else if (eq(m, e, n - i + m, n - i + e))
				e = m;
			else {
				ok = 0;
				break;
			}
		}
		if (ok) {
			cout << n-i << "\n";
			return 0;
		}
	}
	cout << "-1\n";
}