#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

namespace BM{
	using lint = long long;
lint ipow(lint x, lint p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}
vector<int> berlekamp_massey(vector<int> x){
	vector<int> ls, cur;
	int lf, ld;
	for(int i=0; i<x.size(); i++){
		lint t = 0;
		for(int j=0; j<cur.size(); j++){
			t = (t + 1ll * x[i-j-1] * cur[j]) % mod;
		}
		if((t - x[i]) % mod == 0) continue;
		if(cur.empty()){
			cur.resize(i+1);
			lf = i;
			ld = (t - x[i]) % mod;
			continue;
		}
		lint k = -(x[i] - t) * ipow(ld, mod - 2) % mod;
		vector<int> c(i-lf-1);
		c.push_back(k);
		for(auto &j : ls) c.push_back(-j * k % mod);
		if(c.size() < cur.size()) c.resize(cur.size());
		for(int j=0; j<cur.size(); j++){
			c[j] = (c[j] + cur[j]) % mod;
		}
		if(i-lf+(int)ls.size()>=(int)cur.size()){
			tie(ls, lf, ld) = make_tuple(cur, i, (t - x[i]) % mod);
		}
		cur = c;
	}
	for(auto &i : cur) i = (i % mod + mod) % mod;
	return cur;
}
int get_nth(vector<int> rec, vector<int> dp, lint n){
	int m = rec.size();
	vector<int> s(m), t(m);
	s[0] = 1;
	if(m != 1) t[1] = 1;
	else t[0] = rec[0];
	auto mul = [&rec](vector<int> v, vector<int> w){
		int m = v.size();
		vector<int> t(2 * m);
		for(int j=0; j<m; j++){
			for(int k=0; k<m; k++){
				t[j+k] += 1ll * v[j] * w[k] % mod;
				if(t[j+k] >= mod) t[j+k] -= mod;
			}
		}
		for(int j=2*m-1; j>=m; j--){
			for(int k=1; k<=m; k++){
				t[j-k] += 1ll * t[j] * rec[k-1] % mod;
				if(t[j-k] >= mod) t[j-k] -= mod;
			}
		}
		t.resize(m);
		return t;
	};
	while(n){
		if(n & 1) s = mul(s, t);
		t = mul(t, t);
		n >>= 1;
	}
	lint ret = 0;
	for(int i=0; i<m; i++) ret += 1ll * s[i] * dp[i] % mod;
	return ret % mod;
}
int guess_nth_term(vector<int> x, lint n){
	if(n < x.size()) return x[n];
	vector<int> v = berlekamp_massey(x);
	if(v.empty()) return 0;
	return get_nth(v, x, n);
}
};

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
 
const int MAXN = 100005;
 
vector<int> gph[MAXN], dfn;
int sub[MAXN], par[MAXN];
 
void prec(int x, int p){
	dfn.push_back(x);
	sub[x] = 1;
	for(auto &y : gph[x]){
		if(y != p) prec(y, x), sub[x] += sub[y], par[y] = x;
	}
}
 
struct node{
	int win, lose, dp;
};

node solve(int x, int p){ 
	vector<node> vect;
	for(auto &y : gph[x]){
		if(y == p) continue;
		vect.push_back(solve(y, x));
	}
	int winPosition = 0;
	node ret = {1, 0, 0};
	for(auto &z : vect){
		if(z.dp == 0) winPosition++;
	}
	if(winPosition > 0) ret.dp = 1;
	for(int i = 0; i < sz(vect); i++){
		if(winPosition > 1 - vect[i].dp){
			ret.win += vect[i].win + vect[i].lose;
		}
		else{
			ret.win += vect[i].lose;
			ret.lose += vect[i].win;
		}
	}
	return ret;
}

