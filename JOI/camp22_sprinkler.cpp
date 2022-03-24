#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 200055;
int mod;

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

vector<int> gph[MAXN];
int dep[MAXN], par[MAXN], din[MAXN], dout[MAXN], piv;

void dfs(int x, int p){
	din[x] = ++piv;
	for(auto &y : gph[x]){
		if(y != p){	
			par[y] = x;
			dep[y] = dep[x] + 1;
			dfs(y, x);
		}
	}
	dout[x] = piv;
}

mint dp[MAXN][45];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n >> mod;
	for(int i = 0; i < n-1; i++){
		int s, e; cin >> s >> e;
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	for(int i = n + 1; i < n + 45; i++){
		gph[i].push_back(i + 1);
		gph[i + 1].push_back(i);
	}
	gph[1].push_back(n + 1);
	gph[n + 1].push_back(1);
	n += 45;
	dfs(n, -1);
	for(int i = 1; i <= n; i++){
		for(int j = 0; j <= 40; j++){
			dp[i][j] = mint(1);
		}
	}
	for(int i = 1; i <= n - 45; i++){
		int x;
		cin >> x;
		dp[i][0] *= mint(x);
	}
	int q; cin >> q;
	for(int i = 0; i < q; i++){
		int t; cin >> t;
		if(t == 1){
			int v, d, w; cin >> v >> d >> w;
			vector<int> stks;
			for(int i = 0; i <= d; i++){
				stks.push_back(v); v = par[v];
			}
			for(int i = 0; i <= d; i++){
				if(i < d) dp[stks[i]][d - i - 1] *= mint(w);
				dp[stks[i]][d - i] *= mint(w);
			}
		}
		else{
			int v; cin >> v;
			mint ans = 1;
			for(int i = 0; i <= 40; i++) ans *= dp[v][i], v = par[v];
			cout << ans << endl;
		}
	}
}
