#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 10000005;
const int mod =1e6 + 3;

struct mint {
    int val;
    mint() { val = 0; }
    mint(const lint& v) {
        val = (-mod <= v && v < mod) ? v : v % mod;
        if (val < 0) val += mod;
    }

    friend ostream& operator<<(ostream& os, const mint& a) { return os << a.val; }
    friend bool operator==(const mint& a, const mint& b) { return a.val == b.val; }
    friend bool operator!=(const mint& a, const mint& b) { return !(a == b); }
    friend bool operator<(const mint& a, const mint& b) { return a.val < b.val; }

    mint operator-() const { return mint(-val); }
    mint& operator+=(const mint& m) { if ((val += m.val) >= mod) val -= mod; return *this; }
    mint& operator-=(const mint& m) { if ((val -= m.val) < 0) val += mod; return *this; }
    mint& operator*=(const mint& m) { val = (lint)val*m.val%mod; return *this; }
    friend mint ipow(mint a, lint p) {
        mint ans = 1; for (; p; p /= 2, a *= a) if (p&1) ans *= a;
        return ans;
    }
    friend mint inv(const mint& a) { assert(a.val); return ipow(a, mod - 2); }
    mint& operator/=(const mint& m) { return (*this) *= inv(m); }

    friend mint operator+(mint a, const mint& b) { return a += b; }
    friend mint operator-(mint a, const mint& b) { return a -= b; }
    friend mint operator*(mint a, const mint& b) { return a *= b; }
    friend mint operator/(mint a, const mint& b) { return a /= b; }
    operator int64_t() const {return val; }
};

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	vector<int> phi(MAXN + 1);
	vector<mint> ps(MAXN + 1);
	vector<mint> pis(MAXN + 1);
	vector<mint> fs(MAXN + 1);
	vector<mint> fis(MAXN + 1);
	for(int i = 1; i < MAXN; i++){
		phi[i] += i;
		for(int j = 2 * i; j < MAXN; j += i) phi[j] -= phi[i];
		ps[i] = ps[i - 1] + mint(phi[i]);
		pis[i] = pis[i - 1] + mint(1ll * i * phi[i]);
		fs[i] = fs[i - 1] + mint(1ll * phi[i] * i / 2) + (i == 1 ? mint(1) : mint(0));
		fis[i] = fis[i - 1] + mint(1ll * phi[i] * i / 2) * mint(i) + (i == 1 ? mint(1) : mint(0));

	}
	auto f = [&](int n, int k){
		int q = (n - 1) / k;
		mint ret = mint(1ll * n * n) * ps[q] - mint(1ll * n * k) * pis[q] + mint(1ll * k * k) * fis[q] - mint(1ll * k * n) * fs[q];
		return ret;
	};
	int q; cin >> q;
	while(q--){
		int n; cin >> n;
		if(n == 1) cout << "0\n";
		else cout << mint(4) * (f(n, 1) - f(n, 2)) - mint(4 * n - 6) + mint(2 * n) << "\n";
	}
}
