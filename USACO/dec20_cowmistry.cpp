#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXT = 15000000;
const int mod = 1e9 + 7;

template<typename T>
T gcd(const T &a, const T &b) {
    return b == T(0) ? a : gcd(b, a % b);
}

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

int trie[MAXT][2], sz[MAXT], piv = 1;

void add(int s, int e, int ps = 0, int pe = (1 << 30) - 1, int p = 1){
	if(e < ps || pe < s) return;
	if(s <= ps && pe <= e){
		sz[p] = (pe - ps + 1);
		return;
	}
	for(int i=0; i<2; i++) if(!trie[p][i]) trie[p][i] = ++piv;
	int pm = (ps+pe)/2;
	add(s, e, ps, pm, trie[p][0]);
	add(s, e, pm+1, pe, trie[p][1]);
	sz[p] = sz[trie[p][0]] + sz[trie[p][1]];
}

mint totals;
vector<int> midnodes;

int k, D;

void solve(int ps = 0, int pe = (1 << 30) - 1, int p = 1){
	if(sz[p] == pe - ps + 1){
		totals += (pe - ps + 1) / (D + 1);
		return;
	}
	if(p == 0) return;
	if(pe - ps == D){
		if(sz[p]) midnodes.push_back(p);
		return;
	}
	int pm = (ps+pe)/2;
	solve(ps, pm, trie[p][0]);
	solve(pm + 1, pe, trie[p][1]);
}

mint nc3(int d){
	return mint(1ll * d * (d - 1) / 2) * mint(d - 2) * mint((mod + 1) / 3);
}

mint full(int D){
	mint ret = nc3(D / 2) * mint(2);
	ret += mint(1ll * (k - D/2) * (k - D/2 + 1) / 2) * mint(D);
	return ret;
}

mint follow(int p1, int p2, int s, int e){
	if(sz[p1] == 0 || sz[p2] == 0) return mint(0);
	if(s == e) return mint(1);
	if(sz[p1] == e - s + 1 && sz[p2] == e - s + 1){
		return mint(sz[p1]) * mint(max(min(e, k) - s + 1, 0));
	}
	if(sz[p1] < sz[p2]) swap(p1, p2);
	if(sz[p1] == e - s + 1){
		for(int i=0; i<2; i++){
			trie[p1][i] = ++piv;
			sz[piv] = (e - s + 1) / 2;
		}
	}
	int m = (s + e) / 2;
	mint ret = 0;
	if(k <= m){
		for(int i = 0; i < 2; i++){
			ret += follow(trie[p1][i], trie[p2][i], s, m);
		}
	}
	else{
		for(int i = 0; i < 2; i++){
			int s1 = sz[trie[p1][i]];
			int s2 = sz[trie[p2][i]];
			ret += mint(s1) * mint(s2);
			ret += follow(trie[p1][i], trie[p2][i^1], m + 1, e);
		}
	}
	return ret;
}

mint solve(int p1, int p2, int s, int e){
	if(sz[p1] == 0 || sz[p2] == 0) return mint(0);
	if(s == e) return mint(0);
	if(sz[p1] == e - s + 1){
		for(int i=0; i<2; i++){
			trie[p1][i] = ++piv;
			sz[piv] = (e - s + 1) / 2;
		}
	}
	if(sz[p2] == e - s + 1){
		return mint(sz[p1]) * mint(1ll * max(min(e,k) - s + 1, 0) * max(min(e,k) - s, 0) / 2);
	}
	int m = (s + e) / 2;
	mint ret = 0;
	if(k <= m){
		for(int i = 0; i < 2; i++) ret += solve(trie[p1][i], trie[p2][i], s, m);
	}
	else{
		for(int i = 0; i < 2; i++){
			int s1 = sz[trie[p1][i]];
			int s2 = sz[trie[p2][i]];
			ret += mint(s1) * mint(s2) * mint(s2 - 1) * mint((mod + 1) / 2);
			ret += mint(s2) * follow(trie[p1][i], trie[p2][i^1], m+1, e);
			ret += solve(trie[p1][i], trie[p2][i^1], m+1, e);
		}
	}
	return ret;
}

int main(){
	int n;
	scanf("%d %d",&n,&k);
	for(int i=0; i<n; i++){
		int s, e; scanf("%d %d",&s,&e);
		add(s, e);
	}
	D = 1;
	while(D < k) D = 2 * D + 1;
	solve();
	mint ret = totals * full(D + 1);
	for(auto &i : midnodes){
		ret += solve(trie[i][0], trie[i][1], D / 2 + 1, D);
		ret += solve(trie[i][1], trie[i][0], D / 2 + 1, D);
		ret += nc3(trie[i][0] ? sz[trie[i][0]] : D / 2 + 1);
		ret += nc3(trie[i][1] ? sz[trie[i][1]] : D / 2 + 1);
	}
	cout << ret << endl;
}
