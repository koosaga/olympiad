#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, int>;
#define sz(v) ((int)(v).size())
const int mod = 1e9 + 7;

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

vector<int> get_nth(vector<int> rec, lint n){
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
	return s;
}

lint n;
vector<int> trans = {0, 3, 6, 12, 24, 27, 15, 30};
vector<int> poly = {0, 24, 0, 999999815, 0, 703, 0, 999998687, 0, 1320, 0, 999999304, 0, 192, 0, 999999983, 0, 1};

void fillHori(vector<lint> &dp){
	vector<lint> nxt(32);
	for(int i=0; i<32; i++){
		for(auto &j : trans){
			if((i & j) == j){
				nxt[i] += dp[i^j];
			}
		}
		nxt[i] %= mod;
	}
	dp = nxt;
}

void advance(vector<lint> &dp, lint k){
	auto rem = get_nth(poly, k);
	vector<lint> dap(32);
	for(int i=0; i<sz(rem); i++){
		for(int j=0; j<32; j++){
			dap[j] += rem[i] * dp[j] % mod;
			if(dap[j] >= mod) dap[j] -= mod;
		}
		fillHori(dp);
		reverse(dp.begin(), dp.end());
	}
	dp = dap;
}

int main(){
	int k;
	scanf("%lld %d",&n,&k);
	vector<pi> v(k);
	for(int i=0; i<k; i++){
		scanf("%lld %d",&v[i].first,&v[i].second);
	}
	sort(v.begin(), v.end());
	vector<lint> dp(32);
	dp[0] = 1;
	if(sz(v) == 0){
		advance(dp, n);
		cout << dp[0] << endl;
		return 0;
	}
	advance(dp, v[0].first - 1);
	for(int i=0; i<sz(v); ){
		int e = i;
		int msk = 0;
		while(e < sz(v) && v[e].first == v[i].first){
			msk |= (1 << (v[e].second - 1));
			e++;
		}
		vector<lint> nxt(32);
		for(int j=0; j<32; j++){
			if(j & msk) continue;
			nxt[j | msk] = dp[j];
		}
		fillHori(nxt);
		dp = nxt;
		reverse(dp.begin(), dp.end());
		if(e < sz(v)) advance(dp, v[e].first - v[e-1].first-1);
		else advance(dp, n - v[e-1].first);
		i = e;
	}
	cout << dp[0] << endl;
}
