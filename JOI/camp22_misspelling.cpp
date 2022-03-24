#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 500005;
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

mint dp[MAXN][26][2];
mint sumFor[MAXN][26];
pi a[MAXN];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<pi> v[2];
	for(int i = 0; i < m; i++){
		cin >> a[i].first >> a[i].second;
		if(a[i].first < a[i].second){
			v[0].emplace_back(a[i].first, a[i].second - 1);
		}
		else{
			v[1].emplace_back(a[i].second, a[i].first - 1);
		}
	}
	vector<int> lowest[2];
	for(int i = 0; i < 2; i++){
		lowest[i].resize(n + 1);
		sort(all(v[i]), [&](const pi &a, const pi &b){
			return a.second > b.second;
		});
		int ptr = 0;
		priority_queue<int> pq;
		for(int j = n - 1; j >= 0; j--){
			while(ptr < sz(v[i]) && v[i][ptr].second >= j){
				pq.push(v[i][ptr++].first);
			}
			while(sz(pq) && pq.top() > j) pq.pop();
			lowest[i][j] = (sz(pq) ? pq.top() : -1e9);
		}
	}
	mint ret = mint(26);
	for(int i = 1; i < n; i++){
		for(int j = 0; j < 26; j++){
			for(int k = 0; k < 2; k++){
				if(lowest[k][i] <= 0) dp[i][j][k] += mint(1);
				if(max(1, lowest[k][i]) < i){
					dp[i][j][k] += sumFor[i - 1][j] - 
					sumFor[max(0, lowest[k][i] - 1)][j];
				}
			}
			ret += dp[i][j][0] * mint(25 - j);
			ret += dp[i][j][1] * mint(j);
		}
		mint cursum = 0;
		for(int j = 0; j < 26; j++){
			sumFor[i][j] += cursum;
			cursum += dp[i][j][0];
		}
		cursum = 0;
		for(int j = 25; j >= 0; j--){
			sumFor[i][j] += cursum;
			cursum += dp[i][j][1];
		}
		for(int j = 0; j < 26; j++){
			sumFor[i][j] += sumFor[i-1][j];
		}
	}
	cout << ret << endl;
}
