#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;
const int mod = 1e9 + 7;

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


string A, B;
int nxt1[MAXN][2], nxt2[MAXN][2];

void make_fail(string &s, int nxt[MAXN][2]){
	vector<int> fail(sz(s) + 1);
	int p = 0;
	for(int i=1; i<sz(s); i++){
		while(p && s[i] != s[p]) p = fail[p];
		if(s[i] == s[p]) p++;
		fail[i + 1] = p;
	}
	for(int i=0; i<sz(s); i++){
		for(int j=0; j<2; j++){
			int pos = i;
			while(pos && s[pos] != j + '0') pos = fail[pos];
			if(s[pos] == j + '0') pos++;
			nxt[i][j] = pos;
		}
	}
	nxt[sz(s)][0] = nxt[sz(s)][1] = sz(s);
}

int main(){
	int n, k1, k2;
	cin >> n >> k1 >> k2;
	if(k1) cin >> A;
	if(k2) cin >> B;
	if(sz(A) > n){
		puts("0");
		return 0;
	}
	if(sz(B) == 0){
		puts("0");
		return 0;
	}
	if(sz(B) > n) B = "2";
	make_fail(A, nxt1);
	make_fail(B, nxt2);
	vector<vector<mint>> cur, nxt;
	cur = vector<vector<mint>>(sz(A) + 1, vector<mint>(sz(B) + 1, mint(0)));
	cur[0][0] = 1;
	for(int i = 1; i <= n; i++){
		nxt = vector<vector<mint>>(sz(A) + 1, vector<mint>(sz(B) + 1, mint(0)));
		for(int j = 0; j <= sz(A); j++){
			for(int k = 0; k <= sz(B); k++){
				for(int x = 0; x < 2; x++){
					nxt[nxt1[j][x]][nxt2[k][x]] += cur[j][k];
				}
			}
		}
		cur = nxt;
	}
	mint ret = 0;
	for(int i = 0; i < sz(B); i++) ret += cur[sz(A)][i];
	cout << ret << endl;
}
