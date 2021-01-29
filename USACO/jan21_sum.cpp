#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
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

vector<int> gph[MAXN];
int dist[MAXN][2];

vector<pi> parse(){
	int n,m;
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	for(int i=1; i<=n; i++) dist[i][0] = dist[i][1] = 1e9;
	queue<pi> que;
	auto enq = [&](int x, int d){
		if(dist[x][d%2] > d){
			dist[x][d%2] = d;
			que.emplace(x, d%2);
		}
	};
	enq(1, 0);
	while(sz(que)){
		int x, y;
		tie(x, y) = que.front(); que.pop();
		for(auto &i : gph[x]){
			enq(i, dist[x][y] + 1);
		}
	}
	vector<pi> ans;
	for(int i=1; i<=n; i++){
		gph[i].clear();
		ans.emplace_back(dist[i][0], dist[i][1]);
	}
	return ans;
}

int n;
int sumN = 0;
vector<pair<int, pi>> point[MAXN];
int cnt[MAXN][2][2];

mint solve(vector<pi> v){
	vector<int> event[MAXN];
	sort(all(v));
	for(auto &[t, p] : v){
		event[p].push_back(t);
	}
	mint ret = 0;
	vector<mint> ans(2 * sumN + 1);
	fill(all(ans), 1);
	sort(all(v));
	int zfuck = 0;
	for(int i=0; i<n; i++){
		zfuck = max(zfuck, event[i][0]);
		for(int j=0; j<sz(event[i]); j++){
			if(event[i][j] < 1e8){
				ans[event[i][j]] *= mint(j + 1);
			}
			if(j + 1 < sz(event[i]) && event[i][j+1] < 1e8){
				ans[event[i][j+1]] /= mint(j + 1);
			}
		}
	}
	for(int i = 1; i < sz(ans); i++) ans[i] *= ans[i - 1];
	for(int i = 1; i < sz(ans) && i < zfuck; i++) ans[i] = 0;
	for(int i = 1; i <= sumN * 2; i++){
		ret += (ans[i] - ans[i-1]) * mint(i);
	}
	return ret;
}

int main(){
	vector<vector<pi>> v;
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		vector<pi> slist = parse();
		sumN += sz(slist);
		v.push_back(slist);
	}
	vector<mint> ans(2*sumN+1);
	ans[0] = 1;
	vector<pi> val[3];
	for(int i=0; i<n; i++){
		for(auto &j : v[i]){
			if(j.first < j.second){
				val[0].emplace_back(j.first, i);
				val[1].emplace_back(j.second, i);
				val[2].emplace_back(j.second, i);
			}
			else{
				val[0].emplace_back(j.first, i);
				val[1].emplace_back(j.second, i);
				val[2].emplace_back(j.first, i);
			}
		}
	}
	cout << solve(val[0]) + solve(val[1]) - solve(val[2]) << endl;
}
