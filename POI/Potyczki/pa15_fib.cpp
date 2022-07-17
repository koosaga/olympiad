#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 500005;
using lint = __int128_t;
lint mod;

lint get_nth(lint n, vector<lint> rec = {1, 1}, vector<lint> dp = {0, 1}){
	int m = rec.size();
	vector<lint> s(m), t(m);
	s[0] = 1;
	if(m != 1) t[1] = 1;
	else t[0] = rec[0];
	auto mul = [&rec](vector<lint> v, vector<lint> w){
		int m = v.size();
		vector<lint> t(2 * m);
		for(int j=0; j<m; j++){
			for(int k=0; k<m; k++){
				t[j+k] += (lint)v[j] * w[k] % mod;
				if(t[j+k] >= mod) t[j+k] -= mod;
			}
		}
		for(int j=2*m-1; j>=m; j--){
			for(int k=1; k<=m; k++){
				t[j-k] += (lint)t[j] * rec[k-1] % mod;
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
	for(int i=0; i<m; i++) ret += (lint)s[i] * dp[i] % mod;
	return ret % mod;
}


vector<string> str;
char buf[69];

int main(){
	mod = 5e18;
	for(int i=0; i<100; i++){
		long long gnth = get_nth(i);
		if(gnth > 2e18) break;
		sprintf(buf, "%lld", gnth);
		string tmp = buf;
		str.push_back(tmp);
	}
	string s;
	cin >> s;
	for(int i=0; i<sz(str); i++){
		if(sz(str[i]) >= sz(s)){
			if(str[i].substr(sz(str[i]) - sz(s), sz(s)) == s){
				cout << i << endl;
				return 0;
			}
		}
	}
	vector<lint> ans;
	mod = 10;
	for(int i=0; i<60; i++){
		if(get_nth(i) == s.back() - '0') ans.push_back(i);
	}
	lint pwr = 60;
	for(int i=sz(s)-2; i>=0; i--){
		mod *= 10;
		lint val = 0;
		for(int k=i; k<sz(s); k++) val = (val * 10) + s[k] - '0';
		vector<lint> nxt;
		for(int j=0; j<10; j++){
			for(auto &k : ans){
				if(get_nth(j * pwr + k) == val) nxt.push_back(j * pwr + k);
				if(sz(nxt) > 10000) break;
			}
			if(sz(nxt) > 10000) break;
		}
		ans = nxt;
		if(sz(ans) == 0) break;
		pwr *= 10;
	}
	int ptr = 0;
	while(ptr < sz(ans) && ans[ptr] < sz(str)) ptr++;
	if(ptr == sz(ans)) puts("NIE");
	else cout << (long long)ans[ptr] << endl;
}