node naiveMerge(vector<node> &vect){
	int winPosition = 0;
	node ret = {1, 0, 0};
	for(auto &z : vect){
		if(z.dp == 0) winPosition++;
	}
	if(winPosition > 0) ret.dp = 1;
	for(int i = 0; i < sz(vect); i++){
		if(winPosition > 1 - vect[i].dp){
			ret.win += vect[i].win + vect[i].lose;
		}
		else{
			ret.win += vect[i].lose;
			ret.lose += vect[i].win;
		}
	}
	return ret;
}

vector<node> getNodes(int n){
	vector<node> dp(n), pdp(n);
	reverse(all(dfn));
	for(auto &x : dfn){
		vector<node> vect;
		for(auto &y : gph[x]){
			if(y == par[x]) continue;
			vect.push_back(dp[y]);
		}
		dp[x] = naiveMerge(vect);
	}
	reverse(all(dfn));
	for(auto &x : dfn){
		vector<pair<int, node>> vect;
		for(auto &y : gph[x]){
			if(y == par[x]) continue;
			vect.emplace_back(y, dp[y]);
		}
		int winPosition = 0;
		if(x > 0){
			vect.emplace_back(-1, pdp[x]);
		}
		for(auto &[_, z] : vect){
			if(!z.dp) winPosition++;
		}
		node sumPerWinPos[3] = {};
		for(int winPosition = 0; winPosition < 3; winPosition++){
			sumPerWinPos[winPosition].win++;
			for(int i = 0; i < sz(vect); i++){
				if(winPosition > 1 - vect[i].second.dp){
					sumPerWinPos[winPosition].win += vect[i].second.win + vect[i].second.lose;
				}
				else{
					sumPerWinPos[winPosition].win += vect[i].second.lose;
					sumPerWinPos[winPosition].lose += vect[i].second.win;
				}
			}
		}
		for(int i = 0; i < sz(vect); i++){
			if(vect[i].first == -1) continue;
			if(!vect[i].second.dp) winPosition--;
			if(winPosition > 0){
				pdp[vect[i].first].dp = 1;
			}
			pdp[vect[i].first].win = sumPerWinPos[min(winPosition, 2)].win;
			pdp[vect[i].first].lose = sumPerWinPos[min(winPosition, 2)].lose;
			if(winPosition > 1 - vect[i].second.dp){
				pdp[vect[i].first].win -= vect[i].second.win + vect[i].second.lose;
			}
			else{
				pdp[vect[i].first].win -= vect[i].second.lose;
				pdp[vect[i].first].lose -= vect[i].second.win;
			}
			if(!vect[i].second.dp) winPosition++;
		}
	}
	vector<node> ret(n);
	for(int x = 0; x < n; x++){
		vector<node> vect;
		for(auto &y : gph[x]){
			if(y == par[x]) vect.push_back(pdp[x]);
			else vect.push_back(dp[y]);
		}
		ret[x] = naiveMerge(vect);
	}
	return ret;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint n, d; cin >> n >> d;
	for(int i = 0; i < n - 1; i++){
		int u, v; cin >> u >> v;
		u--; v--;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	prec(0, -1);
	auto nodes = getNodes(n);
	vector<int> cnt(n);
	mint lose = 0, wjcnt = 0, win = n;
	mint tot = n;
	mint wjcoeff = n;
	for(int i = 0; i < n; i++){
		auto ans = nodes[i];
		cnt[i] = ans.win;
		if(ans.dp) lose += 1, wjcnt += 1, win -= 1;
		if(i == 0 && ans.dp == 0) wjcoeff = 0;
	}
	mint cntsum = accumulate(all(cnt), 0ll);
	vector<int> recs;
	auto gen = [&](){
		return lose * wjcoeff + win * mint(cnt[0]);
	};
	recs.push_back(gen());
	for(lint i = 1; i < 10; i++){
		mint sum = lose * mint(n) * wjcnt + win * cntsum;
		tot *= mint(1ll * n * n);
		lose = sum;
		win = tot - sum;
		recs.push_back(gen());
	}
	cout << BM::guess_nth_term(recs, d - 1) << "\n";
}

